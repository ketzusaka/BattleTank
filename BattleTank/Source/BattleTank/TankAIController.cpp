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
    if (!ensure(ControlledTank)) { return; }
    
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (!ensure(PlayerController)) { return; }
    
    auto PlayerTank = Cast<ATank>(PlayerController->GetPawn());
    if (!ensure(PlayerTank)) { return; }
    
    MoveToActor(PlayerTank, 3000);
    
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
//    ControlledTank->Fire();
    
}
