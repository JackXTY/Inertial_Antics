// Fill out your copyright notice in the Description page of Project Settings.

#include "InertialBallCharacter.h"
#include "Components/SphereComponent.h"


//void AInertialBallCharacter::SetCollisionComponent()
//{
//	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
//	USphereComponent* Sphere = static_cast<USphereComponent*>(CollisionComponent);
//	Sphere->OnComponentHit.AddDynamic(this, &AInertialBallCharacter::OnHit);
//	RootComponent = CollisionComponent;
//}