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

	//��������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	//������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	//�������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UXInteractionComponent* InteractComp;

	//Ѫ�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttributeComponent* AttributeComp;

	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttackComponent* AttackComp;

	//�������
	UPROPERTY(BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* WeaponComp;

	//�������
	//�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXActionComponent* ActionComp;

	//����λ��
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

	//���
	void SprintStart();

	void SprintStop();

	//�������
	virtual void MBLAttack();

	//�Ҽ�����
	virtual void MBRAttack();

	//���⼼��
	virtual void ExtraSkill();

	void PrimaryInteract();

	//��ɫ����
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
