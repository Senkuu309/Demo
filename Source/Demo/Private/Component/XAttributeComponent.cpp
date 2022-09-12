// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttributeComponent.h"

// Sets default values for this component's properties
UXAttributeComponent::UXAttributeComponent()
{
	//Health = 100;
}

bool UXAttributeComponent::SetDefaultHealth(float DefaultHealth)
{
	Health = DefaultHealth;
	
	return true;
}

bool UXAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	return true;
}
