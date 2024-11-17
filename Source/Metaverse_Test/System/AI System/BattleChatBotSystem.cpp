// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AI System/BattleChatBotSystem.h"
#include "Interfaces/IHttpResponse.h"

// Api랑 Key 모델 초기화
UBattleChatBotSystem::UBattleChatBotSystem() {
    ApiKey = "Key"; // OpenAI API 키를 입력
    Model = "Model"; // 사용할 모델 이름 설정
    RoleMessage = TEXT("이하의 스킬을 보고, 스킬 묘사에 있는 단어를 최대한 사용하지 않으면서 추상적인 단어를 사용하여 그 전에 일어날 법한 상황을 묘사해줘.");
    AssistantResponseText = ""; // 초기화
}

void UBattleChatBotSystem::SendMessageToOpenAI(const FString& Message){
    // HTTP 요청 객체 생성 및 설정
    HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UBattleChatBotSystem::OnResponseReceived);

    HttpRequest->SetURL("https://api.openai.com/v1/chat/completions");
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json");
    HttpRequest->SetHeader("Authorization", FString::Printf(TEXT("Bearer %s"), *ApiKey));

    // JSON 바디 생성
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField("model", Model);

    TArray<TSharedPtr<FJsonValue>> Messages;
    TSharedPtr<FJsonObject> UserMessage = MakeShareable(new FJsonObject);
    UserMessage->SetStringField("role", "user");
    UserMessage->SetStringField("content", Message);
    Messages.Add(MakeShareable(new FJsonValueObject(UserMessage)));

    JsonObject->SetArrayField("messages", Messages);

    // JSON을 문자열로 변환하여 바디에 설정
    FString RequestBody;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
    HttpRequest->SetContentAsString(RequestBody);

    // 요청 실행
    HttpRequest->ProcessRequest();
}

void UBattleChatBotSystem::SetPromptMessage(FString SkillDetail){
    FString MessageSet;

    MessageSet = TEXT("");

    SendMessageToOpenAI(MessageSet);
}

void UBattleChatBotSystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSucceed){
    if (bWasSucceed && Response->GetResponseCode() == 200) {
        // JSON 응답 파싱
        TSharedPtr<FJsonObject> JsonResponse;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

        if (FJsonSerializer::Deserialize(Reader, JsonResponse)) {
            // OpenAI의 응답을 AssistantResponseText에 저장
            AssistantResponseText = JsonResponse->GetArrayField("choices")[0]
                ->AsObject()->GetObjectField("message")->GetStringField("content");

            // 응답 출력 (예: 콘솔에 출력하거나 UI에 연결)
            UE_LOG(LogTemp, Log, TEXT("ChatBot Response: %s"), *AssistantResponseText);
        }
    }
    else {
        // 오류 처리
        UE_LOG(LogTemp, Error, TEXT("Request failed: %s"), *Response->GetContentAsString());
        AssistantResponseText = "Error: Unable to get response from OpenAI.";
    }
}

FString UBattleChatBotSystem::GetReponse() const{
    return  AssistantResponseText;
}
