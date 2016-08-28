// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



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
