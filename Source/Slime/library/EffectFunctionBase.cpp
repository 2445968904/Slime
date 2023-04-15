// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectFunctionBase.h"


UEffectFunctionBase::~UEffectFunctionBase()
{
	
}

void UEffectFunctionBase::SetWorldContext(UObject* NewWorldContext)
{
	WorldContext = new FWorldContext();
	WorldContext->SetCurrentWorld(NewWorldContext->GetWorld());
}

UObject* UEffectFunctionBase::GetWorldContextObject()
{
	return WorldContext->World();
}

class UWorld* UEffectFunctionBase::GetWorld() const
{
	return WorldContext ? WorldContext->World() : NULL;
}
