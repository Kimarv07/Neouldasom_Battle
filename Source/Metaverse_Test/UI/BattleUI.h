// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../System/BattleSystem.h"
#include "Components/Image.h"
#include "BattleUI.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_TEST_API UBattleUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UBattleUI(const FObjectInitializer &ObjectInitializer);

	//시스템 로더(연동)
	class ABattleSystem* LoadedSystem;
	void CallSystem();

	//스킬 적용
	UFUNCTION(BlueprintCallable, Category = "SkillSelect")
	void MappingSkills(SubjectClass Subject, int RowNum);

	//스킬 성공 실패 컷인
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidgetOptional))
	class UImage* Success;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Fail;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSkillSucceed;

	//전투 승리 패배 컷인
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Win;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Lose;

	void ShowPassFailCutIn(bool IsSucceed);
};
