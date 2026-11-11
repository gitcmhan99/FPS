// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHudBase.h"
#include "FPSStatusComponent.h"
#include "Components/TextBlock.h"


UWidgetHudBase::UWidgetHudBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetHudBase::NativeConstruct()
{
    Super::NativeConstruct();
}

void UWidgetHudBase::InitHPText(UFPSStatusComponent& StatusComponent)
{
    float maxHP = StatusComponent.GetMaxHP();
    float currentHP = StatusComponent.CurrentHP;

    TextBlock_Max->SetText(FText::FromString(FString::SanitizeFloat(maxHP)));
    TextBlock_HP->SetText(FText::FromString(FString::SanitizeFloat(currentHP)));
}
