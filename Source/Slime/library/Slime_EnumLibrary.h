#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Materials/MaterialInterface.h"

#include "Slime_EnumLibrary.generated.h"

UENUM(BlueprintType)
enum class EElement : uint8
{
	None =0 ,
	Grass = 1 UMETA(DisplayName = "Grass"),
	Water =2 UMETA(DisplayName = "Water"),
	Fire = 3 UMETA(DisplayName = "Fire"),
};


