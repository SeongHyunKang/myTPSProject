// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerbaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYTPSPROJECT_API UPlayerbaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerbaseComponent()
	{
		PrimaryComponentTick.bCanEverTick = false;
		bWantsInitializeComponent = true;
	};

	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	UPROPERTY()
	ATPSPlayer* me;

	UPROPERTY()
	UCharacterMovementComponent* moveComp;

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) {};

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
