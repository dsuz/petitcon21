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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverDelegate);	// ゲームオーバー
	UPROPERTY(BlueprintAssignable)
	FGameOverDelegate OnGameOver;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeScoreDelegate);	// 得点の変動
	UPROPERTY(BlueprintAssignable)
	FChangeScoreDelegate OnChangeScore;
	UFUNCTION(BlueprintCallable)
	int AddScore(const int Score_Adding);
	UFUNCTION(BlueprintCallable)
	int GetScore();

protected:
	virtual void BeginPlay() override;

private:
	EGameState State = EGameState::None;
	EGameState LastState = EGameState::None;
	int Level = 1;
	int Score = 0;
};
