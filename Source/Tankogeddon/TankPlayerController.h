#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	FVector MousePos;
	
public:
	UPROPERTY()
	class ATankPawn* TankPawn;
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	FVector GetMousePos() { return MousePos; };

protected:
	virtual void BeginPlay() override;
	void Fire();
	void FireSpecial();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float AxisValue);
	void ChangeCannon();
};