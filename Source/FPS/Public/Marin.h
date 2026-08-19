// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SXAttackUnit.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Marin.generated.h"

UCLASS()
class FPS_API AMarin : public AActor, public ISXAttackUnit
{
	GENERATED_BODY()

public:
	// ISXAttackUnit을(를) 통해 상속됨
	void Attack() override;
};
