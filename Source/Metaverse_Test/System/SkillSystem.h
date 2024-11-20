// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YutJudgmentSystem.h"
#include "SkillDataTable.h"

/**
SkillSystem
 */
 
UENUM()
enum EhList {
	BI_2,
	BI_3,
	BA_1,
	BA_2,
	DA_1,
	NA_1A,
	NA_1D,
	NA_1H,
	OA_1,
	OA_2,
	DI_1,
	DI_2,
	DA_2,
	NI_1A,
	SB_1A,
	SB_1D,
	SB_2,
	SB_3,
	SI_1,
	SI_3,
	SA_1,
	SA_2,
	SA_3,
	OI_2,
	M1_1
};

class APlayerCharacter;
class AMonsterCharacter;

class METAVERSE_TEST_API SkillSystem
{
public:
	//Constructor
	SkillSystem();

	//Load DataTable
	void DataLoder();

	//Data Table
	UDataTable* BasicSkillData;
	UDataTable* DefenseSkillData;
	UDataTable* ExplorationSkillData;
	UDataTable* NatureSkillData;
	UDataTable* MedecineSkillData;
	UDataTable* SomaticSkillData;
	UDataTable* MonsterSkillData;

	//Find Skill
	FSkillInfo* FindPlayerSkill(SubjectClass Subject, int RowNum);

	//
	void ExecuteSkill(APlayerCharacter* User, AMonsterCharacter* Target, FSkillInfo* Skill);

	int CostMp;
	int Amount;

	//예외처리 함수
	int MpExceptionHandling(FSkillInfo* SkillRow);
	int AmountExceptionHandling(FSkillInfo* SkillRow);

	class YutJudgmentSystem LoadedSystem;

	int SetByPlayerChoice();
	int SetBySubjectClass();
	int SetByJudgement();
	int SetByHp();
	int SetByMp();
};


