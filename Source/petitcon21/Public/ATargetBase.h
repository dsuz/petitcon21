#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/CapsuleComponent.h"
#include "ATargetBase.generated.h"

UCLASS()
class PETITCON21_API AATargetBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	//UPROPERTY(EditAnywhere)
	//TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditAnywhere)
	float Speed = 200.0;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Damage = 5;
	
public:	
	AATargetBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetVelocity(const FVector& Velocity) const;
};
