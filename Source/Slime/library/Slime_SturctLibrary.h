#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Materials/MaterialInterface.h"
#include "Slime_EnumLibrary.h"

#include "Slime_SturctLibrary.generated.h"

USTRUCT(BlueprintType)
struct FSlimeAttribute
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element")
	EElement Element;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Concentration")
	float Concentration;
};