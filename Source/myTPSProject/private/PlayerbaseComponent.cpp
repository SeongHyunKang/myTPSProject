// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerbaseComponent.h"

// Sets default values for this component's properties
//UPlayerbaseComponent::UPlayerbaseComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//}


// Called when the game starts
void UPlayerbaseComponent::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<ATPSPlayer>(GetOwner());
	moveComp = me->GetCharacterMovement();
}


// Called every frame
void UPlayerbaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

