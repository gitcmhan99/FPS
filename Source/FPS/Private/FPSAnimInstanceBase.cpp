// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAnimInstanceBase.h"
#include "FPSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPS/FPS.h"

void UFPSAnimInstanceBase::NativeInitializeAnimation()
{

    //TryGetPawnOwner
    //Try로 시작하는 함수의 주의사항..
    //게임시작 > Mesh 생성 > AnimInstance 생성 > Pawn연결
    //AnimInstance 생성 > Pawn연결 안된 상태
    APawn* ownerPawn = TryGetPawnOwner();
    if (IsValid(ownerPawn))
    {
        OwnerFPSCharacter = Cast<AFPSCharacterBase>(ownerPawn);
        OwnerFPSCM = OwnerFPSCharacter->GetCharacterMovement();

        //애님인스턴스 폰을 참조하는 경우
        //GetAnimInstance();
    }
}

void UFPSAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
    if (!IsValid(OwnerFPSCharacter) ||
        !IsValid(OwnerFPSCM))
    {
        return;
    }

    Velocity = OwnerFPSCM->Velocity;
    fSpeed = UKismetMathLibrary::VSizeXY(Velocity);

    FVector acceleration = OwnerFPSCM->GetCurrentAcceleration();
    float fAcceleration = UKismetMathLibrary::VSizeXY(acceleration);
    //fAcceleration == 0 // 걷지X
    bool IsNearlyZero = FMath::IsNearlyZero(fAcceleration);

    IsMove = (IsNearlyZero == false &&
              fSpeed > KINDA_SMALL_NUMBER);

    IsFalling = OwnerFPSCM->IsFalling();
}

void UFPSAnimInstanceBase::AnimNotify_CheckAttack()
{
    MYSCREENLOG("AnimNotify_CheckAttack()");

    //델리게이트 함수 또는 특정 함수를 호출
    if (OnCheckAttack.IsBound())
    {
        OnCheckAttack.Broadcast();
    }
}
