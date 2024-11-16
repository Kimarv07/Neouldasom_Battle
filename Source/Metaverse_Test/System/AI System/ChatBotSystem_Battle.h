// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatBotSystem.h"
#include "ChatBotSystem_Battle.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_TEST_API UChatBotSystem_Battle : public UChatBotSystem
{
	GENERATED_BODY()
	
private:
	UChatBotSystem_Battle();

	FString Result;

	void SendPrompt();
};
