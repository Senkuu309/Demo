// Fill out your copyright notice in the Description page of Project Settings.


#include "XGameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "Component/XAttributeComponent.h"
#include "AI/XAICharacter.h"
#include "Character/XCharacter.h"
#include "EngineUtils.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), false, TEXT("Enable Spawning of bots via timer."), ECVF_Cheat);

AXGameModeBase::AXGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AXGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AXGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void AXGameModeBase::KillAll()
{
	for (TActorIterator<AXAICharacter> It(GetWorld()); It; ++It)
	{
		AXAICharacter* Bot = *It;

		UXAttributeComponent* AttributeComp = UXAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->isAlive())
		{
			AttributeComp->Kill(this);
		}
	}
}

void AXGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawing disabled via cvar 'CVarSpawnBots'."));
		return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<AXAICharacter> It(GetWorld()); It; ++It)
	{
		AXAICharacter* Bot = *It;
		if (ensure(Bot->AttributeComp) && Bot->AttributeComp->isAlive())
		{
			NrOfAliveBots++;
		}
	}
	float MaxBotCount = 10.0f;

	if (ensure(DiffcultyCurve))
	{
		MaxBotCount = DiffcultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AXGameModeBase::OnQueryCompleted);

}

void AXGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bot EQS Query Failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(AIClass, Locations[0], FRotator::ZeroRotator);
	}
}

void AXGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AXCharacter* Player = Cast<AXCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}
}

void AXGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}

