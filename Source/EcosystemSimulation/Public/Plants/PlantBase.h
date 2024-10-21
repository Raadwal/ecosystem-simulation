// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantBase.generated.h"

UENUM(BlueprintType)
enum class EPlantStatus : uint8 
{
	GROWING = 0 UMETA(DisplayName = "GROWING"),
	REPRODUCING = 1  UMETA(DisplayName = "REPRODUCING"),
};

UCLASS()
class ECOSYSTEMSIMULATION_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APlantBase();

#pragma region Mutations Setters/Getters

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	* 
	* Chance of plant small mutation after reproduction attempt (0-5% parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSmallMutationChanceSelf(const float& SmallMutationChanceSelf);

	/*
	* Float from range <0, 100>
	* 
	* Chance of plant small mutation after reproduction attempt (0-5% parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSmallMutationChanceSelf() const;

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	*
	* Chance of plant medium mutation after reproduction attempt (5-25% parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMediumMutationChanceSelf(const float& MediumMutationChanceSelf);

	/*
	* Float from range <0, 100>
	*
	* Chance of plant medium mutation after reproduction attempt (5-25% parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMediumMutationChanceSelf() const;

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	*
	* Chance of plant large mutation after reproduction attempt (25-50% parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLargeMutationChanceSelf(const float& LargeMutationChanceSelf);

	/*
	* Float from range <0, 100>
	*
	* Chance of plant medium mutation after reproduction attempt (25-50% parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLargeMutationChanceSelf() const;

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	*
	* Chance of plant ancestor small mutation (0-5% change parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSmallMutationChanceAncestor(const float& SmallMutationChanceAncestor);

	/*
	* Float from range <0, 100>
	*
	* Chance of plant ancestor small mutation (0-5% change parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSmallMutationChanceAncestor() const;

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	*
	* Chance of plant ancestor medium mutation (5-25% change parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMediumMutationChanceAncestor(const float& MediumMutationChanceAncestor);

	/*
	* Float from range <0, 100>
	*
	* Chance of plant ancestor medium mutation (5-25% change parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMediumMutationChanceAncestor() const;

	/*
	* SmallMutationChanceSelf = Float from range <0, 100>
	*
	* Chance of plant ancestor large mutation (25-50% change parameter change)
	*/
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLargeMutationChanceAncestor(const float& LargeMutationChanceAncestor);

	/*
	* Float from range <0, 100>
	*
	* Chance of plant ancestor large mutation (25-50% change parameter change)
	*/
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLargeMutationChanceAncestor() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSmallMutationChangeMin(float& SmallMutationChangeMin);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSmallMutationChangeMin() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSmallMutationChangeMax(const float& SmallMutationChangeMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSmallMutationChangeMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMediumMutationChangeMin(const float& MediumMutationChangeMin);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMediumMutationChangeMin() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMediumMutationChangeMax(const float& MediumMutationChangeMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMediumMutationChangeMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLargeMutationChangeMin(const float& LargeMutationChangeMin);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLargeMutationChangeMin() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLargeMutationChangeMax(const float& LargeMutationChangeMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLargeMutationChangeMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMutationsCount(const int32& MutationsCount);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetMutationsCount() const;

#pragma endregion

#pragma region Growth Setters/Getter

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeToGrowSeconds(const float& TimeToGrowSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeToGrowSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeSinceStartedGrowingSeconds(const float& TimeSinceStartedGrowingSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeSinceStartedGrowingSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeToReproductionAttemptSeconds(const float& TimeToReproductionAttemptSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeToReproductionAttemptSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeSinceStartedReproductionAttemptSeconds(const float& TimeSinceStartedReproductionAttemptSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeSinceStartedReproductionAttemptSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentMultiplier(const float& EnvironmentMultiplier);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentMultiplier() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetGrowPct(const float& GrowPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetGrowPct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductionPct(const float& ReproductionPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductionPct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetPlantStatus(const EPlantStatus& PlantStatus);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	EPlantStatus GetPlantStatus() const;

#pragma endregion

#pragma region Statistics Setters/Getters

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSpeciesName(const FString& SpeciesName);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FString GetSpeciesName() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetInitialHealth(const float& InitialHealth);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetInitialHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCurrentHealth(const float& CurrentHealth);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetInitialHealthLose(const float& InitialHealthLose);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetInitialHealthLose() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCurrentHealthLose(const float& CurrentHealthLose);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCurrentHealthLose() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetHealthLoseMultiplier(const float& HealthLoseMultiplier);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetHealthLoseMultiplier() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetResistance(const float& Resistance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetResistance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductionChancePct(const float& ReproductionChancePct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductionChancePct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductionRange(const int32& ReproductionRange);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetReproductionRange() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetNutrients(const float& Nutrients);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetNutrients() const;

#pragma endregion

#pragma region Environment Setters/Getter

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentTemperature(const float& EnvironmentTemperature);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentTemperature() const;
	
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentHumidity(const float& EnvironmentHumidity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentHumidity() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeToApplyEnvironmentEffectsSeconds(const float& TimeToApplyEnvironmentEffectsSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeToApplyEnvironmentEffectsSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeSinceEnvironmentEffectAppliement(const float& TimeSinceEnvironmentEffectAppliement);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeSinceEnvironmentEffectAppliement() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMinTemperature(const float& MinTemperature);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMinTemperature() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxTemperature(const float& MaxTemperature);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxTemperature() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsInOptimalTemperature(const bool& IsInOptimalTemperature);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsInOptimalTemperature() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMinHumidity(const float& MinHumidity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMinHumidity() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxHumidity(const float& MaxHumidity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxHumidity() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsInOptimalHumidity(const bool& IsInOptimalHumidity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsInOptimalHumidity() const;

#pragma endregion

protected:

#pragma region Mutations

	// Chance of plant small mutation after reproduction attempt
	UPROPERTY(BlueprintSetter = SetSmallMutationChanceSelf, BlueprintGetter = GetSmallMutationChanceSelf, EditAnywhere, Category = "Mutations")
	float _SmallMutationChanceSelf = 5.0f; // Can mutate

	// Chance of plant medium mutation after reproduction attempt
	UPROPERTY(BlueprintSetter = SetMediumMutationChanceSelf, BlueprintGetter = GetMediumMutationChanceSelf, EditAnywhere, Category = "Mutations")
	float _MediumMutationChanceSelf = 2.0f; // Can mutate

	// Chance of plant large mutation after reproduction attempt
	UPROPERTY(BlueprintSetter = SetLargeMutationChanceSelf, BlueprintGetter = GetLargeMutationChanceSelf, EditAnywhere, Category = "Mutations")
	float _LargeMutationChanceSelf = 0.5f; // Can mutate

	// Chance of plant ancestor small mutation 
	UPROPERTY(BlueprintSetter = SetSmallMutationChanceAncestor, BlueprintGetter = GetSmallMutationChanceAncestor, EditAnywhere, Category = "Mutations")
	float _SmallMutationChanceAncestor = 25.0f; // Can mutate

	// Chance of plant ancestor medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChanceAncestor, BlueprintGetter = GetMediumMutationChanceAncestor, EditAnywhere, Category = "Mutations")
	float _MediumMutationChanceAncestor = 10.0f; // Can mutate

	// Chance of plant ancestor large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChanceAncestor, BlueprintGetter = GetLargeMutationChanceAncestor, EditAnywhere, Category = "Mutations")
	float _LargeMutationChanceAncestor = 2.5f; // Can mutate

	// Minimum trait change by small mutation
	UPROPERTY(BlueprintSetter = SetSmallMutationChangeMin, BlueprintGetter = GetSmallMutationChangeMin, EditDefaultsOnly, Category = "Mutations")
	float _SmallMutationChangeMin = 0.0f;

	// Maximum trait change by small mutation
	UPROPERTY(BlueprintSetter = SetSmallMutationChangeMax, BlueprintGetter = GetSmallMutationChangeMax, EditDefaultsOnly, Category = "Mutations");
	float _SmallMutationChangeMax = 5.0f;

	// Minimum trait change by medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChangeMin, BlueprintGetter = GetMediumMutationChangeMin, EditDefaultsOnly, Category = "Mutations")
	float _MediumMutationChangeMin = 0.0f;

	// Maximum trait change by medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChangeMax, BlueprintGetter = GetMediumMutationChangeMax, EditDefaultsOnly, Category = "Mutations");
	float _MediumMutationChangeMax = 25.0f;

	// Minimum trait change by large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChangeMin, BlueprintGetter = GetLargeMutationChangeMin, EditDefaultsOnly, Category = "Mutations")
	float _LargeMutationChangeMin = 0.0f;

	// Maximum trait change by large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChangeMax, BlueprintGetter = GetLargeMutationChangeMax, EditDefaultsOnly, Category = "Mutations");
	float _LargeMutationChangeMax = 50.0f;

	// Maximum trait change by large mutation
	UPROPERTY(BlueprintSetter = SetMutationsCount, BlueprintGetter = GetMutationsCount, VisibleAnywhere, Category = "Mutations");
	int32 _MutationsCount = 0;

#pragma endregion

#pragma region Growth

	// Time that plant needs to grow - min 1s
	UPROPERTY(BlueprintSetter = SetTimeToGrowSeconds, BlueprintGetter = GetTimeToGrowSeconds, EditAnywhere, Category = "Grow")
	float _TimeToGrowSeconds = 60.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetTimeSinceStartedGrowingSeconds, BlueprintGetter = GetTimeSinceStartedGrowingSeconds, Transient, Category = "Grow")
	float _TimeSinceStartedGrowingSeconds = 0.0f;

	// Time after grown plant will reproduce
	// After each reproduction attempt plant has to grow again - min 1s
	UPROPERTY(BlueprintSetter = SetTimeToReproductionAttemptSeconds, BlueprintGetter = GetTimeToReproductionAttemptSeconds, EditAnywhere, Category = "Grow")
	float _TimeToReproductionAttemptSeconds = 30.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetTimeSinceStartedReproductionAttemptSeconds, BlueprintGetter = GetTimeSinceStartedReproductionAttemptSeconds, Transient, Category = "Grow")
	float _TimeSinceStartedReproductionAttemptSeconds = 0.0f;

	// Plant grow faster in optimal environment and has higher reproduction chance
	UPROPERTY(BlueprintSetter = SetEnvironmentMultiplier, BlueprintGetter = GetEnvironmentMultiplier, VisibleAnywhere, Category = "Grow")
	float _EnvironmentMultiplier = 1.0f;

	UPROPERTY(BlueprintSetter = SetGrowPct, BlueprintGetter = GetGrowPct, VisibleAnywhere, Category = "Grow")
	float _GrowPct = 0.0f;

	UPROPERTY(BlueprintSetter = SetReproductionPct, BlueprintGetter = GetReproductionPct, VisibleAnywhere, Category = "Grow")
	float _ReproductionPct = 0.0f;

	UPROPERTY(BlueprintSetter = SetPlantStatus, BlueprintGetter = GetPlantStatus, VisibleAnywhere, Category = "Grow")
	EPlantStatus _PlantStatus = EPlantStatus::GROWING;

#pragma endregion

#pragma region Statistics

	UPROPERTY(BlueprintSetter = SetSpeciesName, BlueprintGetter = GetSpeciesName, EditAnywhere, Category = "Statistics")
	FString _SpeciesName = "";

	// Health is reduced:
	// - when conditions are not conducive to plant growth
	// - after each reproduction
	// Health is gained:
	// - When are conducive to plant growth
	UPROPERTY(BlueprintSetter = SetInitialHealth, BlueprintGetter = GetInitialHealth, EditAnywhere, Category = "Statistics")
	float _InitialHealth = 100.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetCurrentHealth, BlueprintGetter = GetCurrentHealth, VisibleAnywhere, Category = "Statistics")
	float _CurrentHealth = 0.0f;

	// How much health is lost after each reproduction
	UPROPERTY(BlueprintSetter = SetInitialHealthLose, BlueprintGetter = GetInitialHealthLose, EditAnywhere, Category = "Statistics")
	float _InitialHealthLose = 10.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetCurrentHealthLose, BlueprintGetter = GetCurrentHealthLose, VisibleAnywhere, Category = "Statistics")
	float _CurrentHealthLose = _InitialHealthLose;

	// Multiplier for Health lose after each reproduction
	UPROPERTY(BlueprintSetter = SetHealthLoseMultiplier, BlueprintGetter = GetHealthLoseMultiplier, EditAnywhere, Category = "Statistics")
	float _HealthLoseMultiplier = 1.5f; // Can mutate

	// Resistance for health lose <0, 100>
	UPROPERTY(BlueprintSetter = SetResistance, BlueprintGetter = GetResistance, EditAnywhere, Category = "Statistics")
	float _Resistance = 0.0f; // Can mutate

	// When plant grows at the last stage it has chance to reproduce <0, 100>
	// Higher humidility => higher chance to reproduce
	// If plant spawns at occupied spot and it's destroyed
	UPROPERTY(BlueprintSetter = SetReproductionChancePct, BlueprintGetter = GetReproductionChancePct, EditAnywhere, Category = "Statistics")
	float _ReproductionChancePct = 25.0f; // Can mutate

	// Distance on which ancestor can be spawned
	UPROPERTY(BlueprintSetter = SetReproductionRange, BlueprintGetter = GetReproductionRange, EditAnywhere, Category = "Statistics")
	int32 _ReproductionRange = 1; // Can mutate
	
	// Nutrients that plant delivers to animal (How much of hunger bar is filled after eating plant)
	UPROPERTY(BlueprintSetter = SetNutrients, BlueprintGetter = GetNutrients, EditAnywhere, Category = "Statistics")
	float _Nutrients = 0.0f; // Can mutate

#pragma endregion

#pragma region Environment

	UPROPERTY(BlueprintGetter = SetEnvironmentTemperature, BlueprintGetter = GetEnvironmentTemperature, VisibleAnywhere, Category = "Environment")
	float _EnvironmentTemperature = 0.5f;

	UPROPERTY(BlueprintGetter = SetEnvironmentHumidity, BlueprintGetter = GetEnvironmentHumidity, VisibleAnywhere, Category = "Environment")
	float _EnvironmentHumidity = 0.5f;

	// Indicates how often plant will lose health when not in optimal environment
	UPROPERTY(BlueprintSetter = SetTimeToApplyEnvironmentEffectsSeconds, BlueprintGetter = GetTimeToApplyEnvironmentEffectsSeconds, EditAnywhere, Category = "Environment")
	float _TimeToApplyEnvironmentEffectsSeconds = 10.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetTimeSinceEnvironmentEffectAppliement, BlueprintGetter = GetTimeSinceEnvironmentEffectAppliement, Transient, Category = "Environment")
	float _TimeSinceEnvironmentEffectAppliement = 0.0f;

	// Temperature range where plant is not losing health <0, 1>
	UPROPERTY(BlueprintSetter = SetMinTemperature, BlueprintGetter = GetMinTemperature, EditAnywhere, Category = "Environment")
	float _MinTemperature = 0.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetMaxTemperature, BlueprintGetter = GetMaxTemperature, EditAnywhere, Category = "Environment")
	float _MaxTemperature = 1.0f; // Can mutate

	// If plant doesn't grow in optimal temperature it's losing health every _ApplyEnvironmentEffectsTimerSeconds
	// If plant grows in optimal temperature it grow faster and has higher reproduction chance
	UPROPERTY(BlueprintSetter = SetIsInOptimalTemperature, BlueprintGetter = GetIsInOptimalTemperature, VisibleAnywhere, Category = "Environment")
	bool _IsInOptimalTemperature = false;

	// Humidity range where plant is not losing health <0, 1>
	UPROPERTY(BlueprintSetter = SetMinHumidity, BlueprintGetter = GetMinHumidity, EditAnywhere, Category = "Environment")
	float _MinHumidity = 0.0f; // Can mutate

	UPROPERTY(BlueprintSetter = SetMaxHumidity, BlueprintGetter = GetMaxHumidity, EditAnywhere, Category = "Environment")
	float _MaxHumidity = 1.0f; // Can mutate

	// If plant doesn't grow in optimal humidity it's losing health every _ApplyEnvironmentEffectsTimerSeconds
	// If plant grows in optimal humidity it grow faster and has higher reproduction chance
	UPROPERTY(BlueprintSetter = SetIsInOptimalHumidity, BlueprintGetter = GetIsInOptimalHumidity, VisibleAnywhere, Category = "Environment")
	bool _IsInOptimalHumidity = false;
#pragma endregion

};
