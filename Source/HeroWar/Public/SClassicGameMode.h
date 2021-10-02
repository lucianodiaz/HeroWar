// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "SClassicGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorKilled,AActor*,VictimActor,AController*,VictimController);

/**
* 
*/
UCLASS()
class HEROWAR_API ASClassicGameMode : public AGameMode
{
	GENERATED_BODY()

	public:
	ASClassicGameMode();

	UPROPERTY(BlueprintAssignable,Category="Gameplay")
	FOnActorKilled OnActorKilled;

	virtual void BeginPlay() override;

	void CheckStartMatch();

	FTimerHandle TimerHandle_CheckStartMatch;
};
