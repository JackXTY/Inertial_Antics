// Fill out your copyright notice in the Description page of Project Settings.

#include "InertialCharacter.h"

// Sets default values
AInertialCharacter::AInertialCharacter()
{
    SetCollisionComponent();

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(CollisionComponent);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SetupAttachment(CollisionComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    SetCamera();

    ArrowMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMeshComponent"));
    ArrowMeshComponent->SetupAttachment(CameraComponent);

}

void AInertialCharacter::SetCollisionComponent()
{
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    CollisionComponent->SetSimulatePhysics(true);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    // CollisionComponent->OnComponentHit.AddDynamic(this, &AInertialCharacter::OnHit);
    RootComponent = CollisionComponent;
}

// change camera rotation and position according to cameraPitchAngle and cameraDistance
// also deal with actor rotation
void AInertialCharacter::SetCamera()
{
    //if (CameraComponent != nullptr && PrimaryActorTick.bCanEverTick && AutoPossessPlayer != EAutoReceiveInput::Disabled)
 
    if (FMath::Abs(deltaMouseX) > 0.01f)
    {
        horizontalAngle += deltaMouseX * horizontalRotationSpeed;
        deltaMouseX = 0.f;
        
        // UE_LOG(LogTemp, Warning, TEXT("horizontalAngle = %f"), horizontalAngle);
    }
    SetActorRotation(FRotator(0.f, horizontalAngle, 0.f));
    
    if (FMath::Abs(deltaMouseY) > 0.01f)
    {
        cameraPitchAngle = FMath::Clamp(cameraPitchAngle + deltaMouseY * cameraVerticalRotationSpeed, -25.f, 85.f);
        deltaMouseY = 0.f;
    }

    FVector camRelativePos = FVector(-cameraDistance * cos(cameraPitchAngle * 0.017453f), 0.0f, cameraDistance * sin(cameraPitchAngle * 0.017453f));
    CameraComponent->SetRelativeLocation(camRelativePos + focusOffset);
    CameraComponent->SetRelativeRotation(FRotator(-cameraPitchAngle, 0.0f, 0.0f));
    
}

// Called when the game starts or when spawned
void AInertialCharacter::BeginPlay(){
    Super::BeginPlay();
}

// Called every frame
void AInertialCharacter::Tick(float DeltaTime)
{
    // move the camera according to mouse input
    SetCamera();
    SetActorRotation(FRotator(0.f, horizontalAngle, 0.f));

    if (CollisionComponent && CollisionComponent->GetComponentVelocity().Length() < walkMaxSpeed)
    {
        FVector dir = GetActorRightVector()* WalkInput.X + GetActorForwardVector() * WalkInput.Y;
        if (dir.Length() > 0.01f)
        {
            dir.Normalize();
            CollisionComponent->AddImpulse(dir * walkPower * DeltaTime);
        }
    }
}

// Called to bind functionality to input
void AInertialCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponents)
{
    // UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    PlayerInputComponents->BindAxis("MoveX", this, &AInertialCharacter::Move_XAxis);
    PlayerInputComponents->BindAxis("MoveY", this, &AInertialCharacter::Move_YAxis);
    PlayerInputComponents->BindAxis("MouseX", this, &AInertialCharacter::Mouse_XAxis);
    PlayerInputComponents->BindAxis("MouseY", this, &AInertialCharacter::Mouse_YAxis);
    PlayerInputComponents->BindAxis("LeftMouseButton", this, &AInertialCharacter::LeftMouseButton);
}

void AInertialCharacter::Move_XAxis(float AxisValue)
{
    // Move at 100 units per second forward or backward
    //UE_LOG(LogTemp, Warning, TEXT("Move_XAxis %s"), *GetActorForwardVector().ToString());// AxisValue);
    WalkInput.X = AxisValue;
}

void AInertialCharacter::Move_YAxis(float AxisValue)
{
    WalkInput.Y = AxisValue;
}

void AInertialCharacter::Mouse_XAxis(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("Mouse_XAxis %f"), AxisValue);
    deltaMouseX += AxisValue;
}

void AInertialCharacter::Mouse_YAxis(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("Mouse_YAxis %f"), AxisValue);
    deltaMouseY += AxisValue;
}

// Move the pawn with inertia
void AInertialCharacter::LeftMouseButton(float AxisValue)
{
    // UE_LOG(LogTemp, Warning, TEXT("LeftMouseButton %f"), AxisValue);
    if (AxisValue > 0.99f)
    {
        //if (leftMouseButtonVal < 0.01f)
        //{
        //    // on mouse pressed
        //}
  
        // when mouse is being pressed
        leftMouseButtonVal += AxisValue;
    }
    else if (leftMouseButtonVal > 0.99f)
    {
        // on mouse release
        FVector shoot = ArrowMeshComponent->GetRightVector() * FMath::Min(leftMouseButtonVal, 10.0f) * ShootPower;
        if (CollisionComponent) {
            CollisionComponent->AddImpulse(shoot);
        }

        leftMouseButtonVal = 0.f;
    }
    
}

//void AInertialCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//    UE_LOG(LogTemp, Warning, TEXT("Hit everything!!"));
//
//    if (OtherActor != nullptr && OtherActor != this && OtherComponent != nullptr && OtherComponent->IsSimulatingPhysics())
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Hit a possessable!!"));
//    }
//}