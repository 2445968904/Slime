// Copyright Win All. All Rights Reserved.


#include "SeeThroughSystemRuntimeLibrary.h"

#include "CoreMinimal.h"

#if WITH_EDITOR 
#include "MaterialFunctionUtility.h"
#endif

bool USeeThroughSystemRuntimeLibrary::IsMaskedOrTranslucentMaterial(UMaterialInterface* Material)
{
	if (Material)
	{
		return Material->IsMasked();
	}
	return false;
}

UMaterialInterface* USeeThroughSystemRuntimeLibrary::CreateMaskedMaterialInstanceAsset(const FString& AssetName,
	const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext)
{
#if WITH_EDITOR 
	return UMaterialFunctionUtility::CreateMaskedMaterialInstanceAsset(AssetName, PackagePath, Parent, CallingContext);
#endif
	return nullptr;
}
