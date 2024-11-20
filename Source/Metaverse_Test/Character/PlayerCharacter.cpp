// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerCharacter.h"
#include "../System/YutJudgmentSystem.h"

void APlayerCharacter::InitializeSubjectSkills(int B, int D, int S, int N, int O, int E) {
	BasicMagicPoint = B;
	DefenseMagicPoint = D;
	SomaticMagicPoint = S;
	NatureMagicPoint = N;
	OrientalMedicinePoint = O;
	ExplorationMagicPoint = E;
}

bool APlayerCharacter::JudgmentSubject(SubjectClass SkillSubject)
{
	YutJudgmentSystem* System = new YutJudgmentSystem;
	
	switch (SkillSubject)
	{
	case BasicMagic:
		return System->YutJudgingDefault(BasicMagicPoint);
		break;
	case DefenseMagic:
		return System->YutJudgingDefault(DefenseMagicPoint);
		break;
	case ExplorationMagic:
		return System->YutJudgingDefault(ExplorationMagicPoint);
		break;
	case NatureMagic:
		return System->YutJudgingDefault(NatureMagicPoint);
		break;
	case OrientalMedecine:
		return System->YutJudgingDefault(OrientalMedicinePoint);
		break;
	case SomaticMagic:
		return System->YutJudgingDefault(SomaticMagicPoint);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Fail to Use SKILL!"))
		break;
	}
	return false;
}
