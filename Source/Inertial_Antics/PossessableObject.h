// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InertialCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PossessableObject.generated.h"

UCLASS()
class INERTIAL_ANTICS_API APossessableObject : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APossessableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
