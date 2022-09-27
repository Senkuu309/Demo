// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "XGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "AutoLoadPrimary")
	TArray<FPrimaryAssetType> AutoLoadTypes;

	virtual void Init() override;
};
