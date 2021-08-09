// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacter.h"
#include "Engine/StaticMeshActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::Shoot);
}

void AMainCharacter::StartShoot()
{
	//GetWorldTimerManager().SetTimer()
}

void AMainCharacter::Shoot()
{

	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();

		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();

			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AMainBullet>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AMainCharacter::StopShoot()
{
}

void AMainCharacter::Pushed(FVector Impulse)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "PUSH");
	
	
	LaunchCharacter(Impulse,false,false);

}

void AMainCharacter::ChangeAmmo(TSubclassOf<AMainBullet> NewAmmo)
{
	ProjectileClass = NewAmmo;
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "value" + FString::SanitizeFloat(value));
}
void AMainCharacter::MoveRight(float Value)
{
	AddControllerYawInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, "value" + FString::SanitizeFloat(value));
}
