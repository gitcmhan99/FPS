// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeapon.generated.h"

class AFPSCharacterBase;
class UFPSPickup;

UCLASS()
class FPS_API AFPSWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    UFUNCTION()
    void CallBackPickUp(AFPSCharacterBase*  pickupChar);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UFPSPickup> PickupComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName SocketName = TEXT("hand_rSocket");
};
