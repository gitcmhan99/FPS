// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameInstance.h"
#include "FPS/FPS.h"
#include "Marin.h"
#include "Tank.h"
#include "SXAttackUnit.h"

void UFPSGameInstance::Init()
{
	MYLOG("UFPSGameInstance::Init()");

	//테스트 전용 삭제 예정
	AMarin* marin = NewObject<AMarin>();
	if (IsValid(marin))
	{
		marin->Attack();
	}

	ATank* tank = NewObject<ATank>();
	if (IsValid(tank))
	{
		tank->Attack();
	}

	TArray<ISXAttackUnit*> Units;

	if (marin->GetClass()->ImplementsInterface(USXAttackUnit::StaticClass()))
	{
		Units.Add(marin);
	}
	if (tank->GetClass()->ImplementsInterface(USXAttackUnit::StaticClass()))
	{
		Units.Add(Cast<ISXAttackUnit>(tank));
	}

	for (ISXAttackUnit* unit : Units)
	{
		unit->Attack();
	}
}

void UFPSGameInstance::Shutdown()
{
	MYLOG("UFPSGameInstance::Shutdown()");
}
