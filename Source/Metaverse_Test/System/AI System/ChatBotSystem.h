// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "Json.h"
#include "ChatBotSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class METAVERSE_TEST_API UChatBotSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UChatBotSystem();

	//메시지를 전송하고 응답을 처리함
	UFUNCTION(BlueprintCallable, Category = "ChatBotSystem")
	void SendMessageToOpenAI(const FString& Message);

private:
	//HTTP 요청 초기화
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed);

	//HTTP 요청용 객체
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;

	//API와 Key 모델 설정
	FString ApiKey;
	FString Model;
};
