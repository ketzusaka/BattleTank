// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    if (AimingComponent->GetFiringState() == EFiringState::Locked) {
         AimingComponent->Fire();
    }
    
}

void ATankAIController::SetPawn(APawn* InPawn) {
    Super::SetPawn(InPawn);
    if (!InPawn) { return; }
    
    auto PossessedTank = Cast<ATank>(InPawn);
    if (!ensure(PossessedTank)) { return; }
    
    // Subscribe our local method to the tank's death event
    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath() {
    UE_LOG(LogTemp, Warning, TEXT("AICONT got tank death"));
}
