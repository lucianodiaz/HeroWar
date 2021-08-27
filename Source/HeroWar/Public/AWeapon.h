// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ammo/MainBullet.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"

UCLASS()
class HEROWAR_API AAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_Shoot;

	float TimeBetweenShot;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly,Category="Weapon");
	float RateOfFire;

	UPROPERTY(VisibleDefaultsOnly,Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* MuzzleEffect;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	void Shoot();

	//Variables
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AMainBullet> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AMainBullet> DefaultProjectileClass;


	public:
	
	void StartShoot();

	void StopShoot();

	UFUNCTION(BlueprintCallable)
	void ChangeAmmo(TSubclassOf<AMainBullet> NewAmmo);
};
