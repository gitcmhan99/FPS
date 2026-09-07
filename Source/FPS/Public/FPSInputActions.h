// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FPSInputActions.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class FPS_API UFPSInputActions : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UInputAction> Move;
};
