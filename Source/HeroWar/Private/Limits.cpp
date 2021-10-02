// Fill out your copyright notice in the Description page of Project Settings.


#include "Limits.h"

#include "Characters/MainCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALimits::ALimits()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ALimits::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ALimits::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALimits::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
		if(Character)
		{
			UE_LOG(LogTemp,Warning,TEXT("Character is Out of limits"));
			TSubclassOf<UDamageType> DamageCauser;
			UGameplayStatics::ApplyDamage(OtherActor,3,GetInstigatorController(),this,DamageCauser);
			
		}
	}
	
	
}
