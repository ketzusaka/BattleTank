// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 500;
    
    UPROPERTY(VisibleAnywhere, Category = "Gameplay")
    int32 CurrentHealth = StartingHealth;

protected:
    
public:
	// Sets default values for this pawn's properties
	ATank();
    
    virtual void BeginPlay() override;
    
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
    UFUNCTION(BlueprintPure, Category = "Gameplay")
    float GetHealthPercent() const;
};
