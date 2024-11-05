#include "ChatBotSystem.h"


// ������: API Ű�� ���� �ʱ�ȭ�մϴ�.
UChatBotSystem::UChatBotSystem()
{
    ApiKey = ""; // OpenAI API Ű�� �Է�
    Model = "gpt-4o"; // ����� �� �̸� ����
    Prompt = "�� ������� �б� ��ȭ�д翡�� �⺻������ ����ġ�� ���� �����̾�. "; // ������Ʈ ����
}

// ������Ʈ�� �����ϴ� �Լ�
void UChatBotSystem::SetPrompt(const FString& NewPrompt)
{
    Prompt = NewPrompt;
}

// ����� �޽����� ������Ʈ�� OpenAI�� �����ϴ� �Լ�
void UChatBotSystem::SendMessageToOpenAI(const FString& Message)
{
    HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UChatBotSystem::OnResponseReceived);

    HttpRequest->SetURL("https://api.openai.com/v1/chat/completions");
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetHeader("Authorization", FString::Printf(TEXT("Bearer %s"), *ApiKey));

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("model", Model);

    TArray<TSharedPtr<FJsonValue>> Messages;
    TSharedPtr<FJsonObject> PromptMessage = MakeShareable(new FJsonObject);
    PromptMessage->SetStringField("role", "system");
    PromptMessage->SetStringField("content", Prompt); // Prompt�� FString���� ��ȯ
    Messages.Add(MakeShareable(new FJsonValueObject(PromptMessage)));

    TSharedPtr<FJsonObject> UserMessage = MakeShareable(new FJsonObject);
    UserMessage->SetStringField("role", "user");
    UserMessage->SetStringField("content", Message);
    Messages.Add(MakeShareable(new FJsonValueObject(UserMessage)));

    JsonObject->SetArrayField("messages", Messages);

    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    HttpRequest->SetContentAsString(RequestBody);

    HttpRequest->ProcessRequest();
}

// OpenAI�� ������ ó���ϴ� �Լ�
void UChatBotSystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
        TSharedPtr<FJsonObject> JsonResponse;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonResponse))
        {
            FString AssistantResponse = JsonResponse->GetArrayField("choices")[0]
                ->AsObject()->GetObjectField("message")->GetStringField("content");

            OnChatBotResponseReceived.Broadcast(AssistantResponse);

            UE_LOG(LogTemp, Log, TEXT("ChatBot Response: %s"), *AssistantResponse);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Request failed: %s"), *Response->GetContentAsString());
    }
}
