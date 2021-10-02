// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameState.h"

#include "SPlayerController.h"

void ASGameState::MulticastOnStartMatch_Implementation(const TArray<ASPlayerState*>& PlayerStates)
{
	for(FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It;++It)
	{
		ASPlayerController* PClocal = Cast<ASPlayerController>(It->Get());
		if(PClocal && PClocal->IsLocalController())
		{
			PClocal->OnStartMatch(PClocal,PlayerStates);
		}
	}
}
