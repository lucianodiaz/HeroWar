// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChangedSignature, float, Health,
											float, HealthDelta, const class UDamageType*, DamageType,
											class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROWAR_API USHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USHealthComponent();

	protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsDead;

	UPROPERTY(Replicated,BlueprintReadOnly,Category="HealthComponent")
	float Health;

	UPROPERTY(Replicated,BlueprintReadOnly,Category="HealthComponent")
	int Lives;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HealthComponent")
	float DefaultHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							class AController* InstigatedBy, AActor* DamageCauser);
	
	public:
	
	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnHealthChangedSignature OnHealthChanged;
	
	UFUNCTION(BlueprintCallable, Category="HealthComponent")
	void Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category="HealthComponent")
	void Restore();

	float GetHealth() const;

	int GetLives() const;

	UFUNCTION(BlueprintCallable)
	bool IsDead();
		
};
