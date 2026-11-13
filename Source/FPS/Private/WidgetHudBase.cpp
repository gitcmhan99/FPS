// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHudBase.h"
#include "FPSStatusComponent.h"
#include "Components/TextBlock.h"
#include "FPSNonCharacter.h"


UWidgetHudBase::UWidgetHudBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetHudBase::NativeConstruct()
{
    Super::NativeConstruct();

    AFPSNonCharacter* NPC = Cast<AFPSNonCharacter>(Owner);
    if (IsValid(NPC))
    {
        NPC->SetHPTextWidget(this);
    }
}

void UWidgetHudBase::InitHPText(UFPSStatusComponent* StatusComponent)
{
    float maxHP = StatusComponent->GetMaxHP();
    float currentHP = StatusComponent->CurrentHP;

    OnMaxHP(maxHP);
    OnCurrentHP(currentHP);
}

void UWidgetHudBase::OnMaxHP(float maxHP)
{
    TextBlock_Max->SetText(FText::FromString(FString::SanitizeFloat(maxHP)));
}

void UWidgetHudBase::OnCurrentHP(float currentHP)
{
    TextBlock_HP->SetText(FText::FromString(FString::SanitizeFloat(currentHP)));
}
