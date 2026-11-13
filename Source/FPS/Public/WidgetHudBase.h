// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHudBase.generated.h"

class UFPSStatusComponent;
class UTextBlock;


/**
 * 
 */
UCLASS()
class FPS_API UWidgetHudBase : public UUserWidget
{
	GENERATED_BODY()

public:
    UWidgetHudBase(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    void InitHPText(UFPSStatusComponent* StatusComponent);

    void SetOwner(AActor* owner) { Owner = owner; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_HP;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_Max;

    TObjectPtr<AActor> Owner;

public:
    UFUNCTION()
    void OnMaxHP(float maxHP);

    UFUNCTION()
    void OnCurrentHP(float currentHP);
};
