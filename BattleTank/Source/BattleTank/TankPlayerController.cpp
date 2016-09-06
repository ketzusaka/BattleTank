// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

ATankPlayerController::ATankPlayerController() {
    PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    
    if (!GetPawn()) { return; } // For example, if not possessing
    
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if (ensure(AimingComponent)) {
        FoundAimingComponent(AimingComponent);
    }
}

void ATankPlayerController::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    
    AimTowardsCrosshair();
    
}

void ATankPlayerController::AimTowardsCrosshair() {
    if (!GetPawn()) { return; }
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(AimingComponent)) { return; }
    
    FVector HitLocation;
        
    if (GetSightRayHitLocation(HitLocation)) {
        AimingComponent->AimAt(HitLocation);
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
    
    if (!GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Camera)) {
        return false;
    }
    
    HitLocation = Hit.Location;
    return true;
    
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
    Super::SetPawn(InPawn);
    if (!InPawn) { return; }
    
    auto PossessedTank = Cast<ATank>(InPawn);
    if (!ensure(PossessedTank)) { return; }
    
    // Subscribe our local method to the tank's death event
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::OnTankDeath() {
    StartSpectatingOnly();
}
