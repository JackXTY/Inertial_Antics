// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InertialPawn.generated.h"

UCLASS()
class INERTIAL_ANTICS_API AInertialPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInertialPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void Tick(float DeltaTime) override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Mouse_XAxis(float AxisValue);
	void Mouse_YAxis(float AxisValue);
	void LeftMouseButton(float AxisValue);

	float deltaMouseX = 0.f;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
		float deltaMouseY = 0.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
		float minCameraAngle = 0.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
		float maxCameraAngle = 0.f;

	float mouseVal = 0.f;

	FVector2D WalkInput;

	UFUNCTION(BlueprintImplementableEvent)
		void OnMousePress();

	UFUNCTION(BlueprintImplementableEvent)
		void OnMousePressing(float val);

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseRelease(float val);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float walkMaxSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float walkPower = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float mouseMax = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float jumpPower = 2000.f;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		FVector GetWalkDirection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float horizontalRotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float cameraRotationSpeed = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float cameraMinAngle = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float cameraMaxAngle = 80.f;

	float horizontalAngle = 0.f;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StartPlayerControl();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void StopPlayerControl();
};
