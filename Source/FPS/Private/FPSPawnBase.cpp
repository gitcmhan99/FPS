// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPawnBase.h"
#include "FPS/FPS.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameUtil.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AFPSPawnBase::AFPSPawnBase()
{
    MYLOG("Start AFPSPawnBase()");

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = GameUtil::CreateRootComponent<UCapsuleComponent>(this);
    CapsuleComponent->SetCapsuleHalfHeight(90.0f);
    CapsuleComponent->SetCapsuleRadius(40.0f);
    CapsuleComponent->SetLineThickness(5.0f);

    SkeletalMeshComponent = GameUtil::CreateComponent<USkeletalMeshComponent>(
        this,
        true,
        CapsuleComponent);

    FVector NewLocation(0.f, 0.f, -80.0f);
    FRotator NewRotation(0.f, -90.0f, 0.f);
    SkeletalMeshComponent->SetRelativeLocationAndRotation(NewLocation, NewRotation);

    SpringArmComponent =
        GameUtil::CreateComponent<USpringArmComponent>(this, true, CapsuleComponent);

    SpringArmComponent->TargetArmLength = 400.0f;
    SpringArmComponent->SetRelativeRotation(FRotator(-15.0f, 0.f, 0.f));

    CameraComponent = GameUtil::CreateComponent<UCameraComponent>(this, true, SpringArmComponent);

    FloatingPawnMovement = GameUtil::CreateActorComponent<UFloatingPawnMovement>(this);

    MYLOG("End AFPSPawnBase()");
}

// Called when the game starts or when spawned
void AFPSPawnBase::BeginPlay()
{
    MYLOG("Start AFPSPawnBase::BeginPlay()");

	Super::BeginPlay();

    APlayerController* playerController = Cast<APlayerController>(GetController());

    if (playerController)
    {
        //FInputModeGameAndUI   InputModeGameAndUI;
        //FInputModeUIOnly      InputModeUIOnly;

        FInputModeGameOnly InputModeGameOnly;
        playerController -> SetInputMode(InputModeGameOnly);
    }

    {
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

    MYLOG("End AFPSPawnBase::BeginPlay()");
}

// Called every frame
void AFPSPawnBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    MYLOG("Start AFPSPawnBase::SetupPlayerInputComponent()");

	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //PlayerInputComponent->BindAxis(TEXT("UPDown"), this, &ThisClass::UpDown);
    //PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::LeftRight);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent == nullptr)
    {
        return;
    }

    EnhancedInputComponent->BindAction(
        IA_Move,
        ETriggerEvent::Triggered,
        this,
        &AFPSPawnBase::OnMove);
}

void AFPSPawnBase::PostInitializeComponents()
{
    MYLOG("Start AFPSPawnBase::PostInitializeComponents()");

    Super::PostInitializeComponents();

    MYLOG("End AFPSPawnBase::PostInitializeComponents()");
}

void AFPSPawnBase::PossessedBy(AController* NewController)
{
    MYLOG("Start AFPSPawnBase::PossessedBy() %s", *NewController->GetName());

    Super::PossessedBy(NewController);

    MYLOG("End AFPSPawnBase::PossessedBy() %s", *NewController->GetName());
}

void AFPSPawnBase::UnPossessed()
{
    MYLOG("Start AFPSPawnBase::UnPossessed()");

    Super::UnPossessed();

    MYLOG("End AFPSPawnBase::UnPossessed()");
}

void AFPSPawnBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    MYLOG("Start AFPSPawnBase::EndPlay() EndPlayReason: %d", EndPlayReason);

    Super::EndPlay(EndPlayReason);

    MYLOG("End AFPSPawnBase::EndPlay() EndPlayReason: %d", EndPlayReason);
}

void AFPSPawnBase::OnMove(const FInputActionValue& InputValue)
{
    FVector2D MoveValue = InputValue.Get<FVector2D>();

    MYSCREENLOG("Move X: %f, Y: %f", MoveValue.X, MoveValue.Y);
}

void AFPSPawnBase::UpDown(float InAxisValue)
{
    MYSCREENLOG("InAxisValue: %f", InAxisValue);
    AddMovementInput(GetActorForwardVector(), InAxisValue);
} 

void AFPSPawnBase::LeftRight(float InAxisValue)
{
    MYSCREENLOG("LeftRight: %f", InAxisValue);
    AddMovementInput(GetActorRightVector(), InAxisValue);
}

