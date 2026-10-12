// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_CheckAttack.h"
#include "FPSCharacterBase.h"

void UAN_CheckAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (IsValid(MeshComp))
    {
        AFPSCharacterBase* charBase = Cast<AFPSCharacterBase>(MeshComp->GetOwner());
        if (IsValid(charBase))
        {
            charBase->Callback_CheckAttack();
        }
    }
        
}
