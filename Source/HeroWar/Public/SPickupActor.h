// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPickupActor.generated.h"

class USphereComponent;
class ASPowerupActor;

UCLASS()
class HEROWAR_API ASPickupActor : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	ASPickupActor();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* SphereComponent;
	 
	UPROPERTY(VisibleAnywhere,Category="Components")
	UDecalComponent* DecalComponent;

	UPROPERTY(EditInstanceOnly,Category="PickupActor")
	TSubclassOf<ASPowerupActor> PowerUpClass;

	ASPowerupActor* PowerUpInstance;
	
	UPROPERTY(EditInstanceOnly,Category="PickupActor")
	float CooldownDuration;

	FTimerHandle TimerHandle_RespawnTimer;
	
	void Respawn();

	public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
