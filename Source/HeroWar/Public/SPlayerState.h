// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HEROWAR_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY(ReplicatedUsing = OnRep_PlayerLives)
	int PlayerLives;

	int OldPlayerLives;
	
	public:

	ASPlayerState();
	
	UFUNCTION()
	virtual void OnRep_PlayerLives();
	
	UFUNCTION(BlueprintPure,Category="PlayerState")
	int GetPlayerLives();

	void SetPlayerLives(int NewLive);
};
