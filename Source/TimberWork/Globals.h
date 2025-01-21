#pragma once

#include "Globals.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
	Security,
	WoodCutter,
	WoodDepositor
};

UCLASS()
class TIMBERWORK_API UGlobal: public UObject
{
	GENERATED_BODY()
};

