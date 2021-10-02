// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "Net/UnrealNetwork.h"

ASPlayerState::ASPlayerState()
{
	PlayerLives = 3;
}

void ASPlayerState::OnRep_PlayerLives()
{
	OldPlayerLives = GetPlayerLives();
	
}

int ASPlayerState::GetPlayerLives()
{
	return PlayerLives;
}

void ASPlayerState::SetPlayerLives(int NewLive)
{
		OldPlayerLives = PlayerLives;
		PlayerLives = NewLive;
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(ASPlayerState, PlayerLives, SharedParams);
}