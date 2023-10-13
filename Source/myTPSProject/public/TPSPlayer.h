// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, class UInputComponent*);

UCLASS()
class MYTPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	FInputBindingDelegate onInputBindingDelegate;

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* tpsCamComp;

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class USkeletalMeshComponent* gunMeshComp;

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;

public:
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerbaseComponent* playerMove;

	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerbaseComponent* playerFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health)
	int32 hp;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int32 initialHp = 10;

	UFUNCTION(BlueprintCallable, Category = Health)
	void OnHitEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health) // BlueprintNativeEvent는 블루프린트로 덮어쓰는 방식
	void OnGameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Health)
	void OnUsingGrenade(bool isGrenade);
};