// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

ACharacterBase::ACharacterBase()
{
}

void ACharacterBase::InitializeInfo(int H, int D, int C, int W, int F){
	Humanity = H;
	Desire = D;
	Courtesy = C;
	Wisdom = W;
	Fortune = F;

	HpLimit = Desire + Fortune + 18;
	MpLimit = Humanity + Courtesy + Wisdom + 6;

	Hp = HpLimit;
	Mp = MpLimit;
}

int ACharacterBase::GetHP(){return Hp;}

int ACharacterBase::GetMaxHP(){return HpLimit;}

int ACharacterBase::GetMP(){return Mp;}

int ACharacterBase::GetMaxMP(){	return MpLimit;}

void ACharacterBase::SetHP(int HpMount){
	Hp += HpMount;
	Hp = FMath::Clamp(Hp, 0, HpLimit);
}

void ACharacterBase::SetMP(int MpCost){
	Mp += MpCost;
	Mp = FMath::Clamp(Mp, 0, MpLimit);
}

void ACharacterBase::BeginPlay(){
	Super::BeginPlay();
}
