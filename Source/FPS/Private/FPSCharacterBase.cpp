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

#if WITH_EDITOR
    PrimaryActorTick.bCanEverTick = true;
#else
    PrimaryActorTick.bCanEverTick = false;
#endif
}

// Called when the game starts or when spawned
void AFPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

    GameUtil::AddInputMapping(this, IMC_Player);
}

// Called every frame
void AFPSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    switch (CurrentViewMode)
    {
    case EViewType::BACK_VIEW:
        break;
    case EViewType::QUARTER_VIEW:
        if (KINDA_SMALL_NUMBER < DirectionToMove.SizeSquared())
        {
            //Forward 방향의 회전행렬
            FRotator NewRotation = FRotationMatrix::MakeFromX(DirectionToMove).Rotator();
            GetController()->SetControlRotation(NewRotation); //회전행렬만큼 회전

            AddMovementInput(DirectionToMove);
            DirectionToMove = FVector::ZeroVector;
        }
        break;
    }

#if WITH_EDITOR
    FVector LineStart = GetActorLocation() - GetActorForwardVector() * 50.f;
    FVector LineEnd = LineStart + GetControlRotation().Vector() * 500.f;
    FColor Color = FColor::Blue;
    bool bPersistentLines = false;
    float LifeTime = 0;
    uint8 DepthPriority = 0;
    float Thickness = 10.f;

    DrawDebugLine(GetWorld(),
        LineStart,
        LineEnd,
        Color,
        bPersistentLines,
        LifeTime,
        DepthPriority,
        Thickness
    );
#endif
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

    if (InputActions && InputActions->Move)
    {
        EnhancedInputComponent->BindAction(
            InputActions->Move,
            ETriggerEvent::Triggered,
            this,
            &AFPSCharacterBase::OnMove);
    }

    if (InputActions && InputActions->Look)
    {
        EnhancedInputComponent->BindAction(
            InputActions->Look,
            ETriggerEvent::Triggered,
            this,
            &AFPSCharacterBase::OnLook);
    }

    if (InputActions && InputActions->Jump)
    {
        //부모 클래스인 ACharacter에 함수를 연결
        EnhancedInputComponent->BindAction(
            InputActions->Jump,
            ETriggerEvent::Started,
            this,
            &ACharacter::Jump);

        EnhancedInputComponent->BindAction(
            InputActions->Jump,
            ETriggerEvent::Completed,
            this,
            &ACharacter::StopJumping);
    }
}

void AFPSCharacterBase::OnMove(const FInputActionValue& InputValue)
{
    FVector2D MoveValue = InputValue.Get<FVector2D>();

    //컨트롤러가 바라보는 방향 가져오기
    const FRotator ControlRotation = GetController()->GetControlRotation();
    const FRotator ControlRotationYaw(0.f, ControlRotation.Yaw, 0.f);

    //바라보는 방향 ForwardVector 만들기
    const FVector ForwardVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::X);
    const FVector RightVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardVector, MoveValue.X);
    AddMovementInput(RightVector, MoveValue.Y);

    //AddMovementInput(GetActorForwardVector(), MoveValue.X);
    //AddMovementInput(GetActorRightVector(), MoveValue.Y);

    //MYSCREENLOG("Move X: %f, Y: %f", MoveValue.X, MoveValue.Y);
}

void AFPSCharacterBase::OnLook(const FInputActionValue& InputValue)
{
    //if (IsValid(GetController()) == true)
    //{
    //    FVector2D LookValue = InputValue.Get<FVector2D>();

    //    AddControllerYawInput(LookValue.X);
    //    AddControllerPitchInput(LookValue.Y);

    //    MYSCREENLOG("OnLook: %f, LookY: %f", LookValue.X, LookValue.Y);
    //}

    FVector2D LookValue = InputValue.Get<FVector2D>();

    AddControllerYawInput(LookValue.X * LookOffSet);
    AddControllerPitchInput(LookValue.Y * LookOffSet);
}

void AFPSCharacterBase::OnViewChange(const FInputActionValue& InputValue)
{
    switch (CurrentViewMode)
    {
    case EViewType::BACK_VIEW:
        SetViewMode(EViewType::QUARTER_VIEW);
        break;
    case EViewType::QUARTER_VIEW:
        SetViewMode(EViewType::BACK_VIEW);
        break;
    case EViewType::NONE:
    default:
        break;
    }
}

void AFPSCharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    //SetViewMode(EViewType::BACK_VIEW);
    SetViewMode(EViewType::QUARTER_VIEW);
}

void AFPSCharacterBase::SetViewMode(EViewType viewType)
{
    if (CurrentViewMode == viewType)
    {
        return;
    }

    CurrentViewMode = viewType;

    switch (CurrentViewMode)
    {
    case EViewType::BACK_VIEW:
    {
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false; //bUseControllerRotationYaw = true; //bUseControllerRotationYaw 
        bUseControllerRotationRoll = false;

        SpringArmComponent->TargetArmLength = 400.f;
        SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);

        SpringArmComponent->bUsePawnControlRotation = true;

        SpringArmComponent->bInheritPitch = true;
        SpringArmComponent->bInheritYaw = true;
        SpringArmComponent->bInheritRoll = false;

        SpringArmComponent->bDoCollisionTest = true;

        GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
        GetCharacterMovement()->bOrientRotationToMovement = true;
        GetCharacterMovement()->bUseControllerDesiredRotation = false;

        //bOrientRotationToMovement = true;
        //bUseControllerRotationYaw = false;


        break;
    }
    case EViewType::QUARTER_VIEW:
    {
        bUseControllerRotationPitch = false;
        bUseControllerRotationYaw = false; //bUseControllerRotationYaw = true; 
        bUseControllerRotationRoll = false;

        SpringArmComponent->TargetArmLength = 800.f;
        SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

        SpringArmComponent->bUsePawnControlRotation = false;

        SpringArmComponent->bInheritPitch = false;
        SpringArmComponent->bInheritYaw = false;
        SpringArmComponent->bInheritRoll = false;

        SpringArmComponent->bDoCollisionTest = false;

        GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
        GetCharacterMovement()->bOrientRotationToMovement = false;
        GetCharacterMovement()->bUseControllerDesiredRotation = true;

        break;
    }
    case EViewType::NONE:
        break;
    }
}
