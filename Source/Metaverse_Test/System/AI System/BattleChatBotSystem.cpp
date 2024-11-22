// Fill out your copyright notice in the Description page of Project Settings.


#include "System/AI System/BattleChatBotSystem.h"
#include "Interfaces/IHttpResponse.h"

// Api랑 Key 모델 초기화
UBattleChatBotSystem::UBattleChatBotSystem(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("SomeComponent")).DoNotCreateDefaultSubobject(TEXT("SomeOtherComponent"))) {

    ApiKey = ""; // OpenAI API 키를 입력
    Model = "gpt-4o"; // 사용할 모델 이름 설정   
    AssistantResponseText = ""; // 초기화
    
    //프롬프트 저장 데이터 테이블 바인딩
    PromptData = LoadObject<UDataTable>(nullptr, TEXT("/Game/BattleMap/DataTable/DT_PromptData.DT_PromptData"));
}

void UBattleChatBotSystem::SendMessageToOpenAI(const FString& Message){
    // HTTP 요청 객체 생성 및 설정
    HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UBattleChatBotSystem::OnResponseReceived);

    HttpRequest->SetURL("https://api.openai.com/v1/chat/completions");
    HttpRequest->SetVerb("POST");
    HttpRequest->SetHeader("Content-Type", "application/json; charset=utf-8" );
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
    FName Rownum = FName(*(FString::FromInt(1)));
    static const FString PromptDataTableContext(TEXT("PromptDataTableContext"));
    
    MessageData = PromptData->FindRow<FPromptData>(Rownum, PromptDataTableContext, true);
    PromptMessage = MessageData->PromptRole;
    
    FString MessageSet = PromptMessage + TEXT("\n\n") + SkillDetail;    // 메시지 구성

    UE_LOG(LogTemp, Log, TEXT("Prompt Message: %s"), *MessageSet);  //로그 출력

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

FString UBattleChatBotSystem::GetResponse() const{
    return  AssistantResponseText;
}
