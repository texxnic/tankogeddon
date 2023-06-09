// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/UserDefinedStruct.h"
#include "GameStructs.generated.h"


UENUM(BlueprintType)
enum class ECannonType : uint8 {
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireProjectile2 = 1 UMETA(DisplayName = "Use projectile2"),
	FireTrace = 2  UMETA(DisplayName = "Use trace")
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()
	UPROPERTY()
	float DamageValue;
	UPROPERTY()
	AActor * Instigator;
	UPROPERTY()
	AActor * DamageMaker;
};

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
