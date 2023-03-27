// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HBoxComponent.h"
#include "HitTrace_Base.generated.h"


USTRUCT(BlueprintType, meta = (DisplayName = "HitTraceParameter"))
struct FHitTraceParameter
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	AActor* Hitter = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	UHBoxComponent* HBox = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	TArray<TEnumAsByte<ETraceTypeQuery>> TraceChannels;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	float Duration = 0;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	//UGBWPH_HitTraceConfig_Base* ParameterObject = nullptr;

	FHitTraceParameter(){};
};

USTRUCT(BlueprintType, meta = (DisplayName = "HitTraceResult"))
struct FHitTraceResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	TArray<FHitResult> HitResults;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	TArray<FHitResult> ExtendHitResults;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitTrace")
	UObject* ParameterObject = nullptr;

	FHitTraceResult() {};
};


UCLASS()
class HITBOXCOMPONENT_API AHitTrace_Base : public AActor
{
	GENERATED_BODY()
	
public:
	AHitTrace_Base();
public:
	UFUNCTION(BlueprintNativeEvent, Category = "reWrite|HitTrace")
	bool reWrite_InitHitTrace(
		FHitTraceParameter HitTraceParameter);
	virtual bool reWrite_InitHitTrace_Implementation(
		FHitTraceParameter HitTraceParameter){
		return true;
	};

	UFUNCTION(BlueprintCallable, Category = "HitTrace", meta = (DisplayName = "InitHitTrace"))
	bool InitHitTrace(
		FHitTraceParameter HitTraceParameter){
		return reWrite_InitHitTrace(HitTraceParameter);
	};

	UFUNCTION(BlueprintNativeEvent, Category = "reWrite|HitTrace")
	bool reWrite_IsValid();
	virtual bool reWrite_IsValid_Implementation(){
		return false;
	};

	UFUNCTION(BlueprintCallable, Category = "HitTrace", meta = (DisplayName = "IsValid"))
	bool IsValid(){
		return reWrite_IsValid();
	};

	UFUNCTION(BlueprintNativeEvent, Category = "reWrite|HitTrace")
	bool reWrite_StopHitTrace();
	virtual bool reWrite_StopHitTrace_Implementation(){
		return true;
	};

	UFUNCTION(BlueprintCallable, Category = "HitTrace", meta = (DisplayName = "StopHitTrace"))
	bool StopHitTrace(){
		return reWrite_StopHitTrace();
	};
	
	UFUNCTION(BlueprintNativeEvent, Category = "reWrite|HitTrace")
	bool reWrite_UpdateHitTrace(
		float DeltaTime,
		FHitTraceParameter HitTraceParameter,
		FHitTraceResult& HitTraceResult);
	virtual bool reWrite_UpdateHitTrace_Implementation(
		float DeltaTime,
		FHitTraceParameter HitTraceParameter,
		FHitTraceResult& HitTraceResult){
		return true;
	};

	UFUNCTION(BlueprintCallable, Category = "HitTrace", meta = (DisplayName = "UpdateHitTrace"))
	bool UpdateHitTrace(
		float DeltaTime,
		FHitTraceParameter HitTraceParameter,
		FHitTraceResult& HitTraceResult){
		return reWrite_UpdateHitTrace(DeltaTime, HitTraceParameter,HitTraceResult);
	};


};







