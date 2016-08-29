// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if (!Barrel) { return; }
    
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
    UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *OurTankName, *AimDirection.ToString());
    
    MoveBarrelTo(AimDirection);
}

void UTankAimingComponent::MoveBarrelTo(FVector AimDirection) {
    // Work out difference between current barrel rotation and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(5); // TODO: Remove magic number
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
    Barrel = BarrelToSet;
}
