// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XInteractionComponent.h"
#include "Component/XAttributeComponent.h"
#include "Component/XAttackComponent.h"
#include "Component/XActionComponent.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget/XWorldUserWidget.h"

// Sets default values
AXCharacter::AXCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//创建相机臂组件，绑定到角色上
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;  //相机臂旋转
	SpringArmComp->SetupAttachment(RootComponent);
	
	//创建相机组件，绑定到相机臂上
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	//创建交互组件
	InteractComp = CreateDefaultSubobject<UXInteractionComponent>("InteractComp");

	//创建血量组件
	AttributeComp = CreateDefaultSubobject<UXAttributeComponent>("AttributeComp");

	//创建攻击组件
	AttackComp = CreateDefaultSubobject<UXAttackComponent>("AttackComp");

	//创建武器组件
	WeaponComp = CreateDefaultSubobject<UStaticMeshComponent>("WeaponComp");
	WeaponLocation1 = GetMesh()->GetSocketLocation("hand_rSocket");
	WeaponLocation2 = WeaponComp->GetSocketLocation("Mid");
	WeaponLocation3 = WeaponComp->GetSocketLocation("End");

	//创建动作组件
	ActionComp = CreateDefaultSubobject<UXActionComponent>("ActionComp");
}

void AXCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AXCharacter::OnHealthChanged);
}



FVector AXCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called when the game starts or when spawned
void AXCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HUD_Main)
	{
		if (ensure(HUD_MainClass))
		{
			HUD_Main = CreateWidget<UUserWidget>(GetWorld(), HUD_MainClass);
			if (ensure(HUD_Main))
			{
				HUD_Main->AddToViewport();
			}
		}
	}
}

// Called every frame
void AXCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AXCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && Movable)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;

		AddMovementInput(ControlRot.Vector(), value);
	}
	
}

void AXCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && Movable)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0.0f;
		ControlRot.Roll = 0.0f;

		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		AddMovementInput(RightVector, value);
	}
}
	

void AXCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
	
}

void AXCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void AXCharacter::MBLAttack()
{
	AttackComp->SkillInput(EInputType::EPropertyMBL);
}

void AXCharacter::MBRAttack()
{
	AttackComp->SkillInput(EInputType::EPropertyMBR);
}

void AXCharacter::ExtraSkill()
{
	AttackComp->SkillInput(EInputType::EPropertyExtra);
}

void AXCharacter::PrimaryInteract()
{
	if (InteractComp)
	{
		InteractComp->PrimaryInteract();
	}
}

void AXCharacter::OnHealthChanged(AActor* InstigatorActor, UXAttributeComponent* OwningComp, float maxHealth, float newHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (newHealth <= 0.0f)
		{
			APlayerController* PC = Cast<APlayerController>(GetController());
			DisableInput(PC);
		}
	}
}

void AXCharacter::OnAttacking(AActor* InstigatorActor, UXAttackComponent* OwningComp, FAttackStruct CurrentSkill)
{
	PlayAnimMontage(CurrentSkill.AttackAnim);
	OwningComp->isAttacking = true;
	OwningComp->InputBuffer = EInputType::EPropertyNone;
}

void AXCharacter::HealSelf(float Amount)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

// Called to bind functionality to input
void AXCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AXCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AXCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AXCharacter::PrimaryInteract);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AXCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AXCharacter::SprintStop);

	PlayerInputComponent->BindAction("MBL", IE_Pressed, this, &AXCharacter::MBLAttack);
	PlayerInputComponent->BindAction("MBR", IE_Pressed, this, &AXCharacter::MBRAttack);
	PlayerInputComponent->BindAction("ExtraSkill", IE_Pressed, this, &AXCharacter::ExtraSkill);
}