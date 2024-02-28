#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "StageSequenceData.generated.h"

USTRUCT()
struct FStageSequenceData_TableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int StageNumber;
	UPROPERTY(EditAnywhere)
	float TimeSecond;
	//UPROPERTY(EditAnywhere)
	//E_TargetType TargetType;
	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere)
	FVector ShootDirection;
	UPROPERTY(EditAnywhere)
	float ShootSpeed;
};

USTRUCT(BlueprintType)
struct FStageSequenceData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int StageNumber;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TimeSecond;
	//UPROPERTY(EditAnywhere)
	//E_TargetType TargetType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector SpawnLocation;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector ShootDirection;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ShootSpeed;
};

UCLASS()
class PETITCON21_API UStageSequenceDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UDataTable* DataTable;
#endif

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<int, FStageSequenceData> StageSequenceMap;
	
public:
	UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true"))
	void Build();
};
