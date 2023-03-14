// Fill out your copyright notice in the Description page of Project Settings.

#include "InertialBallCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
AInertialBallCharacter::AInertialBallCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Disabled;

    //UE_LOG(LogTemp, Warning, TEXT("Walk Speed = %f"), walkSpeed);

    // SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

    SetCollisionComponent();

    MeshComponent->SetupAttachment(RootComponent);
    // RootComponent = MeshComponent;

    // SetRootComponent(MeshComponent);

    CameraComponent->SetupAttachment(RootComponent);
    SetCamera();

    ArrowMeshComponent->SetupAttachment(CameraComponent);

    // attempt to workaround: delete parent box collision component
    UActorComponent* parentCollision = GetComponentByClass(UBoxComponent::StaticClass());
    if (parentCollision) {
        parentCollision->DestroyComponent();
        parentCollision->SetActive(false);
    }
}

void AInertialBallCharacter::SetCollisionComponent()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollisionComponent"));
	//USphereComponent* Sphere = static_cast<USphereComponent*>(CollisionComponent);
	//Sphere->OnComponentHit.AddDynamic(this, &AInertialBallCharacter::OnHit);
	RootComponent = CollisionComponent;
}