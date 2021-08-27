// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickupActor.h"

#include "SPowerupActor.h"
#include "Characters/MainCharacter.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPickupActor::ASPickupActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(75.0f);
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetRelativeRotation(FRotator(90,0,0));
	DecalComponent->DecalSize = FVector(64,75,75);
	DecalComponent->SetupAttachment(RootComponent);
	
	CooldownDuration = 10.f;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ASPickupActor::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		Respawn();
	}
	
}

void ASPickupActor::Respawn()
{
	if(PowerUpClass == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("PowerUp class is nullptr in %s. Please update your blueprint"), * GetName());
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	PowerUpInstance = GetWorld()->SpawnActor<ASPowerupActor>(PowerUpClass,GetTransform(),SpawnParameters);
}

void ASPickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	
	if(HasAuthority() && MainCharacter && PowerUpInstance)
	{
		PowerUpInstance->ActivatePowerup(OtherActor);

		PowerUpInstance = nullptr;

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer,this,&ASPickupActor::Respawn,CooldownDuration);
	}
}
