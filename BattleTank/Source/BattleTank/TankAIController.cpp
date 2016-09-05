// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    
    auto ControlledTank = GetPawn();
    if (!ensure(ControlledTank)) { return; }
    
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    
    auto PlayerController = GetWorld()->GetFirstPlayerController();
    
    if (!ensure(PlayerController)) { return; }
    
    auto PlayerTank = PlayerController->GetPawn();
    if (!ensure(PlayerTank)) { return; }
    
    MoveToActor(PlayerTank, 3000);
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
         AimingComponent->Fire();
    }
    
}
