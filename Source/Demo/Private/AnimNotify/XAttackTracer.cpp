// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/XAttackTracer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "Character/XCharacter.h"
#include "Component/XAttributeComponent.h"

void UXAttackTracer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Player = Cast<AXCharacter>(MeshComp->GetOwner());
	if (Player)
	{
		ActorsToIgnore = { MeshComp->GetOwner() };

		SocketLocation1 = Player->GetMesh()->GetSocketLocation("hand_rSocket");
		SocketLocation2 = Player->WeaponComp->GetSocketLocation("Mid");
		SocketLocation3 = Player->WeaponComp->GetSocketLocation("End");
		UE_LOG(LogTemp, Warning, TEXT("%f,%f,%f"), SocketLocation2.X, SocketLocation2.Y, SocketLocation2.Z );
	}
}

void UXAttackTracer::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (Player)
	{
		UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), SocketLocation1, Player->GetMesh()->GetSocketLocation("hand_rSocket"), FVector(5, 30, 50), Player->GetMesh()->GetSocketRotation("hand_rSocket"),
			ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);
		for (int i = 0; i < HitResults.Num(); i++)
		{
			AActor* HitActor = HitResults[i].GetActor();
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				UGameplayStatics::ApplyDamage(HitActor, -10.f, EventInstigator, Player, DamageTypeClass);
			}
		}
		UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), SocketLocation2, Player->WeaponComp->GetSocketLocation("Mid"), FVector(5, 30, 50), Player->GetMesh()->GetSocketRotation("hand_rSocket"),
			ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);
		for (int i = 0; i < HitResults.Num(); i++)
		{
			AActor* HitActor = HitResults[i].GetActor();
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				UGameplayStatics::ApplyDamage(HitActor, -10.f, EventInstigator, Player, DamageTypeClass);
			}
		}
		UKismetSystemLibrary::BoxTraceMulti(Player->GetWorld(), SocketLocation3, Player->WeaponComp->GetSocketLocation("End"), FVector(5, 30, 50), Player->GetMesh()->GetSocketRotation("hand_rSocket"),
			ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);
		for (int i = 0; i < HitResults.Num(); i++)
		{
			AActor* HitActor = HitResults[i].GetActor();
			if (!HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);
				UGameplayStatics::ApplyDamage(HitActor, -10.f, EventInstigator, Player, DamageTypeClass);
			}
		}
		SocketLocation1 = Player->GetMesh()->GetSocketLocation("hand_rSocket");
		SocketLocation2 = Player->WeaponComp->GetSocketLocation("Mid");
		SocketLocation3 = Player->WeaponComp->GetSocketLocation("End");
	}

}

void UXAttackTracer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	HitActors.Empty();
}
