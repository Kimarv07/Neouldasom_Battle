// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PlayerCharacter.h"
#include "../Character/MonsterCharacter.h"
#include "SkillDataTable.h"
#include "SkillSystem.h"
#include "AI System/BattleChatBotSystem.h"
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
	
	//NPC �� ����� ����ó���� bool ��
	bool IsNpcUsed;

	//Set Skills
	class SkillSystem LoadSkillSystem;

	//ChatBotSystem for Battle
	UBattleChatBotSystem* ChatBotSystem;

	//Set Battle turn

	//Set Player Turn
	void BattleTurnPlayer();

	//Ready for Monster Turn
	void SetEnemySkill();
	//Set Enemy Turn
	void BattleTurnEnemy();

	//Set NPC Turn
	void BattleTurnNpc();

public:
	void EndTurn();

	bool IsPlayerTurn;

protected:
	//Player Actor
	APlayerCharacter* PlayerEntity;
	//Monster Actor
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
	//MonsterSkillPoint ���� ��ų ���� Ȯ��
	int MonsterJudgeLimit;
	//PlayerSkillData
	FSkillInfo* CurSkill;
	//PlayerSkillSubjectPoint �÷��̾� ������ġ
	int CurSubjectPoint;
	//���ġ
	int DefendedDamage;
	//��ų ��������
	bool IsSkillSucceed;
	//��ų �������� ��ȯ
	bool GetSkillIsSucceed();

	//System
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SkillSystem(SubjectClass Subject, int RowNum);

protected:


	//�÷��̾� ��ų
	void AttackSkill();
	void DefenseSkill();
	void HealSkill();
	void SupportSkill();
	void PracticalSkill();

	//���� ��ų
	void MonsterAttack();
	void MonsterDepense();

	//NPC ��ų
	void NpcAttack();
	void NpcHeal();

	//DebugLog
	void ShowDebugLog();
};
