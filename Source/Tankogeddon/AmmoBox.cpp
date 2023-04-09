// Fill out your copyright notice in the Description page of Project Settings.
#include "AmmoBox.h"
#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent * sceeneCpm =
CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = sceeneCpm;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	Mesh->SetCollisionProfileName(FName("OverlapAll"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetGenerateOverlapEvents(true);
}
void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor*OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(10, 1,FColor::Green, TEXT("overlap begin"));
	ATankPawn * playerPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(OtherActor == playerPawn)
	{
		if(AddAmmoQuantity > 0)
		{
			playerPawn->Cannon->AddAmmo(AddAmmoQuantity);
		} else
		{
			playerPawn->SetupCannon(CannonClass);
		}
		
		Destroy();
	}
}