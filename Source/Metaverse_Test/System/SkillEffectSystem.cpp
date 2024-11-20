// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SkillEffectSystem.h"


// Sets default values
ASkillEffectSystem::ASkillEffectSystem(){
    static ConstructorHelpers::FClassFinder<AActor> AttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/AttackEffect.AttackEffect")); // �������Ʈ ���
    if (AttackEffectClass.Succeeded()){
        AttackEffect = AttackEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> HealEffectClass(TEXT("/Game/BattleMap/SkillEffect/DepenseEffect.DepenseEffect_C")); // �������Ʈ ���
    if (HealEffectClass.Succeeded()){
        HealEffect = HealEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<AActor> DefenseEffectClass(TEXT("/Game/BattleMap/SkillEffect/HealEffect.HealEffect_C")); // �������Ʈ ���
    if (DefenseEffectClass.Succeeded()){
        DefenseEffect = DefenseEffectClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APaperZDCharacter> MonsterAttackEffectClass(TEXT("/Game/BattleMap/SkillEffect/MonsterSkill.MonsterSkill")); // �������Ʈ ���
    if (MonsterAttackEffectClass.Succeeded()){
        MonsterAttackEffect = MonsterAttackEffectClass.Class;
    }
}

void ASkillEffectSystem::SpawnPlayerAttackEffect(){
    if (AttackEffect){  // ��ȿ�� ���� Ŭ������ ������ ��쿡�� ����
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // ������ ��ġ�� ȸ���� ����
        FVector SpawnLocation = FVector(350, -240, 218);
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

void ASkillEffectSystem::SpawnPlayerDefenseEffect(){
}

void ASkillEffectSystem::SpawnMonsterAttackEffect() {
    if (MonsterAttackEffect) {  // ��ȿ�� ���� Ŭ������ ������ ��쿡�� ����
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        // ������ ��ġ�� ȸ���� ����
        FVector SpawnLocation = FVector(350,-240,600);
        FRotator SpawnRotation = GetActorRotation();

        // ���忡�� ���͸� ����
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(MonsterAttackEffect, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor) {
            // 1.5�� �ڿ� �ڵ����� ��������� ���� ����
            SpawnedActor->SetLifeSpan(1.5f);
        }
    }
    else {
        return;
    }
}