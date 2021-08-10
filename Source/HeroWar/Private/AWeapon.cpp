// Fill out your copyright notice in the Description page of Project Settings.


#include "AWeapon.h"

#include "Characters/MainCharacter.h"

// Sets default values
AAWeapon::AAWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	RateOfFire = 60;

	MuzzleSocketName = "MuzzleSocket";
}

// Called when the game starts or when spawned
void AAWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShot = 60/RateOfFire;
}

void AAWeapon::StartShoot()
{
	
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShot - GetWorld()->TimeSeconds,0.0f);
	GetWorldTimerManager().SetTimer(TimerHandle_Shoot,this,&AAWeapon::Shoot,TimeBetweenShot,true,FirstDelay);
}

void AAWeapon::Shoot()
{
	
	if (ProjectileClass != nullptr)
	{
		//UWorld* const World = GetWorld();
		AActor* MyOwner = GetOwner();
		if (MyOwner)
		{
			FVector EyeLocation;
			FRotator EyeRotation;
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
			FVector ShotDirection = EyeRotation.Vector();
			
			FVector MuzzleLocation = StaticMeshComponent->GetSocketLocation(MuzzleSocketName);
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			ActorSpawnParams.Instigator = MyOwner->GetInstigator();
			GetWorld()->SpawnActor<AMainBullet>(ProjectileClass,MuzzleLocation,EyeRotation,ActorSpawnParams);

			LastFireTime = GetWorld()->TimeSeconds;
		}

		
		LastFireTime = GetWorld()->TimeSeconds;
	}
}

void AAWeapon::StopShoot()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Shoot);
}

void AAWeapon::ChangeAmmo(TSubclassOf<AMainBullet> NewAmmo)
{
	ProjectileClass = NewAmmo;
}

