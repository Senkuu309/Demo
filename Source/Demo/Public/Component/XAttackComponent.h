// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XComponentTypes.h"
#include "XAttackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttacking, AActor*, InstigatorActor, UXAttackComponent*, OwningComp, FAttackStruct,CurrentSkill);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TMap<FName,FAttackStruct> AttackSkillData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	FAttackStruct CurrentSkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	bool isAttacking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	bool SaveAttack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	EInputType InputBuffer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TMap<EInputType, FName> SkillList;

public:	
	UXAttackComponent();

	UFUNCTION(BlueprintCallable)
	void SkillInput(EInputType InputType);

	UFUNCTION(BlueprintCallable)
	void ComboEnd();

	UPROPERTY(BlueprintAssignable)
	FOnAttacking OnAttacking;


	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
