// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
    
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
    if (!ensure(Barrel)) { return; }
    
    if (!ensure(Turret)) { return; }
    
    auto OurTankName = GetOwner()->GetName();
    
    auto BarrelLocation = Barrel->GetComponentLocation();
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    // Calculate OutLaunchVelicity
    if (!UGameplayStatics::SuggestProjectileVelocity
        (
         this,
         OutLaunchVelocity,
         StartLocation,
         HitLocation,
         LaunchSpeed,
         false,
         0,
         0,
         ESuggestProjVelocityTraceOption::DoNotTrace
        )) {
        UE_LOG(LogTemp, Error, TEXT("Unable to get a suggested projectile velocity for %s from Barrel %s"), *OurTankName, *(BarrelLocation.ToString()));
        return;
    }
    
    auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // Convert to unit vector
    
    MoveBarrelTo(AimDirection);
    MoveTurretTo(AimDirection);
}

void UTankAimingComponent::MoveBarrelTo(FVector AimDirection) {
    // Work out difference between current barrel rotation and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTo(FVector AimDirection) {
    auto TurretRotator = Turret->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    
    auto TurretRotatorDenormalized = TurretRotator.GetDenormalized();
    auto AimRotatorDenormalized = AimAsRotator.GetDenormalized();
    
    
    float YawDifference = AimRotatorDenormalized.Yaw - TurretRotatorDenormalized.Yaw;
    
    if (YawDifference > 180.f) {
        YawDifference -= 360.f;
    } else if (YawDifference < -180.f) {
        YawDifference += 360.f;
    }
    
    Turret->Rotate(YawDifference);
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret) {
    this->Barrel = Barrel;
    this->Turret = Turret;
}

void UTankAimingComponent::Fire() {
    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    
     if (!ensure(Barrel && ProjectileBlueprint)) { return; }
     if (!isReloaded) { return; }
     
     // Spawn a projectile at the socket location on the barrel
     
     FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
     FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
     auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
     Projectile->LaunchProjectile(LaunchSpeed);
     LastFireTime = FPlatformTime::Seconds();
     
}

