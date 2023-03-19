#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Materials/MaterialInterface.h"

#include "Slime_EnumLibrary.generated.h"

UENUM(BlueprintType)
enum class EElement : uint8
{
	Grass,
	Water,
	Fire
};


