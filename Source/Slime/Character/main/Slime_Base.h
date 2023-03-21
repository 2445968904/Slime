// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "slime/library/Slime_SturctLibrary.h"
#include "Slime/Character/Component/SlimeAttributeHelper.h"
#include "Slime_Base.generated.h"

UCLASS()
class SLIME_API ASlime_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlime_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	USlimeAttributeHelper* SlimeAttributeHelper;
	
};
