// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "DamageTaker.h"
#include "Engine/Engine.h"

// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent * sceeneCpm =
CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

}

void ACannon::Fire()
{
	if(!ReadyToFire || AmmoAmount <= 0)
	{
		return; }
	--AmmoAmount;
	ReadyToFire = false;

	
	ReadyToFire = false;
	ShootEffect->ActivateSystem();
	AudioEffect->Play();
	
	if(Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, FString::Printf(TEXT("Fire - projectile, ammo: %i"), AmmoAmount));
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if(projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, "Fire - trace");
		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;
		FVector start = ProjectileSpawnPoint->GetComponentLocation();
		FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;
		if(GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false,
	0.5f, 0, 5);
			if(hitResult.GetActor())
			{
				IDamageTaker* DamageTakerActor = Cast<IDamageTaker>(hitResult.GetActor());
				if (DamageTakerActor)
				{
					FDamageData damageData;
					damageData.DamageValue = 1.0f;
					damageData.Instigator = GetOwner();
					damageData.DamageMaker = this;

					DamageTakerActor->TakeDamage(damageData);
				}
				else
				{
					hitResult.GetActor()->Destroy();
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	GEngine->AddOnScreenDebugMessage(10, 1,FColor::Red, "Fire - FireSpecial");
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}
void ACannon::Reload()
{
	ReadyToFire = true;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACannon::AddAmmo(int Quantity)
{
	AmmoAmount +=  Quantity;
}
