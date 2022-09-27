// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttributeComponent.h"
#include "XGameModeBase.h"
#include "Net/UnrealNetwork.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribtue Component."), ECVF_Cheat);

UXAttributeComponent::UXAttributeComponent()
{
	MaxHealth = 200;
	CurrentHealth = MaxHealth;

	SetIsReplicatedByDefault(true);
}

bool UXAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}

bool UXAttributeComponent::isAlive() const
{
	return CurrentHealth > 0.0f;
}

UXAttributeComponent* UXAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UXAttributeComponent>(FromActor->GetComponentByClass(UXAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UXAttributeComponent::IsActorAlive(AActor* FromActor)
{
	UXAttributeComponent* AttributeComp = GetAttributes(FromActor);
	if (AttributeComp)
	{
		return AttributeComp->isAlive();
	}
	return false;
}

float UXAttributeComponent::GetCurrentHealth() {
	return CurrentHealth;
}

float UXAttributeComponent::GetMaxHealth() {
	return MaxHealth;
}


FORCEINLINE FAttributePropertyValue& UXAttributeComponent::GetAttributePropertyStructWithName(EAttributePropertyName Name)
{
	return *AttributeProperties.Find(Name);
}

FORCEINLINE float UXAttributeComponent::GetAttributePropertyValueWithName(EAttributePropertyName Name)
{
	return AttributeProperties.Find(Name)->Current;
}

bool UXAttributeComponent::ModifyAttributePropertyValue(EAttributePropertyName Name, float Delta, bool bUpdateUI)
{
	if (Delta != 0.0f)
	{
		float OldValue = GetAttributePropertyValueWithName(Name);
		return SetAttributePropertyValue(Name, OldValue + Delta, bUpdateUI);
	}
	return true;
}

bool UXAttributeComponent::SetAttributePropertyValue(EAttributePropertyName Name, float NewValue, bool bUpdateUI)
{
	if (AttributeProperties.Contains(Name))
	{
		FAttributePropertyValue CurrentValue = GetAttributePropertyStructWithName(Name);
		CurrentValue.Current = FMath::Clamp(NewValue, CurrentValue.Min, CurrentValue.Max);
		AttributeProperties.Add(Name, CurrentValue);
	}
	return false;
}
bool UXAttributeComponent::SetDefaultHealth(float _MaxHealth)
{
	MaxHealth = _MaxHealth;
	CurrentHealth = _MaxHealth;

	return true;
}

bool UXAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultipiler = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultipiler;
	}

	float OldHealth = CurrentHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealth);

	float ActualDelta = CurrentHealth - OldHealth;

	if (ActualDelta != 0.0f)
	{
		MulticastHealthChanged(InstigatorActor, CurrentHealth, ActualDelta);
	}
	
	//OnHealthChanged.Broadcast(InstigatorActor, this, MaxHealth, CurrentHealth, ActualDelta);

	if (ActualDelta < 0.0f && CurrentHealth == 0.0f)
	{
		AXGameModeBase* GM = Cast<AXGameModeBase>(GetWorld()->GetAuthGameMode<AXGameModeBase>());
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0;
}

void UXAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, MaxHealth, NewHealth, Delta);
}


void UXAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXAttributeComponent, CurrentHealth);
	DOREPLIFETIME(UXAttributeComponent, MaxHealth);

	//DOREPLIFETIME_CONDITION(UXAttributeComponent, MaxHealth, COND_InitialOnly);
}