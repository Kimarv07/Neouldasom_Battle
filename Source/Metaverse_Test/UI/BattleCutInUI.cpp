// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleCutInUI.h"

UBattleCutInUI::UBattleCutInUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer) {

	Success = Cast<UImage>(GetWidgetFromName(TEXT("Success")));
	Fail = Cast<UImage>(GetWidgetFromName(TEXT("Fail")));
}

void UBattleCutInUI::ShowPassFailCutIn(bool IsSucceed) {
	FTimerHandle CutInTimerHnadle;

	if (IsSucceed) {
		Success->SetVisibility(ESlateVisibility::Visible);
	}
	else if (!IsSucceed) {
		Fail->SetVisibility(ESlateVisibility::Visible);
	}
}