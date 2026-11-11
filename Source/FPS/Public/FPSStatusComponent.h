// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSStatusComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMaxHPChange, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurretHPChange, float);
DECLARE_MULTICAST_DELEGATE(FOnDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UFPSStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    UPROPERTY()
    float MaxHP;

    UPROPERTY(Transient)
    float CurrentHP;

    UPROPERTY(Transient)
    uint8 bIsDead : 1;

    FOnMaxHPChange OnMaxHPChange;
    FOnCurretHPChange OnCurretHPChange;
    FOnDead OnDead;

public:	
	// Sets default values for this component's properties
	UFPSStatusComponent();

    float ApplyDamage(float damage);

    float GetMaxHP() const { return MaxHP; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
