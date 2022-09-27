// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XComponentTypes.h"
#include "XAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXAttackComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FAttackStruct NextSkill;

	UFUNCTION()
	void PlayAttackMontage(AActor* Instigator);

	UFUNCTION(Server, Reliable)
	void ServerPlayAnimMontage(AActor* Instigator, EInputType InputType);

	UPROPERTY(ReplicatedUsing = "OnRep_bIsAttack", BlueprintReadOnly)
	bool bIsAttack;

	UFUNCTION()
	void OnRep_bIsAttack();

public:	

	UPROPERTY(Replicated)
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TMap<FName,FAttackStruct> AttackSkillData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	FAttackStruct CurrentSkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, Category = "Attack")
	bool isAttacking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, Category = "Attack")
	bool SaveAttack = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	EInputType InputBuffer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	TMap<EInputType, FName> SkillList;

public:	
	UXAttackComponent();

	UFUNCTION(BlueprintCallable)
	void SkillInput(AActor* Instigator, EInputType InputType);

	UFUNCTION(Server,Reliable, BlueprintCallable)
	void ComboEnd();

	//UPROPERTY(BlueprintAssignable)
	//FOnAttacking OnAttacking;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
