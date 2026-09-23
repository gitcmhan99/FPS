// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSAnimInstanceBase.generated.h"

class AFPSCharacterBase;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class FPS_API UFPSAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
    //ENGINE_API virtual void NativeInitializeAnimation();
    virtual void NativeInitializeAnimation() override;

    //ENGINE_API virtual void NativeUpdateAnimation(float DeltaSeconds);
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<AFPSCharacterBase> OwnerFPSCharacter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UCharacterMovementComponent> OwnerFPSCM;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float fVelocity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    uint8 IsMove : 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    uint8 IsFalling : 1;
};
