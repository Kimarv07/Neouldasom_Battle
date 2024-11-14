// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SkillEffectSystem.h"

// Sets default values
ASkillEffectSystem::ASkillEffectSystem(){
    static ConstructorHelpers::FClassFinder<AActor> AttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/AttackEffect.AttackEffect_C")); // �������Ʈ ���
    if (AttackEffectClass.Succeeded()){
        AttackEffect = AttackEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> HealEffectClass(TEXT("/Game/BattleMap/SkillEffect/DepenseEffect.DepenseEffect_C")); // �������Ʈ ���
    if (HealEffectClass.Succeeded()){
        HealEffect = HealEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> DepenseEffectClass(TEXT("/Game/BattleMap/SkillEffect/HealEffect.HealEffect_C")); // �������Ʈ ���
    if (DepenseEffectClass.Succeeded()){
        DepenseEffect = DepenseEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> MonsterAttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/MonsterSkillEffect.MonsterSkillEffect_C")); // �������Ʈ ���
    if (MonsterAttackEffectClass.Succeeded()){
        MonsterAttackEffect = MonsterAttackEffectClass.Class;
    }
}

void ASkillEffectSystem::SpawnPlayerAttackEffect(){
    if (AttackEffect){  // ��ȿ�� ���� Ŭ������ ������ ��쿡�� ����
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // ������ ��ġ�� ȸ���� ����
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();

        // ���忡�� ���͸� ����
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AttackEffect, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor){
            // 1.5�� �ڿ� �ڵ����� ��������� ���� ����
            SpawnedActor->SetLifeSpan(1.5f);
        }
    }
}

void ASkillEffectSystem::SpawnPlayerHealEffect(){
}

void ASkillEffectSystem::SpawnPlayerDepenseEffect(){
}

void ASkillEffectSystem::SpawnMonsterAttackEffect() {
}