// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "MyPawn.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    // Create a camera and visible object
    // Camera
    UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    // Visible Object
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
    
    // Attach our camera and visible object to our root component
    // Attach camera to root component
    OurCamera->AttachTo(RootComponent);
    OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
    OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
    
    // Attach visible object to root component
    OurVisibleComponent->AttachTo(RootComponent);
    
    AccelerationX = 0.0f;
    AccelerationX = 0.0f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    UE_LOG(LogTemp, Warning, TEXT("DeltaTime %f"), DeltaTime);
    
    // Handle growing and shrinking basen on our "Grow" action
    {
        float CurrentScale = OurVisibleComponent->GetComponentScale().X;
        if(bGrowing){
            // Grow to double size over the course of one second
            CurrentScale += DeltaTime;
        } else {
            // Shrink half as fast as we grow
            CurrentScale -= (DeltaTime * 0.5f);
        }
        
        // Make sure we never drop below our starting size, or increase past double size
        CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
        OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
    }
    
    // Handle movement based on our "MoveX" and "MoveY" axes
    {
        FVector NewLocation = GetActorLocation() + CurrentVelocity;

        UE_LOG(LogTemp, Warning, TEXT("NewLocation: %s"), *NewLocation.ToString())
        
        SetActorLocation(NewLocation);
    }

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    // Respond when our grow key is pressed
    InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
    InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);
    InputComponent->BindAction("InstantGrow", IE_Pressed, this, &AMyPawn::InstantGrow);

    // Respond every frame to the values of our two movements
    InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveX_Axis);
    InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveY_Axis);
}


// Functions for growing and move
void AMyPawn::MoveX_Axis(float Axis){
    if(Axis == 0.0f) {
        MovingX = false;
        AccelerationX = 0.0f;
    } else {
        MovingX = true;
        if(AccelerationX >= 500.0f) {
            AccelerationX = 500.0f;
        } else {
            AccelerationX++;
        }
    }
    
    CurrentVelocity.X = FMath::Clamp(Axis, -1.0f, 1.0f) * AccelerationX;
}

void AMyPawn::MoveY_Axis(float Axis){
    if(Axis == 0.0f) {
        MovingY = false;
        AccelerationY = 0.0f;
    } else {
        MovingY = true;
        if(AccelerationY >= 500.0f) {
            AccelerationY = 500.0f;
        } else {
            AccelerationY++;
        }
    }
    
    CurrentVelocity.Y = FMath::Clamp(Axis, -1.0f, 1.0f) * AccelerationY;
}

void AMyPawn::InstantGrow() {
    if(MovingX || MovingY){
        float CurrentScale = OurVisibleComponent->GetComponentScale().X;
        if(CurrentScale >= 1.0f && CurrentScale < 2.0f) {
            OurVisibleComponent->SetWorldScale3D(FVector(2.0f));
        } else {
            OurVisibleComponent->SetWorldScale3D(FVector(1.0f));
        }
    }
}

void AMyPawn::StartGrowing(){
    bGrowing = true;
}

void AMyPawn::StopGrowing() {
    bGrowing = false;
}

