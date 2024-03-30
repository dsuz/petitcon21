#include "ATargetBase.h"

AATargetBase::AATargetBase()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultSceneRoot;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/VREditor/TransformGizmo/TranslateArrowHandle.TranslateArrowHandle"), nullptr, LOAD_None, nullptr);
	StaticMesh->SetStaticMesh(Mesh);
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetEnableGravity(false);
	PrimaryActorTick.bCanEverTick = true;
}

void AATargetBase::BeginPlay()
{
	Super::BeginPlay();
	this->SetLifeSpan(LifeSpan);
}

void AATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;
}

void AATargetBase::SetVelocity(const FVector& Velocity) const
{
	StaticMesh->SetPhysicsLinearVelocity(Velocity);
}

void AATargetBase::ResetLifeSpan(float SecondsFromNow)
{
	this->SetLifeSpan(LifeTime + SecondsFromNow);
}

void AATargetBase::Attacked_Implementation()
{
}
