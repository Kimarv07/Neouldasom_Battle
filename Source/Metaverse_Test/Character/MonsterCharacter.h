// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "MonsterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_TEST_API AMonsterCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
private:
	AMonsterCharacter();

public:
	bool JudgmentSkill(int score);

	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void SetHpByPlayer(int HpMax);
	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void SetMpByPlayer(int MpMax);
};
