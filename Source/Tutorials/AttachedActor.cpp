// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "AttachedActor.h"


// Sets default values
AAttachedActor::AAttachedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttachedBoxComponent"));

	this->RootComponent = BoxComponent;

	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachedMesh"));
	Mesh->SetupAttachment(BoxComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (BoxVisualAsset.Succeeded()) {
		Mesh->SetStaticMesh(BoxVisualAsset.Object);
		Mesh->SetRelativeScale3D(FVector(2.0));
	}
}

// Called when the game starts or when spawned
void AAttachedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttachedActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

