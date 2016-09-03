// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
    // TODO: Clamp Throttle
    
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s throttle set to %f: Applying %s to %s"), Time, *GetName(), Throttle, *(ForceApplied.ToString()), *(ForceLocation.ToString()));
    
    
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
