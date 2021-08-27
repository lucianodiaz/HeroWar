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

	UPROPERTY(VisibleDefaultsOnly,Category = Projectile)
	UStaticMeshComponent* StaticMeshComponent;

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
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float Damage;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageCauser;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float PushStrenght = 100.0f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float PushPitchAngle = 50.0f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float InitialSpeed = 1000.0f;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float MaxSpeed = 1000.0f;

	FTimerHandle Destroy_TimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimerDestroyAmount = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystem* ExplosionParticle;
};
