// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeAttributeHelper.h"

// Sets default values for this component's properties
USlimeAttributeHelper::USlimeAttributeHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlimeAttributeHelper::BeginPlay()
{
	Super::BeginPlay();
	ElementUpdate.Broadcast();
	// ...
	
}


// Called every frame
void USlimeAttributeHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlimeAttributeHelper::AttributeCalculate_Implementation(FSlimeAttribute Now , FSlimeAttribute Want)
{
	
	if(Now.Element!=Want.Element)
	{
		//火加上草
		if(Now.Element==EElement::Fire&&Want.Element==EElement::Grass)
		{
			ConcentrationChange(Want.Concentration*Restrained);
		}
		//草加上火
		else if(Now.Element==EElement::Grass&&Want.Element==EElement::Fire)
		{
			ConcentrationChange(Want.Concentration*UnRestrained);
		}
		//水加上火
		else if(Now.Element==EElement::Water&&Want.Element==EElement::Fire)
		{
			ConcentrationChange(Want.Concentration*Restrained);
		}
		//火加上水
		else if(Now.Element==EElement::Fire&&Want.Element==EElement::Water)
		{
			ConcentrationChange(Want.Concentration*UnRestrained);
		}
		//水加上草
		else if(Now.Element==EElement::Water&&Want.Element==EElement::Grass)
		{
			ConcentrationChange(Want.Concentration*UnRestrained);
		}
		//草加上水
		else if(Now.Element==EElement::Grass&&Want.Element==EElement::Water)
		{
			ConcentrationChange(Want.Concentration*Restrained);
		}
	}
	else
	{
		ConcentrationChange(Want.Concentration);
	}
}

void USlimeAttributeHelper::ConcentrationChange_Implementation(float ConcentAdd)
{

	
}
void USlimeAttributeHelper::ElementChange_Implementation(EElement Now,EElement Want)
{
	
}

