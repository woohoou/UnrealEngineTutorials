// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "ParentActor.h"


// Sets default values
AParentActor::AParentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AParentActor::BeginPlay()
{
	Super::BeginPlay();

	AAttachedActor* AttachedActor = GetWorld()->SpawnActor<AAttachedActor>();
	this->AttachRootComponentToActor(AttachedActor);
}

// Called every frame
void AParentActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

