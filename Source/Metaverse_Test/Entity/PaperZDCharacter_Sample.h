// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PaperZDCharacter_Sample.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class METAVERSE_TEST_API APaperZDCharacter_Sample : public APaperZDCharacter
{
	GENERATED_BODY()
protected:

public:
	APaperZDCharacter_Sample();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Humanity; //�ν�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Desire; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Courtesy; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Wisdom; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Fortune; //õ��


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hp; //ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Mp; //����

	//Initialize: Function for initialize entities information
	UFUNCTION(BlueprintCallable, Category = "Initialize")
	void InitializeInfo(int H, int D, int C, int W, int F);

	//GetInfo: Function for get entities fluctuating information
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetHP();
	UFUNCTION(BlueprintCallable, Category = "GetInfo")
	int GetMP();

	//SetInfo: Function for Set entities fluctuating information
	UFUNCTION(BlueprintCallable, Category = "SetInfo")
	void SetHP(int HpMount);
	UFUNCTION(BlueprintCallable, Category = "SetInfo")
	void SetMP(int MpCost);

	virtual void BeginPlay() override;
};
