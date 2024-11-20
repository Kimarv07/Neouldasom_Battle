// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "Json.h"
#include "../PromptDataTable.h"
#include "BattleChatBotSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class METAVERSE_TEST_API UBattleChatBotSystem : public UObject
{
	GENERATED_BODY()
	
private:
	UBattleChatBotSystem(const FObjectInitializer& ObjectInitializer);
	

	//메시지를 전송하고 응답을 처리함
	UFUNCTION(BlueprintCallable, Category = "ChatBotSystem")
	void SendMessageToOpenAI(const FString& Message);

	//프롬프팅 메세지
	FString PromptMessage;
	
	//Prompt Data Table
	UDataTable* PromptData;

	//Prompt Message Data
	FPromptData* MessageData;
public:
	UFUNCTION(BlueprintCallable, Category = "BattleChatbot")
	//스킬 정보 받은 후 프롬프팅
	void SetPromptMessage(FString SkillDetail);

	//role 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prompt")
	FString RoleMessage;

private:
	//HTTP 요청 초기화
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed);

	//HTTP 요청용 객체
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;

	//API와 Key 모델 설정
	FString ApiKey;
	FString Model;

	//GPT 응답 저장
	FString AssistantResponseText;
	//GPT 응답 가져오기
public:
	FString GetResponse() const;
};
