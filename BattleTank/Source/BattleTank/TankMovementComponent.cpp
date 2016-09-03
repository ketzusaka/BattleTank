// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack) {
    if (!LeftTrack || !RightTrack) { return; }
    this->LeftTrack = LeftTrack;
    this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: throttle throw %f"), Time, Throw);
    
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

