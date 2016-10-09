// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "OrbitComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TUTORIALS_API UOrbitComponent : public UBoxComponent
{
	GENERATED_BODY()

	UBoxComponent* BoxComponent;
	URotatingMovementComponent* RotatingComponent;
	FVector BoxInitialLocation;
	
public:
	UOrbitComponent();
	void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	FVector InitialLocation;
};
