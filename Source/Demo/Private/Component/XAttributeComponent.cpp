// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttributeComponent.h"

// Sets default values for this component's properties
UXAttributeComponent::UXAttributeComponent()
{
	//Health = 100;
}

bool UXAttributeComponent::SetDefaultHealth(float _MaxHealth, float _CurrentHealth)
{
	MaxHealth = _MaxHealth;
	CurrentHealth = _CurrentHealth;
	
	return true;
}

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
	CurrentHealth += Delta;

	OnHealthChanged.Broadcast(nullptr, this, MaxHealth, CurrentHealth, Delta);

	return true;
}
