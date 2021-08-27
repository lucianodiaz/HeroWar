// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLaunchPad.generated.h"

class UBoxComponent;
UCLASS()
class HEROWAR_API ASLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Component")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere,Category="Launch")
	float LaunchStrenght;
	
	UPROPERTY(EditAnywhere, Category = "Launch")
	float LaunchPitchAngle;
	
	public:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
