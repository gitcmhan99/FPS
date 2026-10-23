// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSNonCharacter.h"
#include "FPSAIControllerBase.h"


AFPSNonCharacter::AFPSNonCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AIControllerClass = AFPSAIControllerBase::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
