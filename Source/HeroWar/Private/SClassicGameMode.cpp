// Fill out your copyright notice in the Description page of Project Settings.


#include "SClassicGameMode.h"

#include "SGameState.h"

ASClassicGameMode::ASClassicGameMode()
{
}

void ASClassicGameMode::BeginPlay()
{
	Super::BeginPlay();

	// GetWorldTimerManager().SetTimer(TimerHandle_CheckStartMatch,this,&ASClassicGameMode::CheckStartMatch,1,true);
}

void ASClassicGameMode::CheckStartMatch()
{
	// if(HasMatchStarted())
	// {
	// 	ASGameState* GS = GetGameState<ASGameState>();
	// 	if(GS)
	// 	{
	// 		//GS->MulticastOnStartMatch();
	// 		GetWorldTimerManager().ClearTimer(TimerHandle_CheckStartMatch);
	// 	}
	// }
}
