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
