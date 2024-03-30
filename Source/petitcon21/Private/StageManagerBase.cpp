#include "StageManagerBase.h"

AStageManagerBase::AStageManagerBase()
{
	PrimaryActorTick.bCanEverTick = true;
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
	if (StageSequenceData == nullptr) {
		LoadStageData();
	}	// 理由は不明だが、StageSequenceData が解放されてしまうためこうしている
	
	UE_LOG(LogTemp, Display, TEXT("Start stage %d"), StageNumber);
	Timer = 0;
	IsWorking = true;
	FilteredStageSequenceData->Reset();

	// 該当ステージのデータを抽出する
	UE_LOG(LogTemp, Display, TEXT("Filter stage data for stage #%d..."), StageNumber);
	for (auto data : StageSequenceData->StageSequenceMap) {
		if (data.Value.StageNumber == StageNumber) {
			FilteredStageSequenceData->Add(data.Key, data.Value);
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Finished filtering stage data."));

	// 時間順に並び変える
	UE_LOG(LogTemp, Display, TEXT("Sort stage data..."));
	FilteredStageSequenceData->ValueSort([](const FStageSequenceData& A, const FStageSequenceData& B)
	{
		return A.TimeSecond < B.TimeSecond;
	});
	UE_LOG(LogTemp, Display, TEXT("Finished sorting stage data."));

	// 残りターゲット数を通知する
	UE_LOG(LogTemp, Display, TEXT("Notify target counts: %d"), FilteredStageSequenceData->Num());
	OnTargetGeneration.Broadcast(FilteredStageSequenceData->Num());
	UE_LOG(LogTemp, Display, TEXT("Finished notifying target counts."));
}

void AStageManagerBase::Pause()
{
	IsWorking = false;
}

void AStageManagerBase::Resume()
{
	IsWorking = true;
}

int AStageManagerBase::GetLastStageNumber()
{
	if (StageSequenceData == nullptr) {
		LoadStageData();
	}
	return LastStageNumber;	
}

void AStageManagerBase::LoadStageData()
{
	UE_LOG(LogTemp, Display, TEXT("Load stage sequence data..."));
	StageSequenceData = Cast<UStageSequenceDataAsset>(StaticLoadObject(UStageSequenceDataAsset::StaticClass(), nullptr, *StageSequenceDataAssetPath.ToString()));
	FilteredStageSequenceData = MakeShared<TMap<int, FStageSequenceData>>();
	// 最終ステージの番号を取得する
	for (auto& kv	 : StageSequenceData->StageSequenceMap) {
		if (kv.Value.StageNumber > LastStageNumber) {
			LastStageNumber = kv.Value.StageNumber;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Last Stage Number: %d"), LastStageNumber);
}

