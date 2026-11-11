// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHudComponent.h"
#include "WidgetHudBase.h"

UWidgetHudComponent::UWidgetHudComponent()
{
}

void UWidgetHudComponent::InitWidget()
{
    Super::InitWidget();

    AActor* owner = GetOwner();
    UWidgetHudBase* HPText = Cast<UWidgetHudBase>(GetWidget());
    if (IsValid(owner) && IsValid(HPText))
    {
        HPText->SetOwner(owner);
    }
}
