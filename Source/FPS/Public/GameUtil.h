// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

namespace GameUtil
{
    template<typename T>
    T* CreateComponent(
        AActor* Owner,
        bool isChild = true,
        USceneComponent* InParent = nullptr,
        FName createName = NAME_None)
    {
        static_assert(TIsDerivedFrom<T, USceneComponent>::IsDerived, "T is Not USceneComponent");

        if (!ensureMsgf(Owner, TEXT("CreateComponet Owner Null")))
        {
            return nullptr;
        }

        FName SubobjectFName = MakeComponentName<T>(Owner, createName);

        T* NewComponent = Owner->CreateDefaultSubobject<T>(SubobjectFName);

        if (!ensureMsgf(NewComponent, TEXT("Fail CreateComponet CreateDefaultSubobject")))
        {
            return nullptr;
        }

        if (isChild)
        {
            if (InParent == nullptr)
            {
                InParent = Owner->GetRootComponent();
            }

            if (ensureMsgf(InParent, TEXT("GetRootComponent Parent Null")))
            {
                NewComponent->SetupAttachment(InParent);
            }
        }
        else
        {
            Owner->SetRootComponent(NewComponent);
        }

        return NewComponent;
    }

    template<typename T>
    T* CreateRootComponent(
        AActor* Owner,
        FName createName = NAME_None
    )
    {
        T* t = CreateComponent<T>(Owner, false, nullptr, createName);
        return t;
    }

    template<typename T>
    T* CreateComponentWithLocation(
        AActor* Owner,
        const FVector& vec = FVector::ZeroVector,
        bool isChild = true,
        USceneComponent* InParent = nullptr,
        FName createName = NAME_None
    )
    {
        T* t = CreateComponent<T>(Owner, isChild, InParent, createName);
        if (ensureMsgf(t, TEXT("CreateComponentWithLocation Null")))
        {
            t->SetRelativeLocation(vec);
        }

        return t;
    }

    template<typename T>
    T* CreateActorComponent(
        AActor* Owner,
        FName createName = NAME_None
    )
    {
        static_assert(TIsDerivedFrom<T, UActorComponent>::IsDerived, "T is Not UActorComponent");

        FName SubobjectFName = MakeComponentName<T>(Owner, createName);

        if (!ensureMsgf(Owner, TEXT("CreateActorComponent Owner Null")))
        {
            return nullptr;
        }

        T* t = Owner->CreateDefaultSubobject<T>(SubobjectFName);

        if (!ensureMsgf(t, TEXT("Fail CreateActorComponent CreateDefaultSubobject")))
        {
            return nullptr;
        }

        return t;
    }

    template<typename T>
    FName MakeComponentName(AActor* Owner, FName createName = NAME_None)
    {
        if (!createName.IsNone())
        {
            return createName;
        }

        return MakeUniqueObjectName(Owner, T::StaticClass(), T::StaticClass()->GetFName());
    }

    static void AddInputMapping(const APawn* Pawn, const UInputMappingContext* MappingContext, int32 Priority = 0)
    {
        if (!ensureMsgf(Pawn, TEXT("AddInputMapping Pawn Null")))
        {
            return;
        }

        if (!ensureMsgf(MappingContext, TEXT("AddInputMapping MappingContext Null")))
        {
            return;
        }

        APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
        if (!ensure(IsValid(PlayerController)))
        {
            return;
        }

        ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
        if (!ensure(IsValid(LocalPlayer)))
        {
            return;
        }

        UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
        if (!ensure(IsValid(InputSubsystem)))
        {
            return;
        }

        InputSubsystem->AddMappingContext(MappingContext, Priority);
    }
}
