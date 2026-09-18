// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EViewType : uint8
{
    NONE,
    BACK_VIEW,
    QUARTER_VIEW,
};

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UFPSInputActions;

UCLASS()
class FPS_API AFPSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void OnMove(const FInputActionValue& InputValue);

    virtual void PossessedBy(AController* NewController) override;

#pragma region [Component]
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
    TObjectPtr<UCameraComponent> CameraComponent;
#pragma endregion

#pragma region [Input]
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UFPSInputActions> InputActions;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> IMC_Player;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    float LookOffSet = 0.25f;

    void OnLook(const FInputActionValue& InputValue);
    void OnViewChange(const FInputActionValue& InputValue);
#pragma endregion

#pragma region ViewMode
public:
    void SetViewMode(EViewType eviewtype);

protected:
    EViewType CurrentViewMode = EViewType::NONE;

#pragma endregion ViewMode

protected:
    FVector DirectionToMove = FVector::ZeroVector;
};
