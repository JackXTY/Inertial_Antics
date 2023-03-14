// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InertialCharacter.h"
#include "InertialBallCharacter.generated.h"

/**
 * 
 */
UCLASS()
class INERTIAL_ANTICS_API AInertialBallCharacter : public AInertialCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AInertialBallCharacter();
	virtual void SetCollisionComponent() override;
};
