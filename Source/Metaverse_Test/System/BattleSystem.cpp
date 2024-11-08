// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleSystem.h"
#include "../UI/BattleCutInUI.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABattleSystem::ABattleSystem(){
	TotalDamage = 0;
	IsBattleOver = false;
	IsPlayerTurn = true;
	BattleRound = 1;

	MonsterSkillData = LoadObject<UDataTable>(nullptr, TEXT("/Game/BattleMap/DataTable/DT_MonsterSkill.DT_MonsterSkill"));
}

void ABattleSystem::BeginPlay(){
	Super::BeginPlay();

	BattleTurnPlayer();
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
	if (BattleRound == 6) {
		IsBattleOver = true;
		GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, FString::Printf(TEXT("Battle End!")));
		UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Level/OutSide_2D3DHybrid")));
	}
}

//Entity ����
void ABattleSystem::SetBattleEntities(APlayerCharacter* Entity1, AMonsterCharacter* Entity2){
	PlayerEntity = Entity1;
	MonsterEntity = Entity2;

	if (PlayerEntity == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Initialize Failed!"))
	}
}

//void ABattleSystem::SetBattleNpcs(APlayerCharacter* Entity1, AMonsterCharacter* Entity2) {}

void ABattleSystem::BattleTurnPlayer(){ return; }

void ABattleSystem::BattleTurnEnemy(){ 

	int SkillPersentageNumber = FMath::RandRange(0, 5);
	static const FString SkillDataContextString(TEXT("SkillTableContext"));

	if (SkillPersentageNumber == 0) {
		FName SkillNum = FName(*(FString::FromInt(1)));
		MonsterSkill = MonsterSkillData->FindRow<FSkillInfo>(SkillNum, SkillDataContextString, true);
	}
	else {
		FName SkillNum = FName(*(FString::FromInt(2)));
		MonsterSkill = MonsterSkillData->FindRow<FSkillInfo>(SkillNum, SkillDataContextString, true);
	}
	
	switch (MonsterSkill->SkillType) {
	case Attack:
		MonsterAttack();
		break;
	case Depense:
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

//�� ������ ���� �� ���� ���� Ȯ��.
void ABattleSystem::EndTurn(){
	IsEndGame();

	if (IsPlayerTurn) {
		IsPlayerTurn = false;
		BattleTurnEnemy();
	}
	else {IsPlayerTurn = true;
		BattleTurnPlayer();
		BattleRound += 1;
	}
}

//��ų ���� ���� ��ȯ
bool ABattleSystem::GetSkillIsSucceed(){
	return IsSkillSucceed;
}

//��ų ã��
void ABattleSystem::SkillSystem(SubjectClass Subject, int RowNum){
	CurSkill = LoadSkillSystem.FindPlayerSkill(Subject, RowNum);
		
	//��ų �з��� �°� �Լ� �����α�
	switch (CurSkill->SkillType) {
		case Attack:
			AttackSkill();
			break;
		case Depense:
			DepenseSkill();
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
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);
	
	if (cost <= PlayerEntity->GetMP()) {
		if (PlayerEntity->JudgmentSubject(SkillClass)) {
			MonsterEntity->SetHP(-FMath::Clamp(LoadSkillSystem.AmountExceptionHandling(CurSkill) - DependedDamage, 0, 50));
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

	DependedDamage = 0;
	ShowDebugLog();
}

void ABattleSystem::DepenseSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);
	
	if (PlayerEntity->JudgmentSubject(SkillClass)) {
		DependedDamage = LoadSkillSystem.AmountExceptionHandling(CurSkill);
	}
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::HealSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);
	int healAmount = LoadSkillSystem.AmountExceptionHandling(CurSkill);

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
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);

	PlayerEntity->JudgmentSubject(SkillClass);
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::PracticalSkill(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);

	PlayerEntity->JudgmentSubject(SkillClass);
	PlayerEntity->SetMP(-cost);

	ShowDebugLog();
}

void ABattleSystem::MonsterAttack(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);
	int damage = FMath::Clamp(LoadSkillSystem.AmountExceptionHandling(CurSkill) - DependedDamage, 0, 50);

	if (cost <= MonsterEntity->GetMP()) {
		if (MonsterEntity->JudgmentSkill(3)) {
			PlayerEntity->SetHP(-damage);
		}

		MonsterEntity->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
	}

	DependedDamage = 0;
	ShowDebugLog();
}

void ABattleSystem::MonsterDepense(){
	int cost = LoadSkillSystem.MpExceptionHandling(CurSkill);
	DependedDamage = LoadSkillSystem.AmountExceptionHandling(CurSkill);

	if (cost <= MonsterEntity->GetMP()) {
		if (MonsterEntity->JudgmentSkill(3)) {

		}
		MonsterEntity->SetMP(-cost);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 7.0, FColor::Red, "Skill Ready Failed!");
	}

	ShowDebugLog();
}

void ABattleSystem::ShowDebugLog(){
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, FString::Printf(TEXT("KeyValue %s, SkillName %s ,Amount %d ,MpCost %d ,Detail %s, SKillType %d"), *CurSkill->KeyValue, *CurSkill->SkillName, CurSkill->Amount, CurSkill->MpCost, *CurSkill->Detail, CurSkill->SkillType));
	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Yellow, FString::Printf(TEXT("Player HP: %d, MP: %d Monster HP: %d, MP: %d"), PlayerEntity->Hp, PlayerEntity->Mp, MonsterEntity->Hp, MonsterEntity->Mp));
}