// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "../System/SkillDataTable.h"
#include "../System/YutJudgmentSystem.h"
#include "CharacterBase.generated.h"

/**
 * 
 */

UCLASS()
class METAVERSE_TEST_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Humanity; //인심
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Desire; //의지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Courtesy; //예절
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Wisdom; //지혜
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Fortune; //천운

	int Hp; //체력
	int Mp; //도력

	int HpLimit; //체력 상한치
	int MpLimit; //도력 상한치

	//Initialize: Function for initialize entities information
	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void InitializeInfo(int H, int D, int C, int W, int F);

	//GetInfo: Function for get entities fluctuating information
	//Get Cur HP
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetHP();
	//Get Max HP
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetMaxHP();
	//Get Cur MP
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetMP();
	//Get Max MP
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetMaxMP();

	//SetInfo: Function for Set entities fluctuating information
	UFUNCTION(BlueprintCallable, Category = "SetInfo")
	void SetHP(int HpMount);
	UFUNCTION(BlueprintCallable, Category = "SetInfo")
	void SetMP(int MpCost);
	

	virtual void BeginPlay() override;
};
