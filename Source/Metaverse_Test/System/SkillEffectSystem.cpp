// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SkillEffectSystem.h"


// Sets default values
ASkillEffectSystem::ASkillEffectSystem(){
    static ConstructorHelpers::FClassFinder<AActor> AttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/AttackEffect.AttackEffect")); // 블루프린트 경로
    if (AttackEffectClass.Succeeded()){
        AttackEffect = AttackEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> HealEffectClass(TEXT("/Game/BattleMap/SkillEffect/DepenseEffect.DepenseEffect_C")); // 블루프린트 경로
    if (HealEffectClass.Succeeded()){
        HealEffect = HealEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> DefenseEffectClass(TEXT("/Game/BattleMap/SkillEffect/HealEffect.HealEffect_C")); // 블루프린트 경로
    if (DefenseEffectClass.Succeeded()){
        DefenseEffect = DefenseEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APaperZDCharacter> MonsterAttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/MonsterSkill.MonsterSkill")); // 블루프린트 경로
    if (MonsterAttackEffectClass.Succeeded()){
        MonsterAttackEffect = MonsterAttackEffectClass.Class;
    }
}

void ASkillEffectSystem::SpawnPlayerAttackEffect(){
    if (AttackEffect){  // 유효한 액터 클래스가 설정된 경우에만 스폰
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // 스폰할 위치와 회전값 설정
        FVector SpawnLocation = FVector(350, -240, 218);
        FRotator SpawnRotation = GetActorRotation();

        // 월드에서 액터를 스폰
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AttackEffect, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor){
            // 1.5초 뒤에 자동으로 사라지도록 수명 설정
            SpawnedActor->SetLifeSpan(1.5f);
        }
    }
}

void ASkillEffectSystem::SpawnPlayerHealEffect(){
}

void ASkillEffectSystem::SpawnPlayerDefenseEffect(){
}

void ASkillEffectSystem::SpawnMonsterAttackEffect() {
    if (MonsterAttackEffect) {  // 유효한 액터 클래스가 설정된 경우에만 스폰
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // 스폰할 위치와 회전값 설정
        FVector SpawnLocation = FVector(350,-240,600);
        FRotator SpawnRotation = GetActorRotation();

        // 월드에서 액터를 스폰
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterAttackEffect, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor) {
            // 1.5초 뒤에 자동으로 사라지도록 수명 설정
            SpawnedActor->SetLifeSpan(1.5f);
        }
    }
    else {
        return;
    }
}