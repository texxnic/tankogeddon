// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"

#include "MapLoader.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATankFactory::ATankFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent * sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	BuildingMesh->SetupAttachment(sceneComp);
	DestroyedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Destroyed Mesh"));
	DestroyedMesh->SetupAttachment(sceneComp);
	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	TankSpawnPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);
	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this,&ATankFactory::OnTriggerOverlapBegin);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);

}

// Called when the game starts or when spawned
void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if(LinkedMapLoader)
		LinkedMapLoader->SetIsActivated(false);
	
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this, &ATankFactory::SpawnNewTank, SpawnTankRate, true, SpawnTankRate);
	
}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}
void ATankFactory::Die()
{
	isDestroyed = true;
	if(DestroyedMesh) BuildingMesh = DestroyedMesh;
	
}
void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}
void ATankFactory::SpawnNewTank()
{
	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(),
TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn * newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//
	newTank->SetPatrollingPoints(TankWayPoints);
	//
	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);
}
void ATankFactory::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult)
{
	if(!isDestroyed)
		return;
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(OtherActor == PlayerPawn)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	};
}