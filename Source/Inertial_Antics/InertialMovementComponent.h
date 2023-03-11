// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/ShapeComponent.h"
#include "InertialMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class INERTIAL_ANTICS_API UInertialMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

protected:
	FVector ComputeAcceleration();
	FVector ComputeVelocity(float DeltaTime);
	FVector ComputeMoveDelta(float DeltaTime);

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float Mass;

	void HandleHit(FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MaxVelocityMagnitude = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float MinVelocityMagnitude = 0.2f;

	/*UPROPERTY(BlueprintReadOnly, Category = "Movement")
		FVector Velocity;*/

	/** How much velocity is lost for each bounce. 0 means no loss, 1 means all velocity is lost.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float BounceLoseRatio = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float GravityAcceleration = 5.0f;

	UShapeComponent* UpdatedShape;
};
