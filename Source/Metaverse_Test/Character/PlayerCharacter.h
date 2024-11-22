// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 ���� ���� ������ ����� �÷��̾� ĳ���Ϳ� ���� ������ ��� ����.
 */
UCLASS()
class METAVERSE_TEST_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
protected:
	int BasicMagicPoint;
	int DefenseMagicPoint;
	int SomaticMagicPoint;
	int NatureMagicPoint;
	int OrientalMedicinePoint;
	int ExplorationMagicPoint;

public:
	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void InitializeSubjectSkills(int B, int D, int S, int N, int O, int E);

	//Judgment
	bool JudgmentSubject(SubjectClass SkillSubject);

	//Get Subject Skill Amount
	int GetSubjectSkills(SubjectClass SkillSubject);
};
