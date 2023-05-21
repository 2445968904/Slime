// Copyright Win All. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Materials/MaterialInterface.h"
#include "Components/ActorComponent.h"


#include "MaterialFunctionUtility.generated.h"


UCLASS()
class SEETHROUGHSYSTEM_API UMaterialFunctionUtility : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	
		static bool IsMaskedOrTranslucentMaterial(UMaterialInterface* Material);

	
		static UMaterialInterface* CreateMaskedMaterialInstanceAsset(const FString& AssetName, const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext);

	UFUNCTION(BlueprintCallable, meta=(Category = "SeeThroughSystem"))
		static UActorComponent* AddCanBeMaskedComponentToActor(AActor* target, UClass* CompClass);

};
