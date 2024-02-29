#include "StageManagerBase.h"

AStageManagerBase::AStageManagerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStageManagerBase::BeginPlay()
{
	Super::BeginPlay();
	StageSequenceData = Cast<UStageSequenceDataAsset>(StaticLoadObject(UStageSequenceDataAsset::StaticClass(), nullptr, *StageSequenceDataAssetPath.ToString()));
	FilteredStageSequenceData = MakeShared<TMap<int, FStageSequenceData>>();
}

void AStageManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsWorking) return;
	Timer += GetWorld()->GetDeltaSeconds();
	const auto kv = FilteredStageSequenceData->begin();
	
	if (Timer > kv.Value().TimeSecond) {
		UE_LOG(LogTemp, Display, TEXT("Spawn at %f"), kv.Value().TimeSecond);
		FilteredStageSequenceData->Remove(kv.Key());

		if (FilteredStageSequenceData->Num() == 0) {
			IsWorking = false;
			UE_LOG(LogTemp, Display, TEXT("Done"));
		}
	}
}

void AStageManagerBase::Start(const int StageNumber)
{
	UE_LOG(LogTemp, Display, TEXT("Start stage %d"), StageNumber);
	Timer = 0;
	IsWorking = true;
	FilteredStageSequenceData->Reset();

	// 該当ステージのデータを抽出する
	for (auto data : StageSequenceData->StageSequenceMap) {
		if (data.Value.StageNumber == StageNumber) {
			FilteredStageSequenceData->Add(data.Key, data.Value);
		}
	}

	// 時間順に並び変える
	FilteredStageSequenceData->ValueSort([](const FStageSequenceData& A, const FStageSequenceData& B)
	{
		return A.TimeSecond < B.TimeSecond;
	});
}

void AStageManagerBase::Pause()
{
	IsWorking = false;
}

void AStageManagerBase::Resume()
{
	IsWorking = true;
}

