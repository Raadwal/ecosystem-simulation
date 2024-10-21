// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/Animal.h"
#include "AnimalMale.h"
#include "AnimalFemale.generated.h"

/**
 * 
 */
UCLASS()
class ECOSYSTEMSIMULATION_API AAnimalFemale : public AAnimal
{
	GENERATED_BODY()
	
public:
	AAnimalFemale();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override final;

	UFUNCTION(BluePrintCallable)
	bool SetPregnancy(AAnimalMale* const Father);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxOffspringsQuantity(const int32& MaxOffspringsQuantity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetMaxOffspringsQuantity() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetPregnancyLengthSeconds(const float& PregnancyLengthSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetPregnancyLengthSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetPregnancyPct(const float& PregnancyPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetPregnancyPct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsPregnant(const bool& IsPregnant);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsPregnant() const;

private:

	void SpawnOffsprings();

	void AncestorSetup(AAnimal* const Ancestor);

	void ApplyMutation(AAnimal* const Ancestor, const float& MinChange, const float& MaxChange);

	FVector CreateLocationOffset();

	UPROPERTY(BlueprintSetter = SetMaxOffspringsQuantity, BlueprintGetter = GetMaxOffspringsQuantity, EditAnywhere)
	int32 _MaxOffspringsQuantity = 1;

	UPROPERTY(BlueprintSetter = SetPregnancyLengthSeconds, BlueprintGetter = GetPregnancyLengthSeconds, VisibleAnywhere)
	float _PregnancyLengthSeconds = 30.0f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAnimal> _SelfFemale;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAnimal> _SelfMale;

	UPROPERTY(VisibleAnywhere)
	float _PregnancyTimerSeconds = 0.0f;

	UPROPERTY(BlueprintSetter = SetPregnancyPct, BlueprintGetter = GetPregnancyPct, VisibleAnywhere)
	float _PregnancyPct = 0.0f;

	UPROPERTY(VisibleAnywhere)
	FFatherTraits _FatherTraits;

	UPROPERTY(BlueprintSetter = SetIsPregnant, BlueprintGetter = GetIsPregnant, EditAnywhere)
	bool _IsPregnant = false;
};
