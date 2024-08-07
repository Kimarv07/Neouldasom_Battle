// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfoStruct.generated.h"

/**
 * 
 */

USTRUCT(Atomic, BlueprintType)
struct FEntityInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Humanity; //�ν�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Willingness; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Courtesy; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Wisdom; //����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Fortune; //õ��


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Hp = Willingness + Fortune + 18; //ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Mp = Humanity + Courtesy + Wisdom + 6; //����
};

class METAVERSE_TEST_API InfoStruct
{
public:
	InfoStruct();
	~InfoStruct();
};
