// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PushedObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPushedObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HEROWAR_API IPushedObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Pushed(FVector Impulse) = 0;
};
