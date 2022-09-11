// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UXInteractionComponent;

UCLASS()
class DEMO_API AXCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	//ħ��
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AXCharacter();

protected:

	//��������
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	//������
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//�������
	UPROPERTY(VisibleAnywhere)
	UXInteractionComponent* InteractComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void PrimaryAttack();

	void PrimaryInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
