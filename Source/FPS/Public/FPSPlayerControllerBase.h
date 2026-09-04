// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFPSPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
    AFPSPlayerControllerBase();

public:
    virtual void PostInitializeComponents() override;
    virtual void PlayerTick(float DeltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void LeftRight(float InAxis);

protected:
    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;
    
};
