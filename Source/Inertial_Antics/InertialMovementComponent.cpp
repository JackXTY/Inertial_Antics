// Fill out your copyright notice in the Description page of Project Settings.


#include "InertialMovementComponent.h"


void UInertialMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure that everything is still valid, and that we are allowed to move.
    if (!PawnOwner || !UpdatedComponent || !UpdatedShape || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    UpdatedShape->AddImpulse(ConsumeInputVector() * 100.0f);
    
    FVector DesiredMovementThisFrame = ComputeMoveDelta(DeltaTime);

    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        HandleHit(Hit);        
    }
};

void UInertialMovementComponent::HandleHit(FHitResult& Hit)
{
    if (Hit.IsValidBlockingHit())
    {
        // UE_LOG(LogTemp, Warning, TEXT("Hit %f, %f, %f"), PawnOwner->GetVelocity().X, PawnOwner->GetVelocity().Y, PawnOwner->GetVelocity().Z);
        if (Hit.Component->BodyInstance.bSimulatePhysics)
        {
            // total momentum won't increase
            Hit.Component->AddImpulseAtLocation(Velocity * 100.0f, Hit.ImpactPoint);
        }
        else
        {
            float vel = Velocity.Length() * (1 - BounceLoseRatio);
            if (vel < MinVelocityMagnitude)
            {
                Velocity = FVector::ZeroVector;
            }
            else
            {
                Velocity = (Velocity.GetSafeNormal() + 2 * Hit.ImpactNormal).GetSafeNormal() * vel;
            }
            
        }

        // SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
    }
}

FVector UInertialMovementComponent::ComputeAcceleration()
{
    // a = f/m
    FVector inputForce = ConsumeInputVector() + FVector(0, 0, -GravityAcceleration);
    return inputForce.IsNearlyZero() ? FVector::ZeroVector : inputForce / Mass;
}

FVector UInertialMovementComponent::ComputeVelocity(float DeltaTime)
{
    Velocity += ComputeAcceleration() * DeltaTime;
    Velocity = Velocity.GetClampedToMaxSize(MaxVelocityMagnitude);
    return Velocity;
}

FVector UInertialMovementComponent::ComputeMoveDelta(float DeltaTime)
{
    return ComputeVelocity(DeltaTime) * DeltaTime;
}