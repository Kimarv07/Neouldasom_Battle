// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem.h"
#include "../UI/BattleCutInUI.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/BattleUI.h"

// Sets default values
ABattleSystem::ABattleSystem(){
	IsBattleOver = false;
	IsPlayerTurn = true;
	IsNpcUsed = false;
	BattleRound = 1;

	MonsterSkillData = LoadObject<UDataTable>(nullptr, TEXT("/Game/BattleMap/DataTable/DT_MonsterSkill.DT_MonsterSkill"));

	ChatBotSystem = NewObject<UBattleChatBotSystem>();
}

void ABattleSystem::BeginPlay(){
	Super::BeginPlay();

	SetEnemySkill();
}

void ABattleSystem::IsEndGame(){
	if (PlayerEntity->Hp <= 0) {
		IsBattleOver = true;
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, FString::Printf(TEXT("Battle End!")));
		UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Level/OutSide_2D3DHybrid")));
	}
	if (MonsterEntity->Hp <= 0) {
		IsBattleOver = true;
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, FString::Printf(TEXT("Battle End!")));
		UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Level/OutSide_2D3DHybrid")));
	}
}

//Entity 설정
void ABattleSystem::SetBattleEntities(APlayerCharacter* Entity1, AMonsterCharacter* Entity2){
	PlayerEntity = Entity1;
	MonsterEntity = Entity2;

	if (PlayerEntity == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Initialize Failed!"))
	}
}

void ABattleSystem::SetBattleNpcs(APlayerCharacter* Entity1, APlayerCharacter* Entity2){
	NpcEntity1 = Entity1;
	NpcEntity2 = Entity2;

	IsNpcUsed = true;
}

void ABattleSystem::BattleTurnPlayer(){ return; }

void ABattleSystem::SetEnemySkill(){
	int SkillPersentageNumber = FMath::RandRange(0, 5);
	static const FString SkillDataContextString(TEXT("SkillTableContext"));

	if (SkillPersentageNumber == 0) {
		FName SkillNum = FName(*(FString::FromInt(1)));
		MonsterSkill = MonsterSkillData->FindRow<FSkillInfo>(SkillNum, SkillDataContextString, true);
		MonsterJudgeLimit = 3;
	}
	else {
		FName SkillNum = FName(*(FString::FromInt(2)));
		MonsterSkill = MonsterSkillData->FindRow<FSkillInfo>(SkillNum, SkillDataContextString, true);
		MonsterJudgeLimit = 2;
	}
	ChatBotSystem->SetPromptMessage(MonsterSkill->Detail);
	HintResponse = ChatBotSystem->GetResponse();
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, ChatBotSystem->GetResponse());
}

void ABattleSystem::BattleTurnEnemy(){

	switch (MonsterSkill->SkillType) {
	case Attack:
		MonsterAttack();
		break;
	case Defense:
		MonsterDepense();
		break;
	case Heal:
		//HealSkill();
		break;
	case Support:
		//SupportSkill();
		break;
	case Practical:
		//PracticalSkill();
		break;
	default:
		break;
	}

	EndTurn();
	return;
}

void ABattleSystem::BattleTurnNpc(){
	FSkillInfo* NpcSkill;
	if (PlayerEntity->GetHP() < PlayerEntity->GetMaxHP() / 2) {
		NpcSkill = LoadSkillSystem.FindPlayerSkill(SubjectClass::OrientalMedecine, 2);
	}
	else {
		NpcSkill = LoadSkillSystem.FindPlayerSkill(SubjectClass::NatureMagic, 3);
	}

	switch (NpcSkill->SkillType) {
	case Attack:
		NpcAttack();
		break;
	case Defense:
		//DepenseSkill();
		break;
	case Heal:
		NpcHeal();
		break;
	case Support:
		//SupportSkill();
		break;
	case Practical:
		//PracticalSkill();
		break;
	default:
		break;
	}
}

//턴 끝내고 다음 턴 진행 여부 확인.
void ABattleSystem::EndTurn(){
	IsEndGame();

	if (IsPlayerTurn) {
		IsPlayerTurn = false;
		if (IsNpcUsed) {
			BattleTurnNpc();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Purple, FString::Printf(TEXT("NPC IS NOT USED!")));
		}
		BattleTurnEnemy();
	}
	else {
		IsPlayerTurn = true;
		SetEnemySkill();
		BattleTurnPlayer();
		BattleRound += 1;
	}
}

//스킬 성공 여부 반환
bool ABattleSystem::GetSkillIsSucceed(){
	return IsSkillSucceed;
}

