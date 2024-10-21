// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/PlantBase.h"

APlantBase::APlantBase()
{
	// Empty Constructor
}

#pragma region Mutations Setters/Getters

void APlantBase::SetSmallMutationChanceSelf(const float& SmallMutationChanceSelf)
{
	_SmallMutationChanceSelf = FMath::Clamp(SmallMutationChanceSelf, 0.0f, 100.0f);
}

float APlantBase::GetSmallMutationChanceSelf() const
{
	return _SmallMutationChanceSelf;
}

void APlantBase::SetMediumMutationChanceSelf(const float& MediumMutationChanceSelf)
{
	_MediumMutationChanceSelf = FMath::Clamp(MediumMutationChanceSelf, 0.0f, 100.0f);
}

float APlantBase::GetMediumMutationChanceSelf() const
{
	return _MediumMutationChanceSelf;
}

void APlantBase::SetLargeMutationChanceSelf(const float& LargeMutationChanceSelf)
{
	_LargeMutationChanceSelf = FMath::Clamp(LargeMutationChanceSelf, 0.0f, 100.0f);
}

float APlantBase::GetLargeMutationChanceSelf() const
{
	return _LargeMutationChanceSelf;
}

void APlantBase::SetSmallMutationChanceAncestor(const float& SmallMutationChanceAncestor)
{
	_SmallMutationChanceAncestor = FMath::Clamp(SmallMutationChanceAncestor, 0.0f, 100.0f);
}

float APlantBase::GetSmallMutationChanceAncestor() const
{
	return _SmallMutationChanceAncestor;
}

void APlantBase::SetMediumMutationChanceAncestor(const float& MediumMutationChanceAncestor)
{
	_MediumMutationChanceAncestor = FMath::Clamp(MediumMutationChanceAncestor, 0.0f, 100.0f);
}

float APlantBase::GetMediumMutationChanceAncestor() const
{
	return _MediumMutationChanceAncestor;
}

void APlantBase::SetLargeMutationChanceAncestor(const float& LargeMutationChanceAncestor)
{
	_LargeMutationChanceAncestor = FMath::Clamp(LargeMutationChanceAncestor, 0.0f, 100.0f);
}

float APlantBase::GetLargeMutationChanceAncestor() const
{
	return _LargeMutationChanceAncestor;
}

void APlantBase::SetSmallMutationChangeMin(float& SmallMutationChangeMin)
{
	_SmallMutationChangeMin = FMath::Clamp(SmallMutationChangeMin, 0.0f, _SmallMutationChangeMax);
}

float APlantBase::GetSmallMutationChangeMin() const
{
	return _SmallMutationChangeMin;
}

void APlantBase::SetSmallMutationChangeMax(const float& SmallMutationChangeMax)
{
	_SmallMutationChangeMax = FMath::Max(SmallMutationChangeMax, _SmallMutationChangeMin);
}

float APlantBase::GetSmallMutationChangeMax() const
{
	return _SmallMutationChangeMax;
}

void APlantBase::SetMediumMutationChangeMin(const float& MediumMutationChangeMin)
{
	_MediumMutationChangeMin = FMath::Clamp(MediumMutationChangeMin, 0.0f, _MediumMutationChangeMax);
}

float APlantBase::GetMediumMutationChangeMin() const
{
	return _MediumMutationChangeMin;
}

void APlantBase::SetMediumMutationChangeMax(const float& MediumMutationChangeMax)
{
	_MediumMutationChangeMax = FMath::Max(MediumMutationChangeMax, _MediumMutationChangeMin);
}

float APlantBase::GetMediumMutationChangeMax() const
{
	return _MediumMutationChangeMax;
}

void APlantBase::SetLargeMutationChangeMin(const float& LargeMutationChangeMin)
{
	_LargeMutationChangeMin = FMath::Clamp(LargeMutationChangeMin, 0.0f, _LargeMutationChangeMax);
}

float APlantBase::GetLargeMutationChangeMin() const
{
	return _LargeMutationChangeMin;
}

void APlantBase::SetLargeMutationChangeMax(const float& LargeMutationChangeMax)
{
	_LargeMutationChangeMax = FMath::Max(LargeMutationChangeMax, _LargeMutationChangeMin);
}

float APlantBase::GetLargeMutationChangeMax() const
{
	return _LargeMutationChangeMax;
}

