// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SHealthComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...

	DefaultHealth = 2.0f;
	SetIsReplicatedByDefault(true);
	bIsDead = false;
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(GetOwnerRole() == ROLE_Authority)
	{
		AActor* MyOwner = GetOwner();

		if(MyOwner)
		{
			MyOwner->OnTakeAnyDamage.AddDynamic(this,&USHealthComponent::HandleTakeAnyDamage);
		}
	}


	Health = DefaultHealth;
}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage,0.0f,DefaultHealth);

	UE_LOG(LogTemp,Log,TEXT("Health changed: %s"), *FString::SanitizeFloat(Health));

	bIsDead = Health <= 0.0f;

	OnHealthChanged.Broadcast(Health,Damage,DamageType,InstigatedBy,DamageCauser);

	//ASGameMode* GM = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());

	if(bIsDead)
	{
		// if(GM)
		// {
		// 	GM->OnActorKilled.Broadcast(GetOwner(),DamageCauser,InstigatedBy);
		// }
	}

}

void USHealthComponent::Heal(float HealAmount)
{
	if(HealAmount <= 0.0f || Health <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health+HealAmount,0.0f,DefaultHealth);
	UE_LOG(LogTemp,Log,TEXT("Health changed: %s (+%s) "),*FString::SanitizeFloat(Health),*FString::SanitizeFloat(HealAmount));
	OnHealthChanged.Broadcast(Health,-HealAmount,nullptr,nullptr,nullptr);
}

float USHealthComponent::GetHealth() const
{
	return  Health;
}

bool USHealthComponent::IsDead()
{
	return  bIsDead;
}

void USHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USHealthComponent,Health);
}
