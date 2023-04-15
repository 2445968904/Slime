// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EffectFunctionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,DefaultToInstanced, EditInlineNew)
class SLIME_API UEffectFunctionBase : public UObject
{
	GENERATED_BODY()

	//UEffectFunctionBase();
	~UEffectFunctionBase();
	
protected:
	struct FWorldContext* WorldContext;

	
	UFUNCTION(BlueprintCallable, Category="WorldContext")
		void SetWorldContext(UObject* NewWorldContext);

	UFUNCTION(BlueprintCallable, Category = "WorldContext")
		UObject* GetWorldContextObject();

	
	virtual class UWorld* GetWorld() const override final;
	struct FWorldContext* GetWorldContext() const { return WorldContext; };

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Destroy"))
		void Destroy()
	{
		if (this && this != nullptr)
		{
			this->ConditionalBeginDestroy();
		}
	};
};
