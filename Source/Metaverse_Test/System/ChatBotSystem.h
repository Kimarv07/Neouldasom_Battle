<<<<<<< Updated upstream
// Fill out your copyright notice in the Description page of Project Settings.

=======
>>>>>>> Stashed changes
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
<<<<<<< Updated upstream
#include "Http.h"
#include "Json.h"
#include "ChatBotSystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class METAVERSE_TEST_API UChatBotSystem : public UObject
=======
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Json.h"
#include "ChatBotSystem.generated.h"


// �������Ʈ���� ����� ��������Ʈ ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatBotResponseReceived, const FString&, Response);

/**
 * ChatBot �ý��� Ŭ����
 */
UCLASS(Blueprintable)
class UChatBotSystem : public UObject
>>>>>>> Stashed changes
{
	GENERATED_BODY()
	
public:
<<<<<<< Updated upstream
	UChatBotSystem();

	//�޽����� �����ϰ� ������ ó����
	UFUNCTION(BlueprintCallable, Category = "ChatBotSystem")
	void SendMessageToOpenAI(const FString& Message);
=======
    // ������
    UChatBotSystem();

    // API Ű�� ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChatBot")
    FString ApiKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChatBot")
    FString Model;
    // ������Ʈ�� FText�� �����ϰ� ��Ƽ���� �Է��� �����ϰ� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChatBot")
    FString Prompt;

    // ������Ʈ�� �����ϴ� �Լ�
    UFUNCTION(BlueprintCallable, Category = "ChatBot")
    void SetPrompt(const FString& NewPrompt);

    // ����� �޽��� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "ChatBot")
    void SendMessageToOpenAI(const FString& Message);
>>>>>>> Stashed changes

    // OpenAI�� ������ �������Ʈ�� �����ϴ� ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "ChatBot")
    FOnChatBotResponseReceived OnChatBotResponseReceived;

private:
<<<<<<< Updated upstream
	//HTTP ��û �ʱ�ȭ
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed);

	//HTTP ��û�� ��ü
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;

	//API�� Key �� ����
	FString ApiKey;
	FString Model;
};
=======
    // ���� ó�� �Լ�
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // HTTP ��û ��ü
    TSharedPtr<IHttpRequest> HttpRequest;
};
>>>>>>> Stashed changes
