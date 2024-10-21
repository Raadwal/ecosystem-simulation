// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/Animal.h"
#include "AnimalMale.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEMSIMULATION_API AAnimalMale : public AAnimal
{
	GENERATED_BODY()

public:
	AAnimalMale();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override final;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetDesirability(const float& Desirability);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetDesirability() const;

private:
	
	// Desirability by females -> Higher value, higher change to reproduce <0, 100>
	UPROPERTY(BlueprintSetter = SetDesirability, BlueprintGetter = GetDesirability, EditDefaultsOnly)
	float _Desirability = 100.0f;

	// Delay after unsuccessful reproduction attempt
	UPROPERTY(EditDefaultsOnly)
	float _ReproductionDelaySeconds = 30.0f;

	UPROPERTY(VisibleAnywhere)
	float _ReproductionDelayTimerSeconds = 0.0f;

	UPROPERTY(Transient)
	float _CanReproduce = true;
};
