// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    
    // Start the tank moving the barrel so that a shot would hit where
    // the crosshair intersects the world.
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector&) const;
    bool GetLookDirection(FVector2D, FVector&) const;
    bool GetLookVectorHitLocation(FVector, FVector&) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.f;
    
    UFUNCTION()
    void OnTankDeath();
    
protected:
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingComponent);
    
public:
    // Sets default values for this controller's properties
    ATankPlayerController();
	
    virtual void BeginPlay() override;
    virtual void Tick( float DeltaTime ) override;
    
    virtual void SetPawn(APawn* InPawn) override;
	
};
