// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "CameraDirector.h"


// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CameraIndex = 0;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    TimeToNextCameraChange -= DeltaTime;
    
    if(TimeToNextCameraChange <= 0.0f){
        TimeToNextCameraChange += Cameras[CameraIndex].TimeBetweenCameraChanges;
        
        // Find the actor that handles control for the local player
        APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
        
        if(OurPlayerController){
            OurPlayerController->SetViewTargetWithBlend(Cameras[CameraIndex].CameraActor, Cameras[CameraIndex].SmoothBlendTime);
            if(Cameras.Num() > 0){
                if(CameraIndex > 0 && CameraIndex+1 == Cameras.Num()) {
                    CameraIndex = 0;
                } else {
                    CameraIndex++;
                }
            }
            
            /*
            if(OurPlayerController->GetViewTarget() != Cameras[0] && Cameras[0] != nullptr){
                // Cut instantly to CameraOne
                OurPlayerController->SetViewTarget(Cameras[0]);
            } else if(OurPlayerController->GetViewTarget() != Cameras[1] && Cameras[1] != nullptr){
                // Change smoothly to CameraTwo
                OurPlayerController->SetViewTargetWithBlend(Cameras[1], SmoothBlendTime);
            }
            */
        }
    }

}

