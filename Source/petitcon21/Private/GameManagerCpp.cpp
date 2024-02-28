#include "GameManagerCpp.h"
#include "Kismet/KismetSystemLibrary.h"

AGameManagerCpp::AGameManagerCpp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManagerCpp::ChangeStatus(const EGameState NewState)
{
	this->LastState = this->State;
	this->State = NewState;

	if (this->State == EGameState::Intro) {
		// イントロ再生
		OnIntroduction.Broadcast();
	} else if (this->State == EGameState::InGame) {
		// ゲーム開始
		OnGameStart.Broadcast();
	}

	// enum -> string
	const auto StateStringLast = UEnum::GetValueAsString(this->LastState);
	const auto StateStringCurrent = UEnum::GetValueAsString(this->State);
	const auto Message = FString(TEXT("State changed to ")) + StateStringCurrent + FString(TEXT(" from ")) + StateStringLast;
	UKismetSystemLibrary::PrintString(this, Message);
}

EGameState AGameManagerCpp::GetStatus()
{
	return this->State;
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

