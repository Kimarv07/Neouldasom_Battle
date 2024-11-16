// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePlayerController.generated.h"

/**
 * 
 */

UCLASS()
class METAVERSE_TEST_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected: 
	ABattlePlayerController();

	void BeginPlay() override;

	//Setting HUD
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CutInWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	UUserWidget* CutInWidget;

	void CreateHUD();
};
