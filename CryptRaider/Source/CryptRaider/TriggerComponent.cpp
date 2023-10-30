// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* UnlockActor = GetAcceptableActor();
	if (UnlockActor == nullptr) return;
	
	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(UnlockActor->GetRootComponent());
	if(Component != nullptr)
	{
		Component->SetSimulatePhysics(false);
	}
	UnlockActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	if (Mover == nullptr) return;

	bool ShouldMove = UnlockActor != nullptr;
	Mover->SetShouldMove(ShouldMove);
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");

		if (HasAcceptableTag && !IsGrabbed)
		{
			return Actor;
		}
	}

	return nullptr;
}
