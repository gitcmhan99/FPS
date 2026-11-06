// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSNonCharacter.h"
#include "FPSAIControllerBase.h"
#include "FPSGameInstance.h"
#include "FPSAnimInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

AFPSNonCharacter::AFPSNonCharacter()
    : bIsNowAttacking(false)
{
    PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = AFPSAIControllerBase::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AFPSNonCharacter::BeginAttack()
{
    UFPSAnimInstanceBase* AnimInstance = Cast<UFPSAnimInstanceBase>(GetMesh()->GetAnimInstance());
    checkf(IsValid(AnimInstance) == true, TEXT("Invalid AnimInstance"));

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    if (IsValid(AnimInstance) == true && IsValid(MeleeMontage) == true && AnimInstance->Montage_IsPlaying(MeleeMontage) == false)
    {
        AnimInstance->Montage_Play(MeleeMontage);

        bIsNowAttacking = true;

        if (OnAttackMontageEndedDelegate.IsBound() == false)
        {
            OnAttackMontageEndedDelegate.BindUObject(this, &ThisClass::EndAttack);
            AnimInstance->Montage_SetEndDelegate(OnAttackMontageEndedDelegate, MeleeMontage);
        }
    }
}

void AFPSNonCharacter::EndAttack(UAnimMontage* InMontage, bool bInterruped)
{
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

    bIsNowAttacking = false;

    if (OnAttackMontageEndedDelegate.IsBound() == true)
    {
        OnAttackMontageEndedDelegate.Unbind();
    }
}

