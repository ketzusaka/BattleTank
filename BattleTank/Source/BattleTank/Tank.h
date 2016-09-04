// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankBarrel;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, Category=Firing)
    float LaunchSpeed = 4000;
    
    UPROPERTY(EditDefaultsOnly, Category=Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;
        
    UPROPERTY(EditDefaultsOnly, Category=Firing)
    float ReloadTimeInSeconds = 3.f;
    
    double LastFireTime = 0.f;

protected:
    
public:
	// Sets default values for this pawn's properties
	ATank();
    
    virtual void BeginPlay() override;
    
    UFUNCTION(BlueprintCallable, Category = Gameplay)
    void Fire();
	
};
