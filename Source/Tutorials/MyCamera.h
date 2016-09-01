// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCamera.generated.h"

USTRUCT()
struct TUTORIALS_API FMyCamera
{
    GENERATED_BODY()
    
    FMyCamera();
    
    UPROPERTY(EditAnywhere)
    AActor* CameraActor;
    
    UPROPERTY(EditAnywhere)
    float SmoothBlendTime;
    
    UPROPERTY(EditAnywhere)
    float TimeBetweenCameraChanges;
};