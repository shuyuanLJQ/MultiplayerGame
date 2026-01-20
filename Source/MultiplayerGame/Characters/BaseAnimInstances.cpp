// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAnimInstances.h"
#include "MultiplayerGame/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseAnimInstances::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	BaseCharacters = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstances::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (nullptr != BaseCharacters)
	{
		BaseCharacters = Cast<ABaseCharacter>(TryGetPawnOwner());
	}
	if (BaseCharacters == nullptr) return;

	FVector Velocity = BaseCharacters->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	BIsInAir = BaseCharacters->GetCharacterMovement()->IsFalling();//判断角色是否在空中，根据移动组件传回的是否在下落进行判断

	BIsAccelerating = BaseCharacters->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
