// Fill out your copyright notice in the Description page of Project Settings.


#include "Slime_Base.h"

// Sets default values
ASlime_Base::ASlime_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SlimeAttributeHelper = CreateDefaultSubobject<USlimeAttributeHelper>(TEXT("SlimeAttribureHelper"));
	
}

// Called when the game starts or when spawned
void ASlime_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlime_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlime_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

