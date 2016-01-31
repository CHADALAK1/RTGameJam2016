// Fill out your copyright notice in the Description page of Project Settings.

#include "RTJam.h"
#include "PickupBase.h"



// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickupOverlap);
	Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = Mesh;

	Aura = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Aura"));
	Aura->AttachTo(RootComponent);


}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	this->SetActorRelativeRotation(FRotator(this->GetActorRotation().Pitch, this->GetActorRotation().Yaw + 1, this->GetActorRotation().Roll));

}

void APickupBase::OnPickupOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

}