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

	//�ý��� �δ�(����)
	class ABattleSystem* LoadedSystem;
	void CallSystem();

	//��ų ����
	UFUNCTION(BlueprintCallable, Category = "SkillSelect")
	void MappingSkills(SubjectClass Subject, int RowNum);

	//��ų ���� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(BindWidgetOptional))
	class UImage* Success;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Fail;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsSkillSucceed;

	//���� �¸� �й� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Win;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
	class UImage* Lose;

	void ShowPassFailCutIn(bool IsSucceed);
};
