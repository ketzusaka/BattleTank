// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
    // Force in Newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 400000.0f;
    
    float CurrentThrottle = 0;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    void ApplySidewaysForce();
    void DriveTrack();
    
public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void SetThrottle(float Throttle);
	
    UTankTrack();
    
    void BeginPlay() override;
    
    
	
};
