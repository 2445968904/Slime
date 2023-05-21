// Copyright Win All. All Rights Reserved.


#include "MaskedMaterialInstanceFactory.h"
#include "Materials/MaterialInstanceConstant.h"
#include "CoreMinimal.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ObjectMacros.h"
#include "Misc/Guid.h"
#include "FileHelpers.h"
#include "Misc/MessageDialog.h"
#include "AssetRegistryModule.h"
#include "MaterialEditingLibrary.h"

#include "AssetToolsModule.h"
#include "ObjectTools.h"
#include "PackageTools.h"
#include "Materials/MaterialInstance.h"
/*------------------------------------------------------------------------------
	UMaskedMaterialInstanceFactory implementation.
------------------------------------------------------------------------------*/
UMaskedMaterialInstanceFactory::UMaskedMaterialInstanceFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	SupportedClass = UMaterialInstanceConstant::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UMaskedMaterialInstanceFactory::FactoryCreateNewMaterial(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, UMaterialInterface* Parent, FFeedbackContext* Warn)
{
	UObject* MIC = Super::FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn);
	UMaterialInstanceConstant* Mat = Cast<UMaterialInstanceConstant>(MIC);
	if (Mat) {
		Mat->SetParentEditorOnly(Parent);
		// Set Masked BlendMode
		Mat->BasePropertyOverrides.bOverride_BlendMode = true;
		Mat->BasePropertyOverrides.BlendMode = EBlendMode::BLEND_Masked;
		Mat->UpdateOverridableBaseProperties();
		UMaterialEditingLibrary::UpdateMaterialInstance(Mat);
			
	}

	return Mat;
}


#define LOCTEXT_NAMESPACE "AssetTools"

UObject* UMaskedMaterialInstanceFactory::CreateMaskedMaterialInstanceAsset(const FString& AssetName, const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext)
{
	auto Factory = NewObject<UMaskedMaterialInstanceFactory>();
	auto AssetClass = Factory->SupportedClass;
	// Verify the factory class
	if (!ensure(AssetClass || Factory))
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("MustSupplyClassOrFactory", "The new asset wasn't created due to a problem finding the appropriate factory or class for the new asset."));
		return nullptr;
	}

	if (AssetClass && Factory && !ensure(AssetClass->IsChildOf(Factory->GetSupportedClass())))
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("InvalidFactory", "The new asset wasn't created because the supplied factory does not support the supplied class."));
		return nullptr;
	}

	const FString PackageName = UPackageTools::SanitizePackageName(PackagePath + TEXT("/") + AssetName);

	// Make sure we can create the asset without conflicts
	/*if (!Factory->CanCreateAsset(AssetName, PackageName, LOCTEXT("CreateANewObject", "Create a new object")))
	{
		return nullptr;
	}*/

	UClass* ClassToUse = AssetClass;
	if(!AssetClass && Factory )
	{
		ClassToUse = Factory->GetSupportedClass();
	}

	UPackage* Pkg = CreatePackage(nullptr, *PackageName);
	UObject* NewObj = nullptr;
	EObjectFlags Flags = RF_Public | RF_Standalone | RF_Transactional;
	if (Factory)
	{
		NewObj = Factory->FactoryCreateNewMaterial(ClassToUse, Pkg, FName(*AssetName), Flags, nullptr, Parent, GWarn);
	}
	else if (AssetClass)
	{
		NewObj = NewObject<UObject>(Pkg, ClassToUse, FName(*AssetName), Flags);
	}

	if (NewObj)
	{
		// Notify the asset registry
		FAssetRegistryModule::AssetCreated(NewObj);

		// analytics create record
		//UAssetToolsImpl::OnNewCreateRecord(AssetClass, false);

		// Mark the package dirty...
		Pkg->MarkPackageDirty();
	}

	return NewObj;
}



bool UMaskedMaterialInstanceFactory::CanCreateAsset(const FString& AssetName, const FString& PackageName, const FText& OperationText)
{
	// @todo: These 'reason' messages are not localized strings!
	FText Reason;
	if (!FName(*AssetName).IsValidObjectName(Reason)
		|| !FPackageName::IsValidLongPackageName(PackageName, /*bIncludeReadOnlyRoots=*/false, &Reason))
	{
		FMessageDialog::Open(EAppMsgType::Ok, Reason);
		return false;
	}

	// We can not create assets that share the name of a map file in the same location
	if (FEditorFileUtils::IsMapPackageAsset(PackageName))
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::Format(LOCTEXT("AssetNameInUseByMap", "You can not create an asset named '{0}' because there is already a map file with this name in this folder."), FText::FromString(AssetName)));
		return false;
	}

	// Find (or create!) the desired package for this object
	UPackage* Pkg = CreatePackage(nullptr, *PackageName);

	// Handle fully loading packages before creating new objects.
	TArray<UPackage*> TopLevelPackages;
	TopLevelPackages.Add(Pkg);
	if (!UPackageTools::HandleFullyLoadingPackages(TopLevelPackages, OperationText))
	{
		// User aborted.
		return false;
	}

	// We need to test again after fully loading.
	if (!FName(*AssetName).IsValidObjectName(Reason)
		|| !FPackageName::IsValidLongPackageName(PackageName, /*bIncludeReadOnlyRoots=*/false, &Reason))
	{
		FMessageDialog::Open(EAppMsgType::Ok, Reason);
		return false;
	}

	// Check for an existing object
	UObject* ExistingObject = StaticFindObject(UObject::StaticClass(), Pkg, *AssetName);
	if (ExistingObject != nullptr)
	{
		// Object already exists in either the specified package or another package.  Check to see if the user wants
		// to replace the object.
		bool bWantReplace =
			EAppReturnType::Yes == FMessageDialog::Open(
				EAppMsgType::YesNo,
				EAppReturnType::No,
				FText::Format(
					NSLOCTEXT("UnrealEd", "ReplaceExistingObjectInPackage_F", "An object [{0}] of class [{1}] already exists in file [{2}].  Do you want to replace the existing object?  If you click 'Yes', the existing object will be deleted.  Otherwise, click 'No' and choose a unique name for your new object."),
					FText::FromString(AssetName), FText::FromString(ExistingObject->GetClass()->GetName()), FText::FromString(PackageName)));

		if (bWantReplace)
		{
			// Replacing an object.  Here we go!
			// Delete the existing object
			bool bDeleteSucceeded = ObjectTools::DeleteSingleObject(ExistingObject);

			if (bDeleteSucceeded)
			{
				// Force GC so we can cleanly create a new asset (and not do an 'in place' replacement)
				CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

				// Old package will be GC'ed... create a new one here
				Pkg = CreatePackage(nullptr, *PackageName);
				Pkg->MarkAsFullyLoaded();
			}
			else
			{
				// Notify the user that the operation failed b/c the existing asset couldn't be deleted
				FMessageDialog::Open(EAppMsgType::Ok, FText::Format(NSLOCTEXT("DlgNewGeneric", "ContentBrowser_CannotDeleteReferenced", "{0} wasn't created.\n\nThe asset is referenced by other content."), FText::FromString(AssetName)));
			}

			if (!bDeleteSucceeded || !IsUniqueObjectName(*AssetName, Pkg, Reason))
			{
				// Original object couldn't be deleted
				return false;
			}
		}
		else
		{
			// User chose not to replace the object; they'll need to enter a new name
			return false;
		}
	}

	// Check for a package that was marked for delete in source control
	/*if (!CheckForDeletedPackage(Pkg))
	{
		return false;
	}*/

	return true;
}

#undef LOCTEXT_NAMESPACE

