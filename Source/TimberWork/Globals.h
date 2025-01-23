#pragma once

#include "Globals.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateWood);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateWood,float,Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGodMode,bool,Value);

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

