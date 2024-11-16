// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/PlayerCharacter.h"
#include "../Character/MonsterCharacter.h"
#include "SkillDataTable.h"
#include "SkillSystem.h"
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
	//UFUNCTION(BlueprintCallable, Category = "SystemSet")
	//void SetBattleNpcs(APlayerCharacter* Entity1, AMonsterCharacter* Entity2);

	//Set Skills
	SkillSystem LoadSkillSystem;

	//Set Battle turn
	UFUNCTION(BlueprintCallable, Category = "BattleTurn")
	void BattleTurnPlayer();
	UFUNCTION(BlueprintCallable, Category = "BattleTurn")
	void BattleTurnEnemy();
public:
	void EndTurn();

	bool IsPlayerTurn;

protected:
	//Actor
	APlayerCharacter* PlayerEntity;
	AMonsterCharacter* MonsterEntity;

	UDataTable* MonsterSkillData;

public:
	//Save CurSkillData
	SubjectClass SkillClass;
	FSkillInfo* MonsterSkill;
	FSkillInfo* CurSkill;
	int CurSubjectPoint;
	int DependedDamage;
	bool IsSkillSucceed;
	bool GetSkillIsSucceed();

	//System
	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SkillSystem(SubjectClass Subject, int RowNum);

protected:
	//플레이어 스킬
	void AttackSkill();
	void DepenseSkill();
	void HealSkill();
	void SupportSkill();
	void PracticalSkill();

	//몬스터 스킬
	void MonsterAttack();
	void MonsterDepense();

	//DebugLog
	void ShowDebugLog();
};
