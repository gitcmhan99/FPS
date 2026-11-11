// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "WidgetHudComponent.generated.h"

class UWidgetHudBase;

/**
 * 
 */
UCLASS()
class FPS_API UWidgetHudComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
    UWidgetHudComponent();

    virtual void InitWidget() override;
};
