// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/XComponentTypes.h"
#include "XAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, UXAttributeComponent*, OwningComp, float, MaxHealth, float, CurrentHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attribute")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attribute")
	float CurrentHealth;

	//UPROPERTY(ReplicatedUsing = "")
	//bool bIsAlive;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChanged(AActor * InstigatorActor, float NewHealth, float Delta);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	TMap<EAttributePropertyName, FAttributePropertyValue> AttributeProperties;
	
public:	
	UXAttributeComponent();

	UFUNCTION(BlueprintCallable)
	static UXAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable)
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
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable)
	bool isAlive() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION()
	bool SetDefaultHealth(float _MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

};
