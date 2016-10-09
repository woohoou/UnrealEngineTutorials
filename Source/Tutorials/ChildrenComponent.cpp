// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "ChildrenComponent.h"


// Sets default values for this component's properties
UChildrenComponent::UChildrenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	UChildActorComponent* Children1 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Children1"));
	UChildActorComponent* Children2 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Children2"));
	UChildActorComponent* Children3 = CreateDefaultSubobject<UChildActorComponent>(TEXT("Children3"));

	Children1->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	Children2->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	Children3->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);

	Children1->CreateChildActor();
	Children1->SetRelativeLocation(FVector(FMath::FRandRange(0.0f, 20.0f), FMath::FRandRange(0.0f, 20.0f), 50.0f));

	UStaticMeshComponent* Children1Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildrenMesh1"));
	Children1Mesh->SetupAttachment(Children1);

	Children2->CreateChildActor();
	Children2->SetRelativeLocation(FVector(FMath::FRandRange(-100.0f, 100.0f), FMath::FRandRange(-100.0f, 100.0f), 50.0f));

	UStaticMeshComponent* Children2Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildrenMesh2"));
	Children2Mesh->SetupAttachment(Children2);

	Children3->CreateChildActor();
	Children3->SetRelativeLocation(FVector(FMath::FRandRange(-100.0f, 100.0f), FMath::FRandRange(-100.0f, 100.0f), 50.0f));

	UStaticMeshComponent* Children3Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChildrenMesh3"));
	Children3Mesh->SetupAttachment(Children3);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	if (ConeVisualAsset.Succeeded()) {
		Children1Mesh->SetStaticMesh(ConeVisualAsset.Object);
		Children1Mesh->SetRelativeScale3D(FVector(0.2));

		Children2Mesh->SetStaticMesh(ConeVisualAsset.Object);
		Children2Mesh->SetRelativeScale3D(FVector(0.2));

		Children3Mesh->SetStaticMesh(ConeVisualAsset.Object);
		Children3Mesh->SetRelativeScale3D(FVector(0.2));
	}
}


// Called when the game starts
void UChildrenComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UChildrenComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

