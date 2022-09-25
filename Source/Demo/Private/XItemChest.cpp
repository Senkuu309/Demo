// Fill out your copyright notice in the Description page of Project Settings.


#include "XItemChest.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include"Components/TimelineComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AXItemChest::AXItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>("BonusMesh");
	BonusMesh->SetupAttachment(BaseMesh);

	BonusComp = CreateDefaultSubobject<UParticleSystemComponent>("BonusComp");
	BonusComp->SetupAttachment(BaseMesh);

	TargetPitch = 110;

	SetReplicates(true);
}

void AXItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	bLidOpened = !bLidOpened;

	OnRep_LidOpened();
}

void AXItemChest::OnRep_LidOpened()
{
	float CurrPitch = bLidOpened ? TargetPitch : 0.0f;
	LidMesh->SetRelativeRotation(FRotator(CurrPitch, 0, 0));
}


void AXItemChest::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AXItemChest, bLidOpened);
}
