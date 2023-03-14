// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// #include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
// #include "GameFramework/ProjectileMovementComponent.h"
#include <Inertial_Antics/InertialMovementComponent.h>
#include "InertialCharacter.generated.h"

UCLASS()
class INERTIAL_ANTICS_API AInertialCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInertialCharacter();

protected:
	// Called when the game starts or when spawned
	// virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	// UPROPERTY(EditAnywhere)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;

	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ArrowMeshComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Movement")
		UShapeComponent* CollisionComponent;


	virtual void SetCollisionComponent();

	// Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Mouse_XAxis(float AxisValue);
	void Mouse_YAxis(float AxisValue);
	void LeftMouseButton(float AxisValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float walkMaxSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float walkPower = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float ShootPower = 2000.f;

	// FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
		float cameraDistance = 350.f;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float cameraPitchAngle = 25.f;

	float horizontalAngle = 0.f;

	float deltaMouseX = 0.f;
	float deltaMouseY = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
		float cameraVerticalRotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
		float horizontalRotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "View")
		FVector focusOffset = FVector(0.f, 0.f, 100.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
		float hitStrength = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
		float BounceLoseRatio = 0.3f;

	void SetCamera();

	float leftMouseButtonVal = 0.f;

	//UFUNCTION()
	//	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	FVector2D WalkInput;
};
