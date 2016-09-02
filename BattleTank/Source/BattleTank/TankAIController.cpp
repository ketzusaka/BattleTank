// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    
    auto ControlledTank = Cast<ATank>(GetPawn());
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("AIController is not possessing a tank"));
        return;
    }
    
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (!PlayerController) {
        UE_LOG(LogTemp, Error, TEXT("Could not obtain tank"));
        return;
    }
    
    auto PlayerTank = Cast<ATank>(PlayerController->GetPawn());
    if (!PlayerTank) {
        UE_LOG(LogTemp, Error, TEXT("Cannot find Player Tank"));
        return;
    }
    
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
//    ControlledTank->Fire();
    
}
