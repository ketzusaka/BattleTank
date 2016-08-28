// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
    
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("AIController is not possessing a tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay for tank %s"), *(ControlledTank->GetName()));
    }
}
