// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PlayerCharacter.h"
#include "../Character/MonsterCharacter.h"
#include "SkillDataTable.h"
#include "SkillSystem.h"
#include "SkillEffectSystem.h"
#include "BattleSystem.generated.h"

UCLASS()
class METAVERSE_TEST_API ABattleSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Constructor
	ABattleSystem();

protected:
	virtual void BeginPlay() override;

	//Show Total Monster's Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalDamage; 

	UPROPERTY(EditAnywhere, Category="Widget")
	TSubclassOf<UUserWidget> DamageWidgetClass;

	class Widget* DamageWidget;

	//Set BattleTurn
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsBattleOver; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BattleRound;

	void IsEndGame();

	//Set Actors
	UFUNCTION(BlueprintCallable, Category = "SystemSet")
	void SetBattleEntities(APlayerCharacter* Entity1, AMonsterCharacter* Entity2);

	//Set NPC Actors
	UFUNCTION(BlueprintCallable, Category = "SystemSet")
	void SetBattleNpcs(APlayerCharacter* Entity1, APlayerCharacter* Entity2);
	
	//NPC 미 존재시 예외처리용 bool 값
	bool IsNpcUsed;

	//Set Skills
	class SkillSystem LoadSkillSystem;

	//Set Battle turn

	//Set Player Turn
	void BattleTurnPlayer();

	//Set Enemy Turn
	void BattleTurnEnemy();

	//Set NPC Turn
	void BattleTurnNpc();

public:
	void EndTurn();

	bool IsPlayerTurn;

protected:
	//Actor
	APlayerCharacter* PlayerEntity;
	AMonsterCharacter* MonsterEntity;

	//Bind Npc Actors
	APlayerCharacter* NpcEntity1;
	APlayerCharacter* NpcEntity2;

	UDataTable* MonsterSkillData;

public:
	//Save CurSkillData
	SubjectClass SkillClass;
	//MonsterSkillData
	FSkillInfo* MonsterSkill;
	//MonsterSkillPoint 몬스터 스킬 성공 확률
	int MonsterJudgeLimit;
	//PlayerSkillData
	FSkillInfo* CurSkill;
	//PlayerSkillSubjectPoint 플레이어 과목기능치
	int CurSubjectPoint;


	int DependedDamage;
	bool IsSkillSucceed;
	bool GetSkillIsSucceed();

	//System
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SkillSystem(SubjectClass Subject, int RowNum);

protected:
	class ASkillEffectSystem* EffectSystem;

	//플레이어 스킬
	void AttackSkill();
	void DepenseSkill();
	void HealSkill();
	void SupportSkill();
	void PracticalSkill();

	//몬스터 스킬
	void MonsterAttack();
	void MonsterDepense();

	//NPC 스킬
	void NpcAttack();
	void NpcHeal();

	//DebugLog
	void ShowDebugLog();
};
