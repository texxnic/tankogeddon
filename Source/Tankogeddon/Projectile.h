// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "GameStructs.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float PushForce = 1000;
	FTimerHandle MovementTimerHandle;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	float ExplodeRadius = 200;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	bool Explosive = true;
	
	UFUNCTION()
	void SetDamageToActor(AActor* OtherActor);

	UFUNCTION()
	void MakeImpulse(AActor* OtherActor);

	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void Explode();
	virtual void Start();
protected:

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor*
OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool
bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void Move();



};
