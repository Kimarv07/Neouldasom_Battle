#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

{
	GENERATED_BODY()
	
public:
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

    // OpenAI�� ������ �������Ʈ�� �����ϴ� ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "ChatBot")
    FOnChatBotResponseReceived OnChatBotResponseReceived;

private:
    // ���� ó�� �Լ�
    void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

    // HTTP ��û ��ü
    TSharedPtr<IHttpRequest> HttpRequest;
};
