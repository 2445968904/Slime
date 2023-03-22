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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConcentrationUpdate);

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
	void AttributeCalculate(FSlimeAttribute Now , FSlimeAttribute Want);
	void AttributeCalculate_Implementation(FSlimeAttribute Now , FSlimeAttribute Want);

	UFUNCTION(BlueprintNativeEvent)
	void ConcentrationChange(float ConcentAdd);
	void ConcentrationChange_Implementation(float ConcentAdd);

	UFUNCTION(BlueprintNativeEvent)
	void ElementChange(EElement Now,EElement Want);
	void ElementChange_Implementation(EElement Now,EElement Want);

	//克制
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Restrained = 2.0f;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float UnRestrained = 0.5f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FSlimeAttribute NowElement ;

	UPROPERTY(BlueprintAssignable)
	FUpdateAttribute UpdateAttribute;

	UPROPERTY(BlueprintAssignable)
	FElementUpdate ElementUpdate;
	
	UPROPERTY(BlueprintAssignable)
	FConcentrationUpdate ConcentrationUpdate;
};
