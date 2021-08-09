// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/MainBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Intefaces/PushedObject.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AMainBullet::AMainBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AMainBullet::OnHit);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMainBullet::BeginOverlap);
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 1 seconds by default
	InitialLifeSpan = 0.2f;
	//UpVector = FVector(0.0f, 0.0f, 100.0f);

}

// Called when the game starts or when spawned
void AMainBullet::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(Destroy_TimerHandle, this, &AMainBullet::ClearAmmo, TimerDestroyAmount, true);
}

void AMainBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void AMainBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//IPushedObject* pushedObject = Cast<IPushedObject>(OtherActor);

	if (OtherActor != nullptr && OtherActor != this)
	{
		IPushedObject* pushedObject = Cast<IPushedObject>(OtherActor);

		FRotator PushDirecton = GetActorRotation();

		PushDirecton.Pitch += PushPitchAngle;

		FVector ForceVelocity = PushDirecton.Vector() * PushStrenght;
		
		if (pushedObject != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, OtherActor->GetFName().ToString());
			pushedObject->Pushed(ForceVelocity);
			ClearAmmo();
		}

	}

	if (ExplosionParticle != nullptr && OtherActor != this)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation());
	}
}

void AMainBullet::ClearAmmo()
{
	Destroy();
}


