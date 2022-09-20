// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/XComponentTypes.h"
#include "XAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, UXAttributeComponent*, OwningComp, float, maxHealth, float, newHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeProperty")
	TMap<EAttributePropertyName, FAttributePropertyValue> AttributeProperties;
	
public:	

	UXAttributeComponent();

	UFUNCTION()
	static bool IsActorAlive(AActor* FromActor);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FAttributePropertyValue& GetAttributePropertyStructWithName(EAttributePropertyName Name);

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetAttributePropertyValueWithName(EAttributePropertyName Name);

	//血量变化组件
	UFUNCTION(BlueprintCallable)
	bool ModifyAttributePropertyValue(EAttributePropertyName Name, float Delta, bool bUpdateUI);

	UFUNCTION(BlueprintCallable)
	bool SetAttributePropertyValue(EAttributePropertyName Name, float NewValue, bool bUpdateUI);

	UFUNCTION(BlueprintCallable)
	bool isAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION()
	bool SetDefaultHealth(float _MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

};
