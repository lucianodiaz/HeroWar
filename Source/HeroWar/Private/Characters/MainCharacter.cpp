// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacter.h"

#include "AWeapon.h"
#include "Engine/StaticMeshActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	WeaponSocketName = "GunSocket";
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParameters;
	
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<AAWeapon>(DefaultWeaponClass,FVector::ZeroVector,FRotator::ZeroRotator,SpawnParameters);
	CurrentWeapon->SetOwner(this);
	CurrentWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,WeaponSocketName);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::StartShoot);
	PlayerInputComponent->BindAction("Shoot",IE_Released,this,&AMainCharacter::StopShoot);
}

void AMainCharacter::StartShoot()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->StartShoot();
		bIsShooting = true;
	}
}

void AMainCharacter::StopShoot()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->StopShoot();
		bIsShooting = false;
	}
}

void AMainCharacter::Pushed(FVector Impulse)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "PUSH");
	
	LaunchCharacter(Impulse,false,false);
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}
void AMainCharacter::MoveRight(float Value)
{
	AddControllerYawInput(Value * RotationSpeed * GetWorld()->GetDeltaSeconds());

}