void APlantBase::SetMutationsCount(const int32& MutationsCount)
{
	_MutationsCount = FMath::Max(0, MutationsCount);
}

int32 APlantBase::GetMutationsCount() const
{
	return _MutationsCount;
}

#pragma endregion

#pragma region Growth Setters/Getter

void APlantBase::SetTimeToGrowSeconds(const float& TimeToGrowSeconds)
{
	_TimeToGrowSeconds = FMath::Max(1.0f, TimeToGrowSeconds);
}

float APlantBase::GetTimeToGrowSeconds() const
{
	return _TimeToGrowSeconds;
}

void APlantBase::SetTimeSinceStartedGrowingSeconds(const float& TimeSinceStartedGrowingSeconds)
{
	_TimeSinceStartedGrowingSeconds = FMath::Max(0.0f, TimeSinceStartedGrowingSeconds);
}

float APlantBase::GetTimeSinceStartedGrowingSeconds() const
{
	return _TimeSinceStartedGrowingSeconds;
}

void APlantBase::SetTimeToReproductionAttemptSeconds(const float& TimeToReproductionAttemptSeconds)
{
	_TimeToReproductionAttemptSeconds = FMath::Max(1.0f, TimeToReproductionAttemptSeconds);
}

float APlantBase::GetTimeToReproductionAttemptSeconds() const
{
	return _TimeToReproductionAttemptSeconds;
}

void APlantBase::SetTimeSinceStartedReproductionAttemptSeconds(const float& TimeSinceStartedReproductionAttemptSeconds)
{
	_TimeSinceStartedReproductionAttemptSeconds = FMath::Max(0.0f, TimeSinceStartedReproductionAttemptSeconds);
}

float APlantBase::GetTimeSinceStartedReproductionAttemptSeconds() const
{
	return _TimeSinceStartedReproductionAttemptSeconds;
}

void APlantBase::SetEnvironmentMultiplier(const float& EnvironmentMultiplier)
{
	_EnvironmentMultiplier = FMath::Max(1.0f, EnvironmentMultiplier);
}

float APlantBase::GetEnvironmentMultiplier() const
{
	return _EnvironmentMultiplier;
}

void APlantBase::SetGrowPct(const float& GrowPct)
{
	_GrowPct = FMath::Clamp(GrowPct, 0.0f, 100.0f);
}

float APlantBase::GetGrowPct() const
{
	return _GrowPct;
}

void APlantBase::SetReproductionPct(const float& ReproductionPct)
{
	_ReproductionPct = FMath::Clamp(ReproductionPct, 0.0f, 100.0f);
}

float APlantBase::GetReproductionPct() const
{
	return _ReproductionPct;
}

void APlantBase::SetPlantStatus(const EPlantStatus& PlantStatus)
{
	_PlantStatus = PlantStatus;
}

EPlantStatus APlantBase::GetPlantStatus() const
{
	return _PlantStatus;
}

#pragma endregion

#pragma region Statistics Setters/Getters

void APlantBase::SetSpeciesName(const FString& SpeciesName)
{
	_SpeciesName = SpeciesName;
}

FString APlantBase::GetSpeciesName() const
{
	return _SpeciesName;
}

void APlantBase::SetInitialHealth(const float& InitialHealth)
{
	_InitialHealth = FMath::Max(1.0f, InitialHealth);
}

float APlantBase::GetInitialHealth() const
{
	return _InitialHealth;
}

void APlantBase::SetCurrentHealth(const float& CurrentHealth)
{
	_CurrentHealth = CurrentHealth;
}

float APlantBase::GetCurrentHealth() const
{
	return _CurrentHealth;
}

void APlantBase::SetInitialHealthLose(const float& InitialHealthLose)
{
	_InitialHealthLose = FMath::Max(0.0f, InitialHealthLose);
}

float APlantBase::GetInitialHealthLose() const
{
	return _InitialHealthLose;
}

void APlantBase::SetCurrentHealthLose(const float& CurrentHealthLose)
{
	_CurrentHealthLose = FMath::Max(0.0f, CurrentHealthLose);
}

float APlantBase::GetCurrentHealthLose() const
{
	return _CurrentHealthLose;
}

void APlantBase::SetHealthLoseMultiplier(const float& HealthLoseMultiplier)
{
	_HealthLoseMultiplier = FMath::Max(1.0f, HealthLoseMultiplier);
}

