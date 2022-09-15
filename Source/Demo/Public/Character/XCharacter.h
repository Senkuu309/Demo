// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UXInteractionComponent;
class UXAttributeComponent;

UCLASS(Abstract)
class DEMO_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion")
	bool Movable = true;


protected:

	//相机臂组件
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//相机组件
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//交互组件
	UPROPERTY(VisibleAnywhere)
	UXInteractionComponent* InteractComp;

	//血量组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttributeComponent* AttributeComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	//左键轻攻击
	virtual void LightAttack() {};

	//右键重攻击
	virtual void HeavyAttack() {};

	//额外技能
	virtual void ExtraSkill() {};

	void PrimaryInteract();

	//角色死亡
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UXAttributeComponent*  OwningComp, float maxHealth, float newHealth, float Delta);

	void PostInitializeComponents();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
