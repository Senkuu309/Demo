// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "XAttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UXAttributeComponent : public USceneComponent
{
	GENERATED_BODY()

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;
	

public:	
	// Sets default values for this component's properties
	UXAttributeComponent();
	UFUNCTION()
	bool SetDefaultHealth(float DefaultHealth);

	//血量变化组件
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

};
