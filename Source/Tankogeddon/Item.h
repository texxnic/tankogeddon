#pragma once

#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "HealthComponent.h"
#include "Item.generated.h"


class UStaticMeshComponent;
class ACannon;

UCLASS()

class TANKOGEDDON_API AItem : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	AItem();
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Woverloaded-virtual"
	UFUNCTION()
	void TakeDamage(FDamageData DamageData) override;
	#pragma clang diagnostic pop
	
	UFUNCTION()
	void Fire();
	UFUNCTION()
	FVector GetTurretForwardVector() ;
	FVector GetEyesPosition();
	bool IsPlayerSeen(AItem* Spectator, AItem* Player);
	UFUNCTION()
void RotateTurretTo(FVector TargetPosition);

	
	UPROPERTY()
	ACannon* Cannon;

protected:

	void Die();
	void DamageTaked(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
	float TurretRotationInterpolationKey = 0.5f;
	

};