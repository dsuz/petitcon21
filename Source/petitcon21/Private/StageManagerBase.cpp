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
	// 最終ステージの番号を取得する
	for (auto& kv : StageSequenceData->StageSequenceMap) {
		if (kv.Value.StageNumber > LastStageNumber) {
			LastStageNumber = kv.Value.StageNumber;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Last Stage Number: %d"), LastStageNumber);
}

void AStageManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!IsWorking) return;
	Timer += GetWorld()->GetDeltaSeconds();
	
	if (FilteredStageSequenceData->Num() == 0) {
		UE_LOG(LogTemp, Display, TEXT("Warning: No stage data. Exit..."));
		IsWorking = false;
		return;
	}
	
	const auto kv = FilteredStageSequenceData->begin();
	
	if (Timer > kv.Value().TimeSecond) {
		UE_LOG(LogTemp, Display, TEXT("Spawn: %f, %s, %s"), kv.Value().TimeSecond, *kv.Value().SpawnLocation.ToCompactString(), *kv.Value().SpawnRotation.ToCompactString());
		const auto SpawnTarget = GetWorld()->SpawnActor<AATargetBase>(TargetList[kv.Value().TargetIndex], kv.Value().SpawnLocation, kv.Value().SpawnRotation);
		auto ShootVelocity = kv.Value().ShootDirection;
		ShootVelocity.Normalize();
		ShootVelocity *= kv.Value().ShootSpeed;
		SpawnTarget->SetVelocity(ShootVelocity);
		UE_LOG(LogTemp, Display, TEXT("Shoot: %s"), *ShootVelocity.ToCompactString());
		FilteredStageSequenceData->Remove(kv.Key());
		const auto TargetRemainsCount = FilteredStageSequenceData->Num();
		OnTargetGeneration.Broadcast(TargetRemainsCount);
		
		if (TargetRemainsCount == 0) {
			IsWorking = false;
			UE_LOG(LogTemp, Display, TEXT("Stage sequence finished."));
			OnTargetGenerationComplete.Broadcast();
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

	// 残りターゲット数を通知する
	OnTargetGeneration.Broadcast(FilteredStageSequenceData->Num());
}

void AStageManagerBase::Pause()
{
	IsWorking = false;
}

void AStageManagerBase::Resume()
{
	IsWorking = true;
}

