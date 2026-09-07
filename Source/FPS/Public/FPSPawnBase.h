// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "FPSPawnBase.generated.h"

/*
- Capsule Component
- SkeletalMesh Component
- FloatingPawnMovement Component
- SpringArm Component
- Camera Component
*/
class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class FPS_API AFPSPawnBase : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AFPSPawnBase();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    virtual void PostInitializeComponents() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    void OnMove(const FInputActionValue& InputValue);

protected:
    UPROPERTY(Category = "FPSPawn", EditDefaultsOnly)
    TObjectPtr<UCapsuleComponent> CapsuleComponent;

    UPROPERTY(Category = "FPSPawn", EditDefaultsOnly)
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(Category = "FPSPawn", EditDefaultsOnly)
    TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

    UPROPERTY(Category = "FPSPawn", EditDefaultsOnly)
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(Category = "FPSPawn", EditDefaultsOnly)
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> IA_Move;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> IMC_Player;
    

private:
    void UpDown(float InAxisValue);
    void LeftRight(float InAxisValue);
};
