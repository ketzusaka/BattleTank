// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed) {
    UE_LOG(LogTemp, Warning, TEXT("Barrel RS: %f"), RelativeSpeed);
    // Move the barrel the right amount this frame
    // Given a max elevation, and the frame time
}
