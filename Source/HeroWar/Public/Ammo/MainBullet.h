// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainBullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class HEROWAR_API AMainBullet : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	AMainBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Overlap
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	void ClearAmmo();
public:
	//Variables

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PushStrenght = 100.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PushPitchAngle = 50.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InitialSpeed = 1000.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxSpeed = 1000.0f;

	/*UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector UpVector;*/

	FTimerHandle Destroy_TimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimerDestroyAmount = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* ExplosionParticle;
};
