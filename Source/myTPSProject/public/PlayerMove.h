// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerbaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class MYTPSPROJECT_API UPlayerMove : public UPlayerbaseComponent
{
	GENERATED_BODY()

public:
	void Turn(float value);

	void LookUp(float value);

	virtual void SetupInputBinding(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

	FVector direction;

	void InputHorizontal(float value);

	void InputVertical(float value);

	void InputJump();

	void Move();

	void InputRun();

public:
	UPlayerMove();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};