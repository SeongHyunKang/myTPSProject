// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "TPSPlayer.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "myTPSProject.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAnim.h"

// Sets default values
UEnemyFSM::UEnemyFSM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
}

// Called when the game starts or when spawned
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();
	// UE_LOG(LogTemp, Warning, TEXT("UEnemyFSM BeginPlay called"));

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
	target = Cast<ATPSPlayer>(actor);
	me = Cast<AEnemy>(GetOwner());
	
	anim = Cast<UEnemyAnim>(me->GetMesh()->GetAnimInstance());
}

// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// UE_LOG(LogTemp, Warning, TEXT("UEnemyFSM TickComponent called"));

	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}

void UEnemyFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		currentTime = 0;

		anim->animState = mState;
	}
}

void UEnemyFSM::MoveState()
{
	FVector destination = target->GetActorLocation();

	FVector dir = destination - me->GetActorLocation();

	me->AddMovementInput(dir.GetSafeNormal());

	if (dir.Size() < attackRange)
	{
		mState = EEnemyState::Attack;

		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime;
	}
}

void UEnemyFSM::AttackState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	
	if (currentTime > attackDelayTime)
	{
		PRINT_LOG(TEXT("Attack!!!!!"));
		currentTime = 0;

		anim->bAttackPlay = true;
	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	
	if (distance > attackRange)
	{
		mState = EEnemyState::Move;
		anim->animState = mState;
	}
}

void UEnemyFSM::OnDamageProcess()
{
	hp--;

	if (hp > 0)
	{
		mState = EEnemyState::Damage;

		currentTime = 0;
		int32 index = FMath::RandRange(0, 1);
		FString sectionName = FString::Printf(TEXT("Damage%d"), 0);
		anim->PlayDamageAnim(FName(*sectionName));
	}
	else
	{
		mState = EEnemyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		anim->animState = mState;
	}
}

void UEnemyFSM::DamageState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
}

void UEnemyFSM::DieState()
{
	FVector P0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;

	me->SetActorLocation(P);

	if (P.Z < -200.0f)
	{
		me->Destroy();
	}
}