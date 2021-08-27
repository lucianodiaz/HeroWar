// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"

#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerupActor::ASPowerupActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	// StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	// //RootComponent = StaticMeshComponent;
	// StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn,ECollisionResponse::ECR_Overlap);
	PowerupInterval = 0.0f;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationMovementComponent"));
	RotatingMovementComponent->Velocity = FVector(0,10,0);
	TotalNrOfTicks = 0;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASPowerupActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPowerupActor::OnRep_PowerupActive()
{
	OnPowerupStateChanged(bIsPowerUpActive);
}

void ASPowerupActor::OnTickPowerup()
{
	TicksProcessed ++;

	OnPowerUpTicked();
	
	if( TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();
		//Delete timer
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void ASPowerupActor::ActivatePowerup(AActor* ActivatedFor)
{
	ActivatedForPlayer = ActivatedFor;
	OnActivated();
	bIsPowerUpActive = true;
	OnRep_PowerupActive();
	if(TakeParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,TakeParticleSystem,GetActorLocation());
	}
	if(PowerupInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerupActor::OnTickPowerup, PowerupInterval,true);
	}
	else
	{
		OnTickPowerup();
	}
}

void ASPowerupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerupActor,bIsPowerUpActive);
}
