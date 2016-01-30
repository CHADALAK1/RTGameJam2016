// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RTJamCharacter.generated.h"

UCLASS(config=Game)
class ARTJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:

	/*Force to Add in Direction of Character*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
		FVector ForceLength;

	/*Absolute World Max Height*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Limits")
		float MaxHeight;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/**Overriding jump to add more jumps.
	TODO: Add cooldown for every jump*/
	virtual void Jump() override;

private:

	/** checks to see if the Character is dead(Essentially when Character hits the ground)*/
	bool bIsDead;


public:
	ARTJamCharacter();

	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns bIsDead boolean(Callable throught BP for Level BP*/
	UFUNCTION(BlueprintCallable, Category = Dead)
	bool IsDead() const { return bIsDead; }

	//used to help limit force strength based on altitude of the character
	FORCEINLINE static float LerpFloat(const float A, const float B, const float Alpha){ return A + Alpha*(B - A); };
};
