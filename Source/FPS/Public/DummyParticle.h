// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DummyParticle.generated.h"

class UParticleSystemComponent;
class URotatingMovementComponent;

UCLASS()
class FPS_API ADummyParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummyParticle();

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DummyParticle", meta = (AllowPrivateAccess))
    TObjectPtr<UStaticMeshComponent> staticMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DummyParticle", meta = (AllowPrivateAccess))
    TObjectPtr<UParticleSystemComponent> particleSystem;


    //UActorComponent, USceneComponent가 아니다
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DummyParticle", meta = (AllowPrivateAccess))
    TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "DummyParticle", meta = (AllowPrivateAccess))
    int64 testNumber;
};
