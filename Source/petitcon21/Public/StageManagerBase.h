#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageSequenceData.h"
#include "StageManagerBase.generated.h"

UCLASS(config = Game, defaultconfig)
class PETITCON21_API AStageManagerBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "StageSequenceDataAsset"))
	FSoftObjectPath StageSequenceDataAssetPath;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Target;

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
