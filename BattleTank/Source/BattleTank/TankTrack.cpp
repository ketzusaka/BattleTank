// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
/*    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Calculate the slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    
    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    
    // Calculate and apply sideways force (F = m a)
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
    TankRoot->AddForce(CorrectionForce);*/
    
}

void UTankTrack::SetThrottle(float Throttle) {
    // TODO: Clamp Throttle
    
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    UE_LOG(LogTemp, Warning, TEXT("%s TankRoot: %s"), *(GetOwner()->GetName()), *(TankRoot->GetName()));
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
