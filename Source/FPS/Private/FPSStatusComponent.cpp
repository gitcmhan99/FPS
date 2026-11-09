// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSStatusComponent.h"

// Sets default values for this component's properties
UFPSStatusComponent::UFPSStatusComponent()
    : MaxHP(100.0f)
    , CurrentHP(100.0f)
    , bIsDead(false)
{
	// Set t
	// ...his component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

float UFPSStatusComponent::ApplyDamage(float damage)
{
    if (bIsDead || damage <= 0.0f)
    {
        return 0.f;
    }

    float oldHP = CurrentHP;

    float clampHP = FMath::Clamp<float>(damage, 0, oldHP);

    CurrentHP = (oldHP - clampHP);

    {
        if(CurrentHP <= KINDA_SMALL_NUMBER)
        {
            CurrentHP = 0.f;
            bIsDead = true;

            if (OnDead.IsBound())
            {
                OnDead.Broadcast();
            }
        }

        if(OnCurretHPChange.IsBound())
        {
            OnCurretHPChange.Broadcast(CurrentHP);
        }
    }

    return clampHP;
}


// Called when the game starts
void UFPSStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFPSStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

