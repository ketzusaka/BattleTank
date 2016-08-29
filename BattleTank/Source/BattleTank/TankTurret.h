// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
    UPROPERTY(EditAnywhere, Category = Setup )
    float MaxDegreesPerSecond = 15.0f;
	
    
public:
    // Difference in Degrees
    void Rotate(float Difference);
};
