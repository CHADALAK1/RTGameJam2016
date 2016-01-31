// Fill out your copyright notice in the Description page of Project Settings.

#include "RTJam.h"
#include "InvincibilityBoost.h"



void AInvincibilityBoost::OnPickupOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ARTJamCharacter *Char = Cast<ARTJamCharacter>(OtherActor);
	if (Char)
	{
		Char->InvincibilityTimer();
		Destroy();
	}
}
