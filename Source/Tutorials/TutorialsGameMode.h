// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "TutorialsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALS_API ATutorialsGameMode : public AGameMode
{
	GENERATED_BODY()

	virtual void StartPlay() override;
	
	
};
