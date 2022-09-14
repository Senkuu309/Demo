// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XAICharacter.h"

// Sets default values
AXAICharacter::AXAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

