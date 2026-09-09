// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameUtil.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "FPSInputActions.h"
#include "FPS/FPS.h"


// Sets default values
AFPSCharacterBase::AFPSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 25.f;
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.3f;
    GetCharacterMovement()->BrakingDecelerationWalking = 1800.f;

    GetCapsuleComponent()->InitCapsuleSize(90.f, 40.f);
    GetCapsuleComponent()->SetLineThickness(5.f);

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
    GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    SpringArmComponent = GameUtil::CreateComponent<USpringArmComponent>(this);
    SpringArmComponent->TargetArmLength = 400.f;

    CameraComponent = GameUtil::CreateComponent<UCameraComponent>(this, true, SpringArmComponent);
}

// Called when the game starts or when spawned
void AFPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController == nullptr)
    {
        return;
    }

    ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
    if (LocalPlayer == nullptr)
    {
        return;
    }

    UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (InputSubsystem == nullptr)
    {
        return;
    }

    InputSubsystem->AddMappingContext(IMC_Player, 0);
}

// Called every frame
void AFPSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent == nullptr)
    {
        return;
    }

    EnhancedInputComponent->BindAction(
        InputActions->Move,
        ETriggerEvent::Triggered,
        this,
        &AFPSCharacterBase::OnMove);
}

void AFPSCharacterBase::OnMove(const FInputActionValue& InputValue)
{
    FVector2D MoveValue = InputValue.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MoveValue.X);
    AddMovementInput(GetActorRightVector(), MoveValue.X);

    MYSCREENLOG("Move X: %f, Y: %f", MoveValue.X, MoveValue.Y);
}

