// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"


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
        
    if (GetSightRayHitLocation(HitLocation)) {
        ControlledTank->AimAt(HitLocation);
    }
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    
    // Figure out position of dot
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    FVector LookDirection;
    
    if (!GetLookDirection(ScreenLocation, LookDirection)) {
        UE_LOG(LogTemp, Error, TEXT("Unable to Deproject Screen Position to World"));
        return false;
    }
    
    if (!GetLookVectorHitLocation(LookDirection, HitLocation)) {
        HitLocation = FVector(0.f);
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
    FHitResult Hit;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    
    if (!GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility)) {
        return false;
    }
    
    HitLocation = Hit.Location;
    return true;
    
}
