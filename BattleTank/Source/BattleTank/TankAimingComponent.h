// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState: uint8 {
    Reloading,
    Aiming,
    Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void MoveBarrelTowards(FVector AimDirection);
    bool IsBarrelMoving() const;
    
    UPROPERTY(EditDefaultsOnly, Category=Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category=Firing)
    float ReloadTimeInSeconds = 3.f;
    
    double LastFireTime = 0.f;
    FVector CurrentAimDirection = FVector::ForwardVector;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
    
public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    void AimAt(FVector HitLocation);
	
    UFUNCTION(BlueprintCallable, Category = Gameplay)
    void Fire();
};
