// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "slime/library/Slime_SturctLibrary.h"
#include "SlimeAttributeHelper.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateAttribute);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireWithGrass);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrassWithFire);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaterWithFire);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireWithWater);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrassWithWater);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaterWithGrass);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNormalElementEvent);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FElementUpdate);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConcentrationUpdate,bool,IsAdd);





UCLASS( Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLIME_API USlimeAttributeHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlimeAttributeHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void AttributeCalculate(FSlimeAttribute Want);
	void AttributeCalculate_Implementation(FSlimeAttribute Want);

	UFUNCTION(BlueprintNativeEvent)
	void ConcentrationChange(float ConcentAdd);
	void ConcentrationChange_Implementation(float ConcentAdd);

	UFUNCTION(BlueprintNativeEvent)
	void ElementChange(EElement Want);
	void ElementChange_Implementation(EElement Want);

	//克制
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Restrained = 1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float UnRestrained = 1.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlimeAttribute NowElement ;

	UPROPERTY(BlueprintAssignable)
	FUpdateAttribute UpdateAttribute_Delegate;

	UPROPERTY(BlueprintAssignable)
	FElementUpdate ElementUpdate_Delegate;
	
	UPROPERTY(BlueprintAssignable)
	FConcentrationUpdate ConcentrationUpdate_Delegate;

	UFUNCTION()
	void UpdateElement(EElement Element);

	UFUNCTION(BlueprintCallable)
	void ReduceAttribute(float ReduceNumber);
	
	//持续的元素叠加操作
	UFUNCTION(BlueprintCallable)
	void MakeContinuedAttribute(FSlimeAttribute ContinuedElement,float Time);

	TArray<FContinuedElement_Struct*> ContinuedElements;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TheNumberOfUpdate=0.1f;

	FTimerHandle ContinuedElementsHandle;

	UFUNCTION()
	void UpdateAttribute_Continued();

	UFUNCTION()
	float ContinuedCalculateNumber(EElement Now,EElement Add);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxAddConcentration=100.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool UseAutoConcentrationAdd;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AutoAddTime=5.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AutoOnceAdd=1.0f;
	
	UPROPERTY()
	bool canAutoAddConcentration=true;
	
	UFUNCTION()
	void AutoAddConcentration();

	UFUNCTION()
	void CallWhenConcentrationChange(bool IsAdd);

	FTimerHandle ConcentrationHandle;
	UFUNCTION()
	void SetCanAutoAddConcentration();
};
