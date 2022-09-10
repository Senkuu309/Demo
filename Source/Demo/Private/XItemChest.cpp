// Fill out your copyright notice in the Description page of Project Settings.


#include "XItemChest.h"

void AXItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(targetPitch, 0, 0));
}

// Sets default values
AXItemChest::AXItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
	FVector LidLocation = GetActorLocation();
	LidLocation.X -= 35.0f;
	LidLocation.Z += 50.0f;
	LidMesh->SetRelativeLocation(LidLocation);


	targetPitch = 110;
}

// Called when the game starts or when spawned
void AXItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

