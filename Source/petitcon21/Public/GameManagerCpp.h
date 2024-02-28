#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EGameState.h"
#include "GameManagerCpp.generated.h"

UCLASS()
class PETITCON21_API AGameManagerCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManagerCpp();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void ChangeStatus(const EGameState NewState);
	UFUNCTION(BlueprintCallable)
	EGameState GetStatus();
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIntroductionDelegate);	// イントロを再生する
	UPROPERTY(BlueprintAssignable)
	FIntroductionDelegate OnIntroduction;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStartDelegate);	// ゲームスタート
	UPROPERTY(BlueprintAssignable)
	FGameStartDelegate OnGameStart;

protected:
	virtual void BeginPlay() override;

private:
	EGameState State = EGameState::None;
	EGameState LastState = EGameState::None;
	int Level = 1;
};
