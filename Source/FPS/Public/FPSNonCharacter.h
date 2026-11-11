// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacterBase.h"
#include "FPSNonCharacter.generated.h"

DECLARE_DELEGATE_TwoParams(FOnAttackMontageEnded, UAnimMontage*, bool )

class UWidgetHudComponent;
class UWidgetHudBase;

/**
 * 
 */
UCLASS()
class FPS_API AFPSNonCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
    AFPSNonCharacter();

	virtual void BeginAttack();

	virtual void EndAttack(UAnimMontage* InMontage, bool bInterruped);

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	bool bIsNowAttacking;

protected:
	FOnAttackMontageEnded OnAttackMontageEndedDelegate;
		// 애니메이션 몽타주 재생이 끝났을 때 호출할 델리게이트.

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UWidgetHudComponent> WidgetHudComponent;
};
