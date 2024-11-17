// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "Json.h"
#include "BattleChatBotSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class METAVERSE_TEST_API UBattleChatBotSystem : public UObject
{
	GENERATED_BODY()
	
private:
	UBattleChatBotSystem();
	

	//�޽����� �����ϰ� ������ ó����
	UFUNCTION(BlueprintCallable, Category = "ChatBotSystem")
	void SendMessageToOpenAI(const FString& Message);

	//role ����
	FString RoleMessage;

	//�������� �޼���
	FString PromptMessage;

	UFUNCTION(BlueprintCallable, Category = "BattleChatbot")
	//��ų ���� ���� �� ��������
	void SetPromptMessage(FString SkillDetail);

private:
	//HTTP ��û �ʱ�ȭ
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed);

	//HTTP ��û�� ��ü
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;

	//API�� Key �� ����
	FString ApiKey;
	FString Model;

	//GPT ���� ����
	FString AssistantResponseText;
	//GPT ���� ��������
	FString GetReponse() const;
};
