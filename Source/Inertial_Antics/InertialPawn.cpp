// Fill out your copyright notice in the Description page of Project Settings.


#include "InertialPawn.h"

// Sets default values
AInertialPawn::AInertialPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInertialPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AInertialPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FMath::Abs(deltaMouseX) > 0.01f)
    {
        horizontalAngle += deltaMouseX * horizontalRotationSpeed;
        deltaMouseX = 0.f;

        // UE_LOG(LogTemp, Warning, TEXT("horizontalAngle = %f"), horizontalAngle);
    }
    SetActorRotation(FRotator(rotatePitch, horizontalAngle, rotateRoll));
}

// Called to bind functionality to input
void AInertialPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponents)
{
    // UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    PlayerInputComponents->BindAxis("MoveX", this, &AInertialPawn::Move_XAxis);
    PlayerInputComponents->BindAxis("MoveY", this, &AInertialPawn::Move_YAxis);
    PlayerInputComponents->BindAxis("MouseX", this, &AInertialPawn::Mouse_XAxis);
    PlayerInputComponents->BindAxis("MouseY", this, &AInertialPawn::Mouse_YAxis);
    PlayerInputComponents->BindAxis("LeftMouseButton", this, &AInertialPawn::LeftMouseButton);
}

void AInertialPawn::Move_XAxis(float AxisValue)
{
    // Move at 100 units per second forward or backward
    //UE_LOG(LogTemp, Warning, TEXT("Move_XAxis %s"), *GetActorForwardVector().ToString());// AxisValue);
    WalkInput.X = AxisValue;
}

void AInertialPawn::Move_YAxis(float AxisValue)
{
    WalkInput.Y = AxisValue;
}

void AInertialPawn::Mouse_XAxis(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("Mouse_XAxis %f"), AxisValue);
    deltaMouseX += AxisValue;
}

void AInertialPawn::Mouse_YAxis(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("Mouse_YAxis %f"), AxisValue);
    deltaMouseY += AxisValue;
}

// Move the pawn with inertia
void AInertialPawn::LeftMouseButton(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("LeftMouseButton %f"), AxisValue);
    if (AxisValue > 0.99f)
    {
        if (mouseVal < 0.01f)
        {
            // on mouse pressed
            OnMousePress();
        }
        else {
            OnMousePressing(FMath::Min(mouseVal, mouseMax));
        }

        // when mouse is being pressed
        mouseVal += AxisValue;
    }
    else if (mouseVal > 0.99f)
    {
        // on mouse release
        OnMouseRelease(FMath::Min(mouseVal, mouseMax));
        /*FVector shoot = ArrowMeshComponent->GetRightVector() * FMath::Min(shootVal, shootMax) * ShootPower;
        if (CollisionComponent) {
            CollisionComponent->AddImpulse(shoot);
        }*/

        mouseVal = 0.f;
    }

}

FVector AInertialPawn::GetWalkDirection()
{
    FVector walkDir = GetActorRotation().RotateVector(FVector(WalkInput.Y, WalkInput.X, 0));
    walkDir.Z = 0;
    walkDir.Normalize();
    return walkDir;
}

