// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
    ATank* GetControlledTank() const;
    
    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world.
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector&) const;
    
public:
    // Sets default values for this controller's properties
    ATankPlayerController();
	
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaTime ) override;
	
};
