// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float Difference) {
    Difference = FMath::Clamp(Difference, -MaxDegreesPerSecond, MaxDegreesPerSecond);
    auto RotationChange = Difference * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = RelativeRotation.Yaw + RotationChange;
    UE_LOG(LogTemp, Error, TEXT("Rotation Change: %f; NewRotation: %f"), RotationChange, NewRotation);


    SetRelativeRotation(FRotator(RelativeRotation.Pitch, NewRotation, 0));
}

