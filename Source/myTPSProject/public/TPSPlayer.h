// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class MYTPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

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

	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	void InputFire();

	UPROPERTY(VisibleAnywhere, Category = GunMesh)
	class UStaticMeshComponent* sniperGunComp;

	bool bUsingGrenadeGun = true;

	void ChangeToGrenadeGun();

	void ChangeToSniperGun();

	void SniperAim();

	bool bSniperAim = false;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> sniperUIFactory;

	class UUserWidget* _sniperUI;

	UPROPERTY(EditAnywhere, Category = BulletEffect)
	class UParticleSystem* bulletEffectFactory;

	UPROPERTY(EditDefaultsOnly, Category = SniperUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;

	class UUserWidget* _crosshairUI;

	UPROPERTY(EditDefaultsOnly, category = CameraMotion)
	TSubclassOf<class UCameraShakeBase> cameraShake;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* bulletSound;

public:
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerbaseComponent* playerMove;
};