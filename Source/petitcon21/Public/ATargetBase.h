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
	
public:	
	AATargetBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetVelocity(const FVector& Velocity) const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attacked();
	UFUNCTION(BlueprintNativeEvent)
	void Withdraw();
};
