// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BattleCutInUI.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_TEST_API UBattleCutInUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBattleCutInUI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Success;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Fail;

	void ShowPassFailCutIn(bool IsSucceed);
};
