// Fill out your copyright notice in the Description page of Project Settings.


#include "XGameplayFunctionLibrary.h"
#include "Component/XAttributeComponent.h"

bool UXGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UXAttributeComponent* AttributeComp = UXAttributeComponent::GetAttributes(TargetActor);
	if (AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}
	return false;

}

bool UXGameplayFunctionLibrary::ApplyDirectionDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if (HitComp && HitComp->IsSimulatingPhysics(HitResult.BoneName))
		{
			HitComp->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}
		return true;
	}
	return false;
}
