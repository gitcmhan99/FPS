// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_CheckInput.h"
#include "FPSCharacterBase.h"

void UAN_CheckInput::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (IsValid(MeshComp))
    {
        AFPSCharacterBase* charBase = Cast<AFPSCharacterBase>(MeshComp->GetOwner());
        if (IsValid(charBase))
        {
            charBase->Callback_CheckInput();
        }
    }

}
