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
    bool GetLookDirection(FVector2D, FVector&) const;
    bool GetLookVectorHitLocation(FVector, FVector&) const;
    
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333f;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.f;
    
public:
    // Sets default values for this controller's properties
    ATankPlayerController();
	
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaTime ) override;
	
};
