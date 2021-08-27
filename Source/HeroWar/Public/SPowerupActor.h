// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerupActor.generated.h"


class URotatingMovementComponent;

UCLASS()
class HEROWAR_API ASPowerupActor : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	ASPowerupActor();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// UPROPERTY(VisibleAnywhere,Category="Components")
	// UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere,Category="Components")
	URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(EditDefaultsOnly,Category="Powerups")
	UParticleSystem* TakeParticleSystem;
	
	/* Time between powerup effect */
	UPROPERTY(EditDefaultsOnly,Category="Powerups")
	float PowerupInterval;

	/* Total times we apply the powerup effect */
	UPROPERTY(EditDefaultsOnly,Category="Powerups")
	int32 TotalNrOfTicks;

	FTimerHandle TimerHandle_PowerupTick;

	//Total number ticks apply
	int32 TicksProcessed;

	UPROPERTY(BlueprintReadOnly,Category="Powerups")
	AActor* ActivatedForPlayer;
	
	UPROPERTY(ReplicatedUsing=OnRep_PowerupActive)
	bool bIsPowerUpActive;

	UFUNCTION()
	void OnRep_PowerupActive();

	UFUNCTION(BlueprintImplementableEvent,Category="Powerups")
	void OnPowerupStateChanged(bool bnewIsActive);
	
	
	UFUNCTION()
	void OnTickPowerup();
	
	public:

	void ActivatePowerup(AActor* ActivatedFor);

	UFUNCTION(BlueprintImplementableEvent,Category="Powerups")
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent,Category="Powerups")
	void OnPowerUpTicked();
	
	UFUNCTION(BlueprintImplementableEvent,Category="Powerups")
	void OnExpired();
	
};
