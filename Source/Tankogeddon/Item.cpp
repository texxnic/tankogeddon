#include "Item.h"
#include "Cannon.h"
#include "HealthComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = HitCollider;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(HitCollider);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &AItem::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &AItem::DamageTaked);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
}

auto AItem::TakeDamage(FDamageData DamageData) -> void
{
	HealthComponent->TakeDamage(DamageData);
}


void AItem::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void AItem::Die()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	Destroy();
}

void AItem::DamageTaked(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Unit %s taked damage: %f, health: %f"), *GetName(), Value, HealthComponent->GetHealth());
}

FVector AItem::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}
void AItem::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation =
  UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation,
  TurretRotationInterpolationKey));
}
FVector AItem::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}
bool AItem::IsPlayerSeen(AItem* Spectator, AItem* Player)
{
	FVector playerPos = Player->GetActorLocation();
	FVector eyesPos = Spectator->GetEyesPosition();

	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);

	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(Spectator);
	traceParams.bReturnPhysicalMaterial = false;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECC_Visibility, traceParams))
	{
		if (hitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return hitResult.GetActor() == Player;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
	return false;
}

