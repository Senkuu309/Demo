// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/XComponentTypes.h"
#include "XCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UXInteractionComponent;
class UXAttributeComponent;
class UXAttackComponent;
class UXWorldUserWidget;
class UXActionComponent;

UCLASS(Abstract)
class DEMO_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion")
	bool Movable = true;

public:

	//相机臂组件
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	//相机组件
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	//交互组件
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UXInteractionComponent* InteractComp;

	//血量组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttributeComponent* AttributeComp;

	//攻击组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttackComponent* AttackComp;

	//武器组件
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* WeaponComp;

	//动作组件
	//攻击组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXActionComponent* ActionComp;

	//武器位置
	UPROPERTY(VisibleAnywhere)
	FVector WeaponLocation1;

	UPROPERTY(VisibleAnywhere)
	FVector WeaponLocation2;

	UPROPERTY(VisibleAnywhere)
	FVector WeaponLocation3;


public:	

	UXWorldUserWidget* ActiveHealthBar;

	UUserWidget* HUD_Main;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUD_MainClass;

	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	//冲刺
	void SprintStart();

	void SprintStop();

	//左键攻击
	virtual void MBLAttack();

	//右键攻击
	virtual void MBRAttack();

	//额外技能
	virtual void ExtraSkill();

	void PrimaryInteract();

	//角色死亡
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UXAttributeComponent* OwningComp, float maxHealth, float newHealth, float Delta);

	UFUNCTION()
	void OnAttacking(AActor* InstigatorActor, UXAttackComponent* OwningComp, FAttackStruct CurrentSkill);

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);
	
	void PostInitializeComponents();

	FVector GetPawnViewLocation() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
