// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float Difference) {
    Difference = FMath::Clamp(Difference, -MaxDegreesPerSecond, MaxDegreesPerSecond);
    auto RotationChange = Difference * GetWorld()->DeltaTimeSeconds;
    auto NewRotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, NewRotation, 0));
}

