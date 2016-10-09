// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "OrbitComponent.h"


UOrbitComponent::UOrbitComponent() {
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if(BoxVisualAsset.Succeeded()) {
		Mesh->SetStaticMesh(BoxVisualAsset.Object);
	}

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("OrbitComponent"));

	UE_LOG(LogTemp, Warning, TEXT("GetComponentLocation InitialLocation is %s"),
		*this->GetComponentLocation().ToString());

	InitialLocation = FVector(-50.0f, -50.0f, 20.0f);
}

void UOrbitComponent::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BoxComponent InitialLocation is %s"),
		*InitialLocation.ToString());

	UE_LOG(LogTemp, Warning, TEXT("GetComponentLocation InitialLocation is %s"),
		*this->GetComponentLocation().ToString());

	FVector BoxInitialLocation = InitialLocation;
	Mesh->SetRelativeLocation(BoxInitialLocation);
	Mesh->SetWorldScale3D(FVector(FMath::FRandRange(0.1, 0.3)));

	RotatingComponent->UpdatedComponent = Mesh;
	RotatingComponent->PivotTranslation = FVector(InitialLocation.X*-1, InitialLocation.Y*-1, 0.0f);
	RotatingComponent->RotationRate = FRotator(0.0f, FMath::FRandRange(50.0, 100.0), 0.0f);
}

