// Copyright Win All. All Rights Reserved.

#include "MaterialFunctionUtility.h"
#include "MaskedMaterialInstanceFactory.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "SSCSEditor.h"
#include "ComponentAssetBroker.h"
#include "Kismet2/BlueprintEditorUtils.h"


#include "Materials/Material.h"

UMaterialFunctionUtility::UMaterialFunctionUtility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}
bool UMaterialFunctionUtility::IsMaskedOrTranslucentMaterial(UMaterialInterface* Material)
{
	if (Material)
	{
		return Material->IsMasked();
	}
	return false;
}

UMaterialInterface* UMaterialFunctionUtility::CreateMaskedMaterialInstanceAsset(const FString& AssetName, const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext)
{
#if WITH_EDITOR
	auto Factory = NewObject<UMaskedMaterialInstanceFactory>();
	UObject* ref = Factory->CreateMaskedMaterialInstanceAsset(AssetName, PackagePath, Parent, CallingContext);
	if (ref)
		return Cast<UMaterialInterface>(ref);
#endif
	return nullptr;
}

UActorComponent* UMaterialFunctionUtility::AddCanBeMaskedComponentToActor(AActor* target, UClass* CompClass) {
	if (!target) return nullptr;
	if (!CompClass) return nullptr;

	
	UActorComponent* component = NewObject<UActorComponent>(target,CompClass, "CanBeMasked", RF_Transactional);
	if (!component) return nullptr;
	target->AddInstanceComponent(component);
	component->OnComponentCreated();
	component->RegisterComponent();
	FComponentAssetBrokerage::AssignAssetToComponent(component, target);
	auto node = FSCSEditorTreeNode::FactoryNodeFromComponent(component);
	auto SCNode = node->GetSCSNode();
	target->Modify(true);
	return component;
}