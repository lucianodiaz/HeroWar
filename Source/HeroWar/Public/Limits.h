// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Limits.generated.h"

class UBoxComponent;
UCLASS()
class HEROWAR_API ALimits : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALimits();

protected:

	UPROPERTY(VisibleDefaultsOnly,Category="Component")
	UBoxComponent* BoxComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
