// Fill out your copyright notice in the Description page of Project Settings.

#include "RTJam.h"
#include "GravityBoost.h"


void AGravityBoost::OnPickupOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	Super::OnPickupOverlap(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ARTJamCharacter *Char = Cast<ARTJamCharacter>(OtherActor);

	if (Char)
	{
		Char->GravityTimer();
		Destroy();
	}
}

