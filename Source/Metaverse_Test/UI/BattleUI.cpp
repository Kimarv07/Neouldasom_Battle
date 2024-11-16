// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BattleUI.h"
#include "Kismet/GameplayStatics.h"


UBattleUI::UBattleUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer){
	Success = Cast<UImage>(GetWidgetFromName(TEXT("Success")));
	Fail = Cast<UImage>(GetWidgetFromName(TEXT("Fail")));
	Win = Cast<UImage>(GetWidgetFromName(TEXT("Success")));
	Lose = Cast<UImage>(GetWidgetFromName(TEXT("Fail")));
}

void UBattleUI::CallSystem(){
	if (!LoadedSystem) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABattleSystem::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0) {
			LoadedSystem = Cast<ABattleSystem>(FoundActors[0]);
		}
	}
}

void UBattleUI::MappingSkills(SubjectClass Subject, int RowNum){
	if (!LoadedSystem) {
		CallSystem();
	}

	LoadedSystem->SkillSystem(Subject, RowNum);
	ShowPassFailCutIn(LoadedSystem->GetSkillIsSucceed());
	IsSkillSucceed = LoadedSystem->GetSkillIsSucceed();
	LoadedSystem->EndTurn();
}

//성공/실패 여부 확인 가능한 컷인
void UBattleUI::ShowPassFailCutIn(bool IsSucceed){
	FTimerHandle CutInTimerHnadle;

	if (IsSucceed) {
 		Success->SetVisibility(ESlateVisibility::Visible);
	}
	else if(!IsSucceed) {
		Fail->SetVisibility(ESlateVisibility::Visible);
	}


}
