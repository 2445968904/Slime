// Copyright Win All. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Materials/MaterialInterface.h"
#include "UObject/Object.h"
#include "SeeThroughSystemRuntimeLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SEETHROUGHSYSTEMRUNTIME_API USeeThroughSystemRuntimeLibrary : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(Category = "SeeThroughSystem"))
		static bool IsMaskedOrTranslucentMaterial(UMaterialInterface* Material);

	UFUNCTION(BlueprintCallable, meta=(Category = "SeeThroughSystem"))
		static UMaterialInterface* CreateMaskedMaterialInstanceAsset(const FString& AssetName, const FString& PackagePath, UMaterialInterface* Parent, FName CallingContext);
		
};
