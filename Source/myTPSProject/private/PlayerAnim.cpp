// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include "GameFramework/characterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();

	auto player = Cast<ATPSPlayer>(ownerPawn);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forwardVector = player->GetActorForwardVector();

		speed = FVector::DotProduct(forwardVector, velocity);

		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}