float APlantBase::GetHealthLoseMultiplier() const
{
	return _HealthLoseMultiplier;
}

void APlantBase::SetResistance(const float& Resistance)
{
	_Resistance = FMath::Clamp(Resistance, 0.0f, 100.0f);
}

float APlantBase::GetResistance() const
{
	return _Resistance;
}

void APlantBase::SetReproductionChancePct(const float& ReproductionChancePct)
{
	_ReproductionChancePct = FMath::Clamp(ReproductionChancePct, 0.0f, 100.0f);
}

float APlantBase::GetReproductionChancePct() const
{
	return _ReproductionChancePct;
}

void APlantBase::SetReproductionRange(const int32& ReproductionRange)
{
	_ReproductionRange = FMath::Max(1, ReproductionRange);
}

int32 APlantBase::GetReproductionRange() const
{
	return _ReproductionRange;
}

void APlantBase::SetNutrients(const float& Nutrients)
{
	_Nutrients = Nutrients;
}

float APlantBase::GetNutrients() const
{
	return _Nutrients;
}

#pragma endregion

#pragma region Environment Setters/Getter

void APlantBase::SetEnvironmentTemperature(const float& EnvironmentTemperature)
{
	_EnvironmentTemperature = FMath::Clamp(EnvironmentTemperature, 0.0f, 1.0f);
}

float APlantBase::GetEnvironmentTemperature() const
{
	return _EnvironmentTemperature;
}

void APlantBase::SetEnvironmentHumidity(const float& EnvironmentHumidity)
{
	_EnvironmentHumidity = FMath::Clamp(EnvironmentHumidity, 0.0f, 1.0f);
}

float APlantBase::GetEnvironmentHumidity() const
{
	return _EnvironmentHumidity;
}

void APlantBase::SetTimeToApplyEnvironmentEffectsSeconds(const float& TimeToApplyEnvironmentEffectsSeconds)
{
	_TimeToApplyEnvironmentEffectsSeconds = FMath::Max(1.0f, TimeToApplyEnvironmentEffectsSeconds);
}

float APlantBase::GetTimeToApplyEnvironmentEffectsSeconds() const
{
	return _TimeToApplyEnvironmentEffectsSeconds;
}

void APlantBase::SetTimeSinceEnvironmentEffectAppliement(const float& TimeSinceEnvironmentEffectAppliement)
{
	_TimeSinceEnvironmentEffectAppliement = FMath::Max(0.0f, TimeSinceEnvironmentEffectAppliement);
}

float APlantBase::GetTimeSinceEnvironmentEffectAppliement() const
{
	return _TimeSinceEnvironmentEffectAppliement;
}

void APlantBase::SetMinTemperature(const float& MinTemperature)
{
	_MinTemperature = FMath::Clamp(MinTemperature, 0.0f, _MaxTemperature);
}

float APlantBase::GetMinTemperature() const
{
	return _MinTemperature;
}

void APlantBase::SetMaxTemperature(const float& MaxTemperature)
{
	_MaxTemperature = FMath::Clamp(MaxTemperature, _MinTemperature, 1.0f);
}

float APlantBase::GetMaxTemperature() const
{
	return _MaxTemperature;
}

void APlantBase::SetIsInOptimalTemperature(const bool& IsInOptimalTemperature)
{
	_IsInOptimalTemperature = IsInOptimalTemperature;
}

bool APlantBase::GetIsInOptimalTemperature() const
{
	return _IsInOptimalTemperature;
}

void APlantBase::SetMinHumidity(const float& MinHumidity)
{
	_MinHumidity = FMath::Clamp(MinHumidity, 0.0f, _MaxHumidity);
}

float APlantBase::GetMinHumidity() const
{
	return _MinHumidity;
}

void APlantBase::SetMaxHumidity(const float& MaxHumidity)
{
	if (_MinHumidity > MaxHumidity)
		return;

	_MaxHumidity = FMath::Clamp(MaxHumidity, _MinHumidity, 1.0f);
}

float APlantBase::GetMaxHumidity() const
{
	return _MaxHumidity;
}

void APlantBase::SetIsInOptimalHumidity(const bool& IsInOptimalHumidity)
{
	_IsInOptimalHumidity = IsInOptimalHumidity;
}

bool APlantBase::GetIsInOptimalHumidity() const
{
	return _IsInOptimalHumidity;
}

#pragma endregion