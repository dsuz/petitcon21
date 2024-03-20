#include "GameManagerCpp.h"

AGameManagerCpp::AGameManagerCpp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManagerCpp::ChangeStatus(const EGameState NewState)
{
	this->LastState = this->State;
	this->State = NewState;

	if (this->State == EGameState::Intro) {	// イントロ再生
		OnIntroduction.Broadcast();
	} else if (this->State == EGameState::InGame) {	// ゲーム開始
		OnGameStart.Broadcast();
	} else if (this->State == EGameState::GameOver) { // ゲームオーバー
		OnGameOver.Broadcast();
	} else if (this->State == EGameState::Clear) {	// ステージクリア
		OnClearStage.Broadcast();
	}

	// enum -> string
	const auto StateStringLast = UEnum::GetValueAsString(this->LastState);
	const auto StateStringCurrent = UEnum::GetValueAsString(this->State);
	UE_LOG(LogTemp, Display, TEXT("State changed from %s to %s"), *StateStringLast, *StateStringCurrent);
}

EGameState AGameManagerCpp::GetStatus()
{
	return this->State;
}

int AGameManagerCpp::AddScore(const int Score_Adding)
{
	this->Score += Score_Adding;
	UE_LOG(LogTemp, Display, TEXT("Add Score: %d, Total Score: %d"), Score_Adding, Score);
	OnChangeScore.Broadcast();
	return this->Score;
}

int AGameManagerCpp::GetScore()
{
	return Score;
}

void AGameManagerCpp::BeginPlay()
{
	Super::BeginPlay();
	this->ChangeStatus(EGameState::Intro);
}

void AGameManagerCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

