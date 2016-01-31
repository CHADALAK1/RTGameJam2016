// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actors/PickupBase.h"
#include "GravityBoost.generated.h"

/**
 * 
 */
UCLASS()
class RTJAM_API AGravityBoost : public APickupBase
{
	GENERATED_BODY()
	
	
public:

	virtual void OnPickupOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	
};
