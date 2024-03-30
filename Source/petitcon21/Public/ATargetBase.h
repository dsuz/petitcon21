#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATargetBase.generated.h"

UCLASS()
class PETITCON21_API AATargetBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Damage = 5;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Score = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeSpan = 5.0;	// アクタインスタンスが自動的に消えるまでの時間
	
public:	
	AATargetBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetVelocity(const FVector& Velocity) const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attacked();
};
