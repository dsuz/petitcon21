#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageSequenceData.h"
#include "ATargetBase.h"
#include "StageManagerBase.generated.h"

UCLASS(config = Game, defaultconfig)
class PETITCON21_API AStageManagerBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "StageSequenceDataAsset"))
	FSoftObjectPath StageSequenceDataAssetPath;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AATargetBase>> TargetList;

	//DECLARE_MULTICAST_DELEGATE_OneParam(FNotifyTargetRemainsCountDelegate, void, const int);	// ターゲットを生成するたびに呼び、残りターゲット数を与える
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyTargetRemainsCountDelegate, int, TargetRemainsCount);	// ターゲットを生成するたびに呼び、残りターゲット数を与える
	UPROPERTY(BlueprintAssignable)
	FNotifyTargetRemainsCountDelegate OnTargetGeneration;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetGenerationCompleteDelegate);	// ターゲットの生成を終了した時に呼ぶ
	UPROPERTY(BlueprintAssignable)
	FTargetGenerationCompleteDelegate OnTargetGenerationComplete;

	UPROPERTY(BlueprintReadOnly)
	int LastStageNumber = 0;
	
private:
	UPROPERTY()
	TSoftObjectPtr<class UStageSequenceDataAsset> StageSequenceData;

	float Timer = 0;
	bool IsWorking = false;
	// そのステージのターゲット出力シーケンス
	TSharedPtr<TMap<int, FStageSequenceData>> FilteredStageSequenceData;
	
protected:
	virtual void BeginPlay() override;

public:
	AStageManagerBase();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void Start(const int StageNumber);
	UFUNCTION(BlueprintCallable)
	void Pause();
	UFUNCTION(BlueprintCallable)
	void Resume();
};
