// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
    
    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
    
    // Call from the pathfinding logic by the AI controllers
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    
public:
	
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack);
    
	UFUNCTION(BlueprintCallable, Category = "Movement")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void IntendTurnRight(float Throw);
	
};
