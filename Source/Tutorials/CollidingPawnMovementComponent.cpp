// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "CollidingPawnMovementComponent.h"




void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!this->PawnOwner || !this->UpdatedComponent || this->ShouldSkipUpdate(DeltaTime)) {
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector DesiredMovementThisFrame = this->ConsumeInputVector().GetClampedToMaxSize(1.0) * DeltaTime * 150.0f;

	if (!DesiredMovementThisFrame.IsNearlyZero()) {
		FHitResult Hit;

		this->SafeMoveUpdatedComponent(DesiredMovementThisFrame, this->UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit()) {
			this->SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}

}