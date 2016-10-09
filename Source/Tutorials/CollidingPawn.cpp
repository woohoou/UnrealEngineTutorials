// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "CollidingPawn.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create SphereComponent and set to this->RootComponent
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	this->RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Add StaticMeshComponent to SphereComponent
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(this->RootComponent);

	// Find StaticMesh Asset and set to StaticMeshComponent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Create a ParticleSystemComponent and Attach To StaticMeshComponent
	OurParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystemComponent->SetupAttachment(SphereVisual);
	OurParticleSystemComponent->bAutoActivate = false;
	OurParticleSystemComponent->SetRelativeLocation(FVector(-20.f, 0.0f, 20.0f));

	// Find ParticleSystem Asset and set as Template of our ParticleSystemComponent
	static ConstructorHelpers::FObjectFinder<UParticleSystem>  ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded()) {
		OurParticleSystemComponent->SetTemplate(ParticleAsset.Object);
	}

	// Create SpringArmComponent for smooth camera and sliding collisions and attach to RootComponent (SphereComponent)
	USpringArmComponent* SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArmComponent->SetupAttachment(this->RootComponent);
	SpringArmComponent->SetRelativeRotation(FRotator(-45.0, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 3.0f;

	// Create a CameraComponent and attach to SpringArmComponent
	UCameraComponent* CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	// CollidingPawn posses input of Input::Player0
	this->AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our CollidingPawnMovementComponent has inheritance of PawnMovementComponent
	// and add RootComponent (SphereComponent) to UpdatedComponent
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = this->RootComponent;

	/* OrbitStaticMeshComponent */
	UOrbitComponent* OrbitComponent = CreateDefaultSubobject<UOrbitComponent>(TEXT("P0"));
	OrbitComponent->SetupAttachment(this->RootComponent);

}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACollidingPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	InputComponent->BindAxis("MoveX", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveY", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

// Return MovementComponent in override of virtual function GetMovementComponent
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const {
	return OurMovementComponent;
}

// MoveForward with Axisalue
void ACollidingPawn::MoveForward(float AxisValue) {
	if (this->OurMovementComponent && (this->OurMovementComponent->UpdatedComponent == this->RootComponent)) {
		this->OurMovementComponent->AddInputVector(this->GetActorForwardVector() * AxisValue);
	}
}

// MoveRight with AxisValue
void ACollidingPawn::MoveRight(float AxisValue) {
	if (this->OurMovementComponent && (this->OurMovementComponent->UpdatedComponent == this->RootComponent)) {
		this->OurMovementComponent->AddInputVector(this->GetActorRightVector() * AxisValue);
	}
}

// Turn rotation with AxisValue
void ACollidingPawn::Turn(float AxisValue) {
	FRotator NewRotation = this->GetActorRotation();
	NewRotation.Yaw += AxisValue;
	this->SetActorRotation(NewRotation);
}

// Toggle our ParticleSystem
void ACollidingPawn::ParticleToggle() {
	if (this->OurParticleSystemComponent && this->OurParticleSystemComponent->Template) {
		this->OurParticleSystemComponent->ToggleActive();
	}
}