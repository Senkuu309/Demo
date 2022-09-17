// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttributeComponent.h"

bool UXAttributeComponent::isAlive() const
{
	return CurrentHealth > 0.0f;
}

// Sets default values for this component's properties
UXAttributeComponent::UXAttributeComponent()
{
	//Health = 100;
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

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
	CurrentHealth += Delta;

	OnHealthChanged.Broadcast(nullptr, this, MaxHealth, CurrentHealth, Delta);

	return true;
}
