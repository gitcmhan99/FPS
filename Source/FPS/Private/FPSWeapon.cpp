// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSWeapon.h"
#include "FPSPickup.h"
#include "GameUtil.h"
#include "FPS/FPS.h"
#include "FPSCharacterBase.h"

// Sets default values
AFPSWeapon::AFPSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    PickupComponent = GameUtil::CreateRootComponent<UFPSPickup>(this);
}

// Called when the game starts or when spawned
void AFPSWeapon::BeginPlay()
{
	Super::BeginPlay();

    if (IsValid(PickupComponent))
    {
        PickupComponent->OnPickUp.AddDynamic(this, &ThisClass::CallBackPickUp);
    }
}

void AFPSWeapon::CallBackPickUp(AFPSCharacterBase* pickupChar)
{
    MYSCREENLOG("%s", *pickupChar->GetName());

    if (IsValid(pickupChar) == false)
    {
        return;
    }

    PickupComponent->SetSimulatePhysics(false);
    SetActorEnableCollision(false);

    FAttachmentTransformRules AttachmentRules(
        EAttachmentRule::SnapToTarget,
        true);

    AttachToComponent(
        pickupChar->GetMesh(),
        AttachmentRules,
        SocketName);
}

