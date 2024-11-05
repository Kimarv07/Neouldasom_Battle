// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatBotSystem.h"
#include "Interfaces/IHttpResponse.h"

//Api�� Key �� �ʱ�ȭ
UChatBotSystem::UChatBotSystem(){
	ApiKey = "Key";// OpenAI API Ű�� �Է�
	Model = "Model";// ����� �� �̸� ����
}

void UChatBotSystem::SendMessageToOpenAI(const FString& Message){
    // HTTP ��û ��ü ���� �� ����
    HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UChatBotSystem::OnResponseReceived);

    HttpRequest->SetURL("https://api.openai.com/v1/chat/completions");
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetHeader("Authorization", FString::Printf(TEXT("Bearer %s"), *ApiKey));

    // JSON �ٵ� ����
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("model", Model);

    TArray<TSharedPtr<FJsonValue>> Messages;
    TSharedPtr<FJsonObject> UserMessage = MakeShareable(new FJsonObject);
    UserMessage->SetStringField("role", "user");
    UserMessage->SetStringField("content", Message);
    Messages.Add(MakeShareable(new FJsonValueObject(UserMessage)));

    JsonObject->SetArrayField("messages", Messages);

    // JSON�� ���ڿ��� ��ȯ�Ͽ� �ٵ� ����
    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    HttpRequest->SetContentAsString(RequestBody);

    // ��û ����
    HttpRequest->ProcessRequest();
}

void UChatBotSystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed){
    if (bWasSucceed && Response->GetResponseCode() == 200){
        // JSON ���� �Ľ�
        TSharedPtr<FJsonObject> JsonResponse;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonResponse)){
            FString AssistantResponse = JsonResponse->GetArrayField("choices")[0]
                ->AsObject()->GetObjectField("message")->GetStringField("content");

            // ���� ��� (��: �ֿܼ� ����ϰų� UI�� ����)
            UE_LOG(LogTemp, Log, TEXT("ChatBot Response: %s"), *AssistantResponse);
        }
    }
    else{
        // ���� ó��
        UE_LOG(LogTemp, Error, TEXT("Request failed: %s"), *Response->GetContentAsString());
    }
}
