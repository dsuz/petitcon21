#include "ATargetBase.h"
//#include "Components/CapsuleComponent.h"

AATargetBase::AATargetBase()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = DefaultSceneRoot;
	//Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UCapsuleComponent"));
	//Capsule->SetupAttachment(RootComponent);
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
}

void AATargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AATargetBase::SetVelocity(const FVector& Velocity) const
{
	StaticMesh->SetPhysicsLinearVelocity(Velocity);
}

// void AATargetBase::SetVelocity(const FVector& Force) const
// {
// 	//StaticMesh->AddForce(Force);
// 	StaticMesh->SetPhysicsLinearVelocity(Force);
// }

