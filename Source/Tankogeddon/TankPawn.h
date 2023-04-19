#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Pawn.h"
#include "Engine/TargetPoint.h"
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
	void SwapCannon();

	TArray<FVector> GetPatrollingPoints();
	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);
	
	UFUNCTION()
	float GetMovementAccurency() {return MovementAccurency; };

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points" , Meta = (MakeEditWidget = true))
	TArray<ATargetPoint*> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Moveparams|Accurency")
	float MovementAccurency = 50;

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



	float targetForwardAxisValue = 0.0f;
	float targetRightAxisValue = 0.0f;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;
	
	TSubclassOf<ACannon> SecondCannon;

	


	UPROPERTY()
	ATankPlayerController* TankController;
};