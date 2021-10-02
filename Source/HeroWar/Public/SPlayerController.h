// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

class ASPlayerState;
/**
 * 
 */
UCLASS()
class HEROWAR_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

	ASPlayerController();

	public:

	UFUNCTION(BlueprintImplementableEvent,Category="PlayerController")
	void OnStartMatch(ASPlayerController* PClocal, const TArray<ASPlayerState*>& PlayerStates);
};
