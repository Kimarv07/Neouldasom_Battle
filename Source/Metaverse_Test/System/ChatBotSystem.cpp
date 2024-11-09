#include "ChatBotSystem.h"


//**������: API Ű�� ���� �ʱ�ȭ�մϴ�.
UChatBotSystem::UChatBotSystem()
{
    ApiKey = ""; // OpenAI API Ű�� �Է�
    Model = "gpt-4o"; // ����� �� �̸� ����
    Prompt = ""; // ������Ʈ ����
}

//**������Ʈ�� �����ϴ� �Լ�
void UChatBotSystem::SetPrompt(const FString& NewPrompt)// ���ο� ������Ʈ(�ʱ� �޽���)�� �����ϴ� �Լ�
{
    Prompt = NewPrompt;    // ������Ʈ�� ���޹��� �� ������Ʈ�� ������Ʈ�մϴ�.
}

//**����� �޽����� ������Ʈ�� OpenAI�� �����ϴ� �Լ�
void UChatBotSystem::SendMessageToOpenAI(const FString& Message)// ����� �޽����� ������Ʈ�� OpenAI ������ �����ϴ� �Լ�
{
    HttpRequest = FHttpModule::Get().CreateRequest(); // HTTP ��û�� �����մϴ�.
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UChatBotSystem::OnResponseReceived);// HTTP ��û �Ϸ� �� ������ ó���ϴ� �ݹ��� �����մϴ�.

    HttpRequest->SetURL("https://api.openai.com/v1/chat/completions");// OpenAI API�� URL�� �����մϴ�.
    HttpRequest->SetVerb("POST");// ��û ���(POST)�� �����մϴ�.
    HttpRequest->SetHeader("Content-Type", "application/json");// ��û�� Content-Type�� JSON �������� �����մϴ�.
    HttpRequest->SetHeader("Authorization", FString::Printf(TEXT("Bearer %s"), *ApiKey));// API Ű�� Authorization ����� �߰��մϴ�.

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);// JSON ��ü�� �����մϴ�.
    JsonObject->SetStringField("model", Model);// ����Ϸ��� �� �̸��� JSON�� �߰��մϴ�.

    TArray<TSharedPtr<FJsonValue>> Messages;// �޽��� �迭�� �����Ͽ� ������Ʈ�� ����� �޽����� �߰��մϴ�.
    TSharedPtr<FJsonObject> PromptMessage = MakeShareable(new FJsonObject);// �ý��� ������ �޽���(������Ʈ)�� JSON ��ü�� �����մϴ�.
    PromptMessage->SetStringField("role", "system");
    PromptMessage->SetStringField("content", Prompt); // Prompt�� FString���� ��ȯ
    Messages.Add(MakeShareable(new FJsonValueObject(PromptMessage))); // ������ ������Ʈ �޽����� �޽��� �迭�� �߰��մϴ�.

    TSharedPtr<FJsonObject> UserMessage = MakeShareable(new FJsonObject);// ����� ������ �޽����� JSON ��ü�� �����մϴ�.
    UserMessage->SetStringField("role", "user");
    UserMessage->SetStringField("content", Message);
    Messages.Add(MakeShareable(new FJsonValueObject(UserMessage)));// ������ ����� �޽����� �޽��� �迭�� �߰��մϴ�.

    JsonObject->SetArrayField("messages", Messages);// �޽��� �迭�� JSON ��ü�� �����մϴ�.

    FString RequestBody;// JSON ��ü�� ���ڿ��� ����ȭ�Ͽ� ��û ������ �����մϴ�.
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    HttpRequest->SetContentAsString(RequestBody);

    HttpRequest->ProcessRequest();// HTTP ��û�� �����մϴ�.

}

// OpenAI�� ������ ó���ϴ� �Լ�
void UChatBotSystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response->GetResponseCode() == 200)// ��û�� �����ϰ� ���� �ڵ尡 200�� ��쿡�� ó���մϴ�.
    {
        TSharedPtr<FJsonObject> JsonResponse;// JSON ������ �Ľ��� JsonResponse ��ü�� �����մϴ�.
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonResponse))// ������ JsonResponse�� �Ľ��մϴ�.
        {
            FString AssistantResponse = JsonResponse->GetArrayField("choices")[0]// ���� JSON���� ���� ������ �����մϴ�.
                ->AsObject()->GetObjectField("message")->GetStringField("content");

            OnChatBotResponseReceived.Broadcast(AssistantResponse);// ���� ���� �� ��ε�ĳ��Ʈ �̺�Ʈ�� ���� �ٸ� �ý��ۿ� �˸��ϴ�.

            UE_LOG(LogTemp, Log, TEXT("ChatBot Response: %s"), *AssistantResponse);// �� ������ �α׿� ����մϴ�.
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Request failed: %s"), *Response->GetContentAsString());// ��û ���� �� ���� ������ �α׿� ����մϴ�.
    }
}