//스킬 찾기
void ABattleSystem::SkillSystem(SubjectClass Subject, int RowNum){
	CurSkill = LoadSkillSystem.FindPlayerSkill(Subject, RowNum);
		
	//스킬 분류에 맞게 함수 나눠두기
	switch (CurSkill->SkillType) {
		case Attack:
			AttackSkill();
			break;
		case Defense:
			DefenseSkill();
			break;
		case Heal:
			HealSkill();
			break;
		case Support:
			SupportSkill();
			break;
		case Practical:
			PracticalSkill();
			break;
		default:
			break;
		}
}

void ABattleSystem::AttackSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);
	
	if (cost <= PlayerEntity->GetMP()) {
		if (PlayerEntity->JudgmentSubject(SkillClass)) {
			MonsterEntity->SetHP(-FMath::Clamp(LoadSkillSystem.AmountExceptionHandling(CurSkill, PlayerEntity) - DefendedDamage, 0, 50));
			IsSkillSucceed = true;
		}
		else
			IsSkillSucceed = false;
		PlayerEntity->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
		IsSkillSucceed = false;
	}

	DefendedDamage = 0;
	ShowDebugLog();
}

void ABattleSystem::DefenseSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);
	
	if (PlayerEntity->JudgmentSubject(SkillClass)) {
		DefendedDamage = LoadSkillSystem.AmountExceptionHandling(CurSkill, PlayerEntity);
	}
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::HealSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);
	int healAmount = LoadSkillSystem.AmountExceptionHandling(CurSkill, PlayerEntity);

	if (PlayerEntity->JudgmentSubject(SkillClass)) {
		PlayerEntity->SetHP(healAmount);
		IsSkillSucceed = true;
	}
	else
		IsSkillSucceed = false;
	PlayerEntity->SetMP(-cost);
	

	ShowDebugLog();
}

void ABattleSystem::SupportSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);

	PlayerEntity->JudgmentSubject(SkillClass);
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::PracticalSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);

	PlayerEntity->JudgmentSubject(SkillClass);
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::MonsterAttack(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, PlayerEntity);
	int damage = FMath::Clamp(LoadSkillSystem.AmountExceptionHandling(CurSkill, nullptr) - DefendedDamage, 0, 50);

	if (cost <= MonsterEntity->GetMP()) {
		if (MonsterEntity->JudgmentSkill(MonsterJudgeLimit)) {
			PlayerEntity->SetHP(-damage);
			//EffectSystem->SpawnMonsterAttackEffect();
		}

		MonsterEntity->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
	}

	DefendedDamage = 0;
	ShowDebugLog();
}

void ABattleSystem::MonsterDepense(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, nullptr);
	DefendedDamage = LoadSkillSystem.AmountExceptionHandling(CurSkill, nullptr);

	if (cost <= MonsterEntity->GetMP()) {
		if (MonsterEntity->JudgmentSkill(MonsterJudgeLimit)) {

		}
		MonsterEntity->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
	}

	ShowDebugLog();
}

void ABattleSystem::NpcAttack(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, NpcEntity1);

	if (cost <= NpcEntity1->GetMP()) {
		if (NpcEntity1->JudgmentSubject(SkillClass)) {
			MonsterEntity->SetHP(-FMath::Clamp(LoadSkillSystem.AmountExceptionHandling(CurSkill, NpcEntity1) - DefendedDamage, 0, 50));
			IsSkillSucceed = true;
		}
		else
			IsSkillSucceed = false;
		NpcEntity1->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
		IsSkillSucceed = false;
	}

	DefendedDamage = 0;
	ShowDebugLog();
}

void ABattleSystem::NpcHeal(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill, NpcEntity1);
	int healAmount = LoadSkillSystem.AmountExceptionHandling(CurSkill, NpcEntity1);

	if (NpcEntity2->JudgmentSubject(SkillClass)) {
		PlayerEntity->SetHP(healAmount);
		IsSkillSucceed = true;
	}
	else
		IsSkillSucceed = false;
	NpcEntity2->SetMP(-cost);


	ShowDebugLog();
}

void ABattleSystem::ShowDebugLog(){
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, FString::Printf(TEXT("KeyValue %s, SkillName %s ,Amount %d ,MpCost %d ,Detail %s, SKillType %d"), *CurSkill->KeyValue, *CurSkill->SkillName, CurSkill->Amount, CurSkill->MpCost, *CurSkill->Detail, CurSkill->SkillType));
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, FString::Printf(TEXT("Player HP: %d, MP: %d Monster HP: %d, MP: %d"), PlayerEntity->Hp, PlayerEntity->Mp, MonsterEntity->Hp, MonsterEntity->Mp));
}