// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPlayerState.h"
#include "GameFramework/GameState.h"
#include "SGameState.generated.h"

class ASPlayerController;
/**
 * 
 */
UCLASS()
class HEROWAR_API ASGameState : public AGameState
{
	GENERATED_BODY()


	public:

	UFUNCTION(BlueprintCallable,NetMulticast,Reliable)
	void MulticastOnStartMatch(const TArray<ASPlayerState*>& PlayerStates);
};
