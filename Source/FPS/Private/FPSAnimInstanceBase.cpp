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

    //AI 이동(MoveTo, 네비메시 경로 추적)은 가속도를 거의 안 씁니다.
    //등속 이동 중에는 가속도가 0입니다. 최고속도에 도달해 일정 속도로 걸으면 가속도는 정의상 0이 됩니다.
    //fAcceleration == 0 // 걷지X
    /*bool IsNearlyZero = FMath::IsNearlyZero(fAcceleration);

    IsMove = (IsNearlyZero == false &&
              fSpeed > KINDA_SMALL_NUMBER);*/

    //수정은 한가지 값만 체크하도록 수정
    IsMove = fSpeed > KINDA_SMALL_NUMBER; 

    IsFalling = OwnerFPSCM->IsFalling();

    //IsDead = OwnerFPSCharacter->GetIsDead();

    if (IsValid(OwnerFPSCharacter->GetStatusComponents()))
    {
        IsDead = OwnerFPSCharacter->GetStatusComponents()->bIsDead;
    }
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

void UFPSAnimInstanceBase::AnimNotify_CheckDead()
{
    MYSCREENLOG("AnimNotify_CheckDead()");

    if (OnCheckDead.IsBound())
    {
        OnCheckDead.Broadcast();
    }
}
