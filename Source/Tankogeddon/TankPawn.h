#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankPlayerController;
class ACannon;

UCLASS()
class TANKOGEDDON_API ATankPawn : public AItem
{
	GENERATED_BODY()

public:
	ATankPawn();
	
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Move(float DeltaTime);

	UFUNCTION()
	void RotateRight(float AxisValue);
	

	UFUNCTION()
	void FireSpecial();
	void SetupCannon(TSubclassOf<ACannon> newCannon);
	void ChangeCannon();
protected:
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float InterpolationKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
	float TurretRotationInterpolationKey = 0.5f;


	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;
	
	TSubclassOf<ACannon> SecondCannon;

	


	UPROPERTY()
	ATankPlayerController* TankController;
};