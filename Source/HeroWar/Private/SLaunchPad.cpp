// Fill out your copyright notice in the Description page of Project Settings.


#include "SLaunchPad.h"

#include "Characters/MainCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ASLaunchPad::ASLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	RootComponent = StaticMeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ASLaunchPad::OnBeginOverlap);


	LaunchStrenght = 1500.0f;
	LaunchPitchAngle = 65.0f;
}

// Called when the game starts or when spawned
void ASLaunchPad::BeginPlay()
{
	Super::BeginPlay();
}

void ASLaunchPad::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		FRotator LaunchDireaction = GetActorRotation();
		LaunchDireaction.Pitch += LaunchPitchAngle;

		FVector LaunchVelocity = LaunchDireaction.Vector() * LaunchStrenght;
		
		AMainCharacter* MC = Cast<AMainCharacter>(OtherActor);
		if(MC)
		{
			MC->LaunchCharacter(LaunchVelocity,true,true);
		}
	}
}
