// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PromptDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPromptData: public FTableRowBase {
	GENERATED_BODY()

public:
	FPromptData() : KeyValue("SP_0"), PromptRole("Role"){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString KeyValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString PromptRole;
};
