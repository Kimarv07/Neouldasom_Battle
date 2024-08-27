// Fill out your copyright notice in the Description page of Project Settings.


#include "Control/BattlePlayerController.h"
#include "Blueprint/UserWidget.h"

ABattlePlayerController::ABattlePlayerController(){
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/BattleMap/SampleButton/MyBattleUI.MyBattleUI_C"));
    if (WidgetClassFinder.Succeeded())
    {
        HUDWidgetClass = WidgetClassFinder.Class;
    }
}

void ABattlePlayerController::BeginPlay(){
	Super::BeginPlay();

    // ���콺 Ŀ���� �׻� ���̵��� ����
    bShowMouseCursor = true;

    // �Է� ��带 ���Ӱ� UI�� ��� ����� �� �ֵ��� ����
    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // �ʿ信 ���� ���콺 �� ��� ���� ����
    SetInputMode(InputMode);
	CreateHUD();
} 

void ABattlePlayerController::CreateHUD(){
    HUDWidget = CreateWidget(GetWorld()->GetFirstPlayerController(), HUDWidgetClass);
    HUDWidget->AddToViewport();
}
