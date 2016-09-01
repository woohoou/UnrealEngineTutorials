// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "FloatingObject.h"


// Sets default values
AFloatingObject::AFloatingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloatingObject::BeginPlay()
{
	Super::BeginPlay();
    RunningTime = 0.0f;
}

// Called every frame
void AFloatingObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    float DeltaHeight = (FMath::Sin((RunningTime + DeltaTime) * 60.0f) - FMath::Sin(RunningTime * 60.0f));
    FVector CurrentActorLocation = this->GetActorLocation();
    NewPosition.Z = CurrentActorLocation.Z + (DeltaHeight * 10.0f);
    NewPosition.X = CurrentActorLocation.X;
    NewPosition.Y = CurrentActorLocation.Y;
    
    UE_LOG(LogTemp, Warning, TEXT("New Position: %f"), NewPosition.X)
    
    RunningTime += DeltaTime;
    
    SetActorLocation(NewPosition);
 
}