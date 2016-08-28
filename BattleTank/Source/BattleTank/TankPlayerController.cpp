// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



ATankPlayerController::ATankPlayerController() {
    PrimaryActorTick.bCanEverTick = true;
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    
    
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessing a tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay for tank %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    
    AimTowardsCrosshair();
    
}

void ATankPlayerController::AimTowardsCrosshair() {
    auto ControlledTank = GetControlledTank();
    
    if (!ControlledTank) { return; }
    
    FVector HitLocation;
    
    // Get world location of linetrace through crosshair
    
    if (GetSightRayHitLocation(HitLocation)) {
        UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
        // If hits landscape
            // Tell controlled tank to aim at this point
    }
    
    
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    HitLocation = FVector(1.0f);
    // Figure out position of dot
    
    // Determine where it hits the landscape
        // If hit landscape, set Location and return true
        // Otherwise, return false
    
    return true;
}
