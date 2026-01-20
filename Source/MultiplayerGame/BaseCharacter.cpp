// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建并设置弹簧臂
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh()); // 挂载到角色骨骼
	CameraBoom->TargetArmLength = 600.f; // 相机与角色的距离
	CameraBoom->bUsePawnControlRotation = true; // 弹簧臂跟随玩家视角转动
	
	// 创建并设置跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// 将相机挂载到弹簧臂的末端Socket
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 相机不跟随玩家直接旋转，而是跟随弹簧臂
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis("Lookup", this, &ABaseCharacter::Lookup);
}


void ABaseCharacter::MoveForward(float Value)
{
	if (nullptr != Controller && 0.f != Value)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (nullptr != Controller && 0.f != Value) 
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABaseCharacter::Lookup(float Value)
{
	AddControllerPitchInput(Value);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


