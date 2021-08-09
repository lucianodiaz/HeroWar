// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Intefaces/PushedObject.h"
#include "Ammo/MainBullet.h"
#include "MainCharacter.generated.h"


UCLASS()
class HEROWAR_API AMainCharacter : public ACharacter, public IPushedObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Funciones
private:
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartShoot();

	void Shoot();

	void StopShoot();

public:
	//Methods

	UFUNCTION(BlueprintCallable)
	void Pushed(FVector Impulse) override;

	//UFUNCTION()
	void ChangeAmmo(TSubclassOf<AMainBullet> NewAmmo);
public:
	//Variables

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AMainBullet> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AMainBullet> DefaultProjectileClass;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	FVector GunOffset;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float RotationSpeed = 45;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ShootingRange = 500;
};
