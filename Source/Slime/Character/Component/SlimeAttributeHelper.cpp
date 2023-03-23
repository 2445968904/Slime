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
	ElementUpdate_Delegate.Broadcast();
	ConcentrationUpdate_Delegate.Broadcast();
	// ...
	
}


// Called every frame
void USlimeAttributeHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlimeAttributeHelper::AttributeCalculate_Implementation( FSlimeAttribute Want)
{
	
	if(NowElement.Element!=Want.Element)
	{
		//火加上草
		if(NowElement.Element==EElement::Fire&&Want.Element==EElement::Grass)
		{
			ConcentrationChange(Want.Concentration*Restrained*-1);
		}
		//草加上火
		else if(NowElement.Element==EElement::Grass&&Want.Element==EElement::Fire)
		{
			ConcentrationChange(Want.Concentration*UnRestrained*-1);
		}
		//水加上火
		else if(NowElement.Element==EElement::Water&&Want.Element==EElement::Fire)
		{
			ConcentrationChange(Want.Concentration*Restrained*-1);
		}
		//火加上水
		else if(NowElement.Element==EElement::Fire&&Want.Element==EElement::Water)
		{
			ConcentrationChange(Want.Concentration*UnRestrained*-1);
		}
		//水加上草
		else if(NowElement.Element==EElement::Water&&Want.Element==EElement::Grass)
		{
			ConcentrationChange(Want.Concentration*UnRestrained*-1);
		}
		//草加上水
		else if(NowElement.Element==EElement::Grass&&Want.Element==EElement::Water)
		{
			ConcentrationChange(Want.Concentration*Restrained*-1);
		}
        else if(NowElement.Element==EElement::None)		
		ConcentrationChange(Want.Concentration*UnRestrained);
		
		UpdateElement(Want.Element);
	}
	else
	{
		ConcentrationChange(Want.Concentration);
	}
}

void USlimeAttributeHelper::ConcentrationChange_Implementation(float ConcentDown)
{
	NowElement.Concentration+=ConcentDown;
	ConcentrationUpdate_Delegate.Broadcast();
}
void USlimeAttributeHelper::ElementChange_Implementation(EElement Want)
{
	
}

void USlimeAttributeHelper::UpdateElement(EElement Element)
{
	if(NowElement.Element==EElement::None)
	{
		NowElement.Element=Element;
		ElementUpdate_Delegate.Broadcast();
		return ;
	}
	if(NowElement.Concentration==0)
	{
		if(NowElement.Element!=EElement::None)
		NowElement.Element=EElement::None;
		else
			NowElement.Element=Element;
		ElementUpdate_Delegate.Broadcast();
	}
	else if(NowElement.Concentration<0)
	{
		NowElement.Element=Element;
		NowElement.Concentration*=-1.0f;
		ConcentrationUpdate_Delegate.Broadcast();
		ElementUpdate_Delegate.Broadcast();
	}
}

void USlimeAttributeHelper::ReduceAttribute(float ReduceNumber)
{
	ConcentrationChange(ReduceNumber);
}

void USlimeAttributeHelper::MakeContinuedAttribute(FSlimeAttribute ContinuedElement, float Time)
{
	
	
	FContinuedElement_Struct *Children=new FContinuedElement_Struct;
	float con=ContinuedElement.Concentration*TheNumberOfUpdate/Time;

	GEngine->AddOnScreenDebugMessage
			(
				2, 5.0f, FColor::Red, FString::Printf(TEXT("%lf"),con)
					);
	
	Children->ValueUpdate.Concentration=con;
	Children->ValueUpdate.Element=ContinuedElement.Element;
	Children->UpdateTime=0.0f;
	Children->TargetTime=Time;
	ContinuedElements.Add(Children);
	//AActor::GetWorldTimerManager().SetTimer()
	if(!ContinuedElementsHandle.IsValid())
	GetWorld()->GetTimerManager().SetTimer(ContinuedElementsHandle, this, &USlimeAttributeHelper::UpdateAttribute_Continued, TheNumberOfUpdate, true);
	else
	{
		float maxtime=Time;
		for (auto It : ContinuedElements)
		{
			if(Time>(It->TargetTime-It->UpdateTime))
				Time=It->TargetTime-It->UpdateTime;
		}
		GetWorld()->GetTimerManager().ClearTimer(ContinuedElementsHandle);
		GetWorld()->GetTimerManager().SetTimer(ContinuedElementsHandle, this, &USlimeAttributeHelper::UpdateAttribute_Continued, TheNumberOfUpdate, true);
	}
	if(ContinuedElements.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage
			(
				0, 5.0f, FColor::Yellow, (TEXT("NoMember"))
					);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage
			(
				0, 5.0f, FColor::Yellow, TEXT("HaveMember"),false
					);
	}
}

void USlimeAttributeHelper::UpdateAttribute_Continued()
{
	EElement Element=EElement::None;
	float Con=0.0f;
	TArray<FContinuedElement_Struct*> ContinuedElements_local;
	for (auto &It : ContinuedElements)
	{
		It->UpdateTime+=TheNumberOfUpdate;
		if(Element==EElement::None)
			Element=It->ValueUpdate.Element;
		
		Con+=It->ValueUpdate.Concentration*(ContinuedCalculateNumber(Element,It->ValueUpdate.Element));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage
			(
				2, 5.0f, FColor::Yellow, FString::Printf(TEXT("%lf"),ContinuedCalculateNumber(Element,It->ValueUpdate.Element))
					);
					
		}
		if(Con<0)
		{
			Element=It->ValueUpdate.Element;
			Con=Con*-1.0f;
		}
			
		else if(Con==0)
		{
			Element=EElement::None;
		}
		//ContinuedElements.RemoveAt()
		if(It->UpdateTime>=It->TargetTime)
			ContinuedElements_local.Add(It);
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%lf"), Con));
	}
	
	for(auto &It : ContinuedElements_local)
	ContinuedElements.Remove(It);
	
	if(ContinuedElements.IsEmpty())
		GetWorld()->GetTimerManager().ClearTimer(ContinuedElementsHandle);

	FSlimeAttribute in ;
	in.Concentration=Con;
	in.Element=Element;
	AttributeCalculate(in);
}


float USlimeAttributeHelper::ContinuedCalculateNumber(EElement Now, EElement Add)
{
	if(Now==Add)
		return 1.0f;
	else if(Now==EElement::Fire&&Add==EElement::Grass)
		return UnRestrained*-1;
	else if(Now==EElement::Grass&&Add==EElement::Fire)
		return Restrained*-1;
	else if(Now==EElement::Grass&&Add==EElement::Water)
		return Restrained*-1;
	else if(Now==EElement::Water&&Add==EElement::Grass)
		return UnRestrained*-1;
	else if(Now==EElement::Fire&&Add==EElement::Water)
		return Restrained*-1;
	else if(Now==EElement::Water&&Add==EElement::Fire)
		return UnRestrained*-1;
	else
		return 0.0f;
}



