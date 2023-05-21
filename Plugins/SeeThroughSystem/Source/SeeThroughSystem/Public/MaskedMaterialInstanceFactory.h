// Copyright Win All. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialInterface.h"

#include "MaskedMaterialInstanceFactory.generated.h"


UCLASS(BlueprintType, Blueprintable)
class SEETHROUGHSYSTEM_API UMaskedMaterialInstanceFactory : public UMaterialInstanceConstantFactoryNew
{
	GENERATED_UCLASS_BODY()
public:
	//~ Begin UFactory Interface
	UObject* FactoryCreateNewMaterial(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, UMaterialInterface* Parent, FFeedbackContext* Warn);
	//~ Begin UFactory Interface	
	UObject* CreateMaskedMaterialInstanceAsset(const FString& AssetName, const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext);


	bool CanCreateAsset(const FString& AssetName, const FString& PackageName, const FText& OperationText);
};