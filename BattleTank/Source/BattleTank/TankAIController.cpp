// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (!PlayerController) {
        UE_LOG(LogTemp, Error, TEXT("Could not obtain tank"));
        return nullptr;
    }
    
    return Cast<ATank>(PlayerController->GetPawn());
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Error, TEXT("AIController is not possessing a tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay for tank %s"), *(ControlledTank->GetName()));
    }
    
    auto PlayerTank = GetPlayerTank();
    
    if (!PlayerTank) {
        UE_LOG(LogTemp, Error, TEXT("Could not find player tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("PlayerTank '%s' found"), *(PlayerTank->GetName()));
    }
}
