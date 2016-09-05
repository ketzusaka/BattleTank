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
	PrimaryComponentTick.bCanEverTick = true;
    
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    if (Ammo <= 0) {
        FiringState = EFiringState::OutOfAmmo;
    } else if (LastFireTime + ReloadTimeInSeconds > FPlatformTime::Seconds()) {
        FiringState = EFiringState::Reloading;
        auto Time = GetWorld()->GetTimeSeconds();
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    } else {
        FiringState = EFiringState::Locked;
    }
	
}

EFiringState UTankAimingComponent::GetFiringState() const {
    return FiringState;
}

int32 UTankAimingComponent::GetAmmoRemaining() const {
    return Ammo;
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
    
    CurrentAimDirection = OutLaunchVelocity.GetSafeNormal(); // Convert to unit vector
    
    MoveBarrelTowards(CurrentAimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    
    if (FMath::Abs(DeltaRotator.Yaw) < 180) {
        Turret->Rotate(DeltaRotator.Yaw);
    } else {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret) {
    this->Barrel = Barrel;
    this->Turret = Turret;
}

void UTankAimingComponent::Fire() {
    if (!ensure(Barrel && ProjectileBlueprint)) { return; }
    if (FiringState == EFiringState::Reloading || FiringState == EFiringState::OutOfAmmo) { return; }
    
    // Spawn a projectile at the socket location on the barrel

    FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
    
    Ammo--;
}

bool UTankAimingComponent::IsBarrelMoving() const {
    if (!ensure(Barrel)) { return false; }
    
    return !Barrel->GetForwardVector().Equals(CurrentAimDirection, 0.05f);
}
