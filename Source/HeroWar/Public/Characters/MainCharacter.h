// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Intefaces/PushedObject.h"
#include "MainCharacter.generated.h"


class USHealthComponent;
class AAWeapon;
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void StartShoot();

	void StopShoot();

protected:
	UPROPERTY(BlueprintReadOnly)
	AAWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USHealthComponent* HealthComponent;
	
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<AAWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float RotationSpeed = 45;

	UPROPERTY(BlueprintReadWrite,Category="Weapon")
	bool bIsShooting;
	
	UFUNCTION(BlueprintCallable)
	virtual void Pushed(FVector Impulse) override;

};
