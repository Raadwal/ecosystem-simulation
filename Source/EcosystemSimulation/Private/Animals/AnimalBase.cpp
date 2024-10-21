// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/AnimalBase.h"

// Sets default values
AAnimalBase::AAnimalBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();

	_CurrentHealth = _InitialHealth;
	_CurrentSpeed = _InitialSpeed;
	_CurrentSensoryDistance = _InitialSensoryDistance;

	(FMath::RandRange(0, 1) == 1) ? _Gender = EAnimalGender::MALE : _Gender = EAnimalGender::FEMALE;
}

#pragma region Mutations Setters/Getters

void AAnimalBase::SetSmallMutationChance(const float& SmallMutationChance)
{
	_SmallMutationChance = FMath::Clamp(SmallMutationChance, 0.0f, 100.0f);
}

float AAnimalBase::GetSmallMutationChance() const
{
	return _SmallMutationChance;
}

void AAnimalBase::SetMediumMutationChance(const float& MediumMutationChance)
{
	_MediumMutationChance = FMath::Clamp(MediumMutationChance, 0.0f, 100.0f);
}

float AAnimalBase::GetMediumMutationChance() const
{
	return _MediumMutationChance;
}

void AAnimalBase::SetLargeMutationChance(const float& LargeMutationChance)
{
	_LargeMutationChance = FMath::Clamp(LargeMutationChance, 0.0f, 100.0f);
}

float AAnimalBase::GetLargeMutationChance() const
{
	return _LargeMutationChance;
}

void AAnimalBase::SetSmallMutationChangeMin(float& SmallMutationChangeMin)
{
	_SmallMutationChangeMin = FMath::Clamp(SmallMutationChangeMin, 0.0f, _SmallMutationChangeMax);
}

float AAnimalBase::GetSmallMutationChangeMin() const
{
	return _SmallMutationChangeMin;
}

void AAnimalBase::SetSmallMutationChangeMax(const float& SmallMutationChangeMax)
{
	_SmallMutationChangeMax = FMath::Max(SmallMutationChangeMax, _SmallMutationChangeMin);
}

float AAnimalBase::GetSmallMutationChangeMax() const
{
	return _SmallMutationChangeMax;
}

void AAnimalBase::SetMediumMutationChangeMin(const float& MediumMutationChangeMin)
{
	_MediumMutationChangeMin = FMath::Clamp(MediumMutationChangeMin, 0.0f, _MediumMutationChangeMax);
}

float AAnimalBase::GetMediumMutationChangeMin() const
{
	return _MediumMutationChangeMin;
}

void AAnimalBase::SetMediumMutationChangeMax(const float& MediumMutationChangeMax)
{
	_MediumMutationChangeMax = FMath::Max(MediumMutationChangeMax, _MediumMutationChangeMin);
}

float AAnimalBase::GetMediumMutationChangeMax() const
{
	return _MediumMutationChangeMax;
}

void AAnimalBase::SetLargeMutationChangeMin(const float& LargeMutationChangeMin)
{
	_LargeMutationChangeMin = FMath::Clamp(LargeMutationChangeMin, 0.0f, _LargeMutationChangeMax);
}

float AAnimalBase::GetLargeMutationChangeMin() const
{
	return _LargeMutationChangeMin;
}

void AAnimalBase::SetLargeMutationChangeMax(const float& LargeMutationChangeMax)
{
	_LargeMutationChangeMax = FMath::Max(LargeMutationChangeMax, _LargeMutationChangeMin);
}

float AAnimalBase::GetLargeMutationChangeMax() const
{
	return _LargeMutationChangeMax;
}

void AAnimalBase::SetMutationsCount(const int32& MutationsCount)
{
	_MutationsCount = FMath::Max(MutationsCount, 0.0f);
}

int32 AAnimalBase::GetMutationsCount() const
{
	return _MutationsCount;
}

#pragma endregion

#pragma region Growth Setters/Getters

void AAnimalBase::SetIsChild(const bool& IsChild)
{
	_IsChild = IsChild;
}

bool AAnimalBase::GetIsChild() const
{
	return _IsChild;
}

void AAnimalBase::SetTimeToGrowSeconds(const float& TimeToGrowSeconds)
{
	_TimeToGrowSeconds = FMath::Max(TimeToGrowSeconds, 1.0f);
}

float AAnimalBase::GetTimeToGrowSeconds() const
{
	return _TimeToGrowSeconds;
}

void AAnimalBase::SetGrowthTimerSeconds(const float& GrowTimerSeconds)
{
	_GrowthTimerSeconds = FMath::Clamp(GrowTimerSeconds, 0.0f, _TimeToGrowSeconds);
}

float AAnimalBase::GetGrowthTimerSeconds() const
{
	return _GrowthTimerSeconds;
}

void AAnimalBase::SetGrowthPct(const float& GrowthPct)
{
	_GrowthPct = FMath::Clamp(GrowthPct, 0.0f, 100.0f);
}

float AAnimalBase::GetGrowthPct() const
{
	return _GrowthPct;
}

#pragma endregion

#pragma region Traits Setters/Getters

void AAnimalBase::SetSpeciesName(const FString& SpeciesName)
{
	_SpeciesName = SpeciesName;
}

FString AAnimalBase::GetSpeciesName() const
{
	return _SpeciesName;
}

void AAnimalBase::SetAttack(const float& Attack)
{
	_Attack = FMath::Max(0.0f, Attack);
}

float AAnimalBase::GetAttack() const
{
	return _Attack;
}

void AAnimalBase::SetInitialHealth(const float& InitialHealth)
{
	_InitialHealth = FMath::Max(InitialHealth, 0.0f);
}

float AAnimalBase::GetInitialHealth() const
{
	return _InitialHealth;
}

void AAnimalBase::SetCurrentHealth(const float& CurrentHealth)
{
	_CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, _InitialHealth);
}

float AAnimalBase::GetCurrentHealth() const
{
	return _CurrentHealth;
}

void AAnimalBase::SetHungerMax(const float& HungerMax)
{
	_HungerMax = FMath::Max(HungerMax, 0.0f);
}

float AAnimalBase::GetHungerMax() const
{
	return _HungerMax;
}

void AAnimalBase::SetHungerCurrent(const float& HungerCurrent)
{
	_HungerCurrent = FMath::Clamp(HungerCurrent, 0.0f, _HungerMax);
}

float AAnimalBase::GetHungerCurrent() const
{
	return _HungerCurrent;
}

void AAnimalBase::SetHungerGainSecond(const float& HungerGainSecond)
{
	_HungerGainSecond = FMath::Max(HungerGainSecond, 0.0f);
}

float AAnimalBase::GetHungerGainSecond() const
{
	return _HungerGainSecond;
}

void AAnimalBase::SetHungerPct(const float& HungerPct)
{
	_HungerPct = FMath::Clamp(HungerPct, 0.0f, 100.0f);
}

float AAnimalBase::GetHungerPct() const
{
	return _HungerPct;
}

void AAnimalBase::SetThirstMax(const float& ThirstMax)
{
	_ThirstMax = FMath::Max(ThirstMax, 0.0f);
}

float AAnimalBase::GetThirstMax() const
{
	return _ThirstMax;
}

void AAnimalBase::SetThirstCurrent(const float& ThirstCurrent)
{
	_ThirstCurrent = FMath::Clamp(ThirstCurrent, 0.0f, _ThirstMax);
}

float AAnimalBase::GetThirstCurrent() const
{
	return _ThirstCurrent;
}

void AAnimalBase::SetThirstGainSecond(const float& ThirstGainSecond)
{
	_ThirstGainSecond = FMath::Max(ThirstGainSecond, 0.0f);
}

float AAnimalBase::GetThirstGainSecond() const
{
	return _ThirstGainSecond;
}

void AAnimalBase::SetThirstPct(const float& ThirstPct)
{
	_ThirstPct = FMath::Clamp(ThirstPct, 0.0f, 100.0f);
}

float AAnimalBase::GetThirstPct() const
{
	return _ThirstPct;
}

void AAnimalBase::SetReproductiveUrgeMax(const float& ReproductiveUrgeMax)
{
	_ReproductiveUrgeMax = FMath::Max(ReproductiveUrgeMax, 0.0f);
}

float AAnimalBase::GetReproductiveUrgeMax() const
{
	return _ReproductiveUrgeMax;
}

void AAnimalBase::SetReproductiveUrgeCurrent(const float& ReproductiveUrgeCurrent)
{
	_ReproductiveUrgeCurrent = FMath::Clamp(ReproductiveUrgeCurrent, 0.0f, _ReproductiveUrgeMax);
}

float AAnimalBase::GetReproductiveUrgeCurrent() const
{
	return _ReproductiveUrgeCurrent;
}

void AAnimalBase::SetReproductiveUrgeGainSecond(const float& ReproductiveUrgeGainSecond)
{
	_ReproductiveUrgeGainSecond = FMath::Max(ReproductiveUrgeGainSecond, 0.0f);
}

float AAnimalBase::GetReproductiveUrgeGainSecond() const
{
	return _ReproductiveUrgeGainSecond;
}

void AAnimalBase::SetReproductiveUrgePct(const float& ReproductiveUrgePct)
{
	_ReproductiveUrgePct = FMath::Clamp(ReproductiveUrgePct, 0.0f, 100.0f);
}

float AAnimalBase::GetReproductiveUrgePct() const
{
	return _ReproductiveUrgePct;
}

void AAnimalBase::SetInitialSpeed(const float& InitialSpeed)
{
	_InitialSpeed = FMath::Max(InitialSpeed, 0.0f);
}

float AAnimalBase::GetInitialSpeed() const
{
	return _InitialSpeed;
}

void AAnimalBase::SetCurrentSpeed(const float& CurrentSpeed)
{
	_CurrentSpeed = FMath::Max(CurrentSpeed, 0.0f);
}

float AAnimalBase::GetCurrentSpeed() const
{
	return _CurrentSpeed;
}

void AAnimalBase::SetSpeedMultiplierHT(const float& SpeedMultiplierHT)
{
	_SpeedMultiplierHT = FMath::Clamp(SpeedMultiplierHT, 0.0f, 100.0f);
}

float AAnimalBase::GetSpeedMultiplierHT() const
{
	return _SpeedMultiplierHT;
}

void AAnimalBase::SetInitialSensoryDistance(const float& InitialSensoryDistance)
{
	_InitialSensoryDistance = FMath::Max(InitialSensoryDistance, 0.0f);
}

float AAnimalBase::GetInitialSensoryDistance() const
{
	return _InitialSensoryDistance;
}

void AAnimalBase::SetCurrentSensoryDistance(const float& CurrentSensoryDistance)
{
	_CurrentSensoryDistance = FMath::Max(CurrentSensoryDistance, 0.0f);
}

float AAnimalBase::GetCurrentSensoryDistance() const
{
	return _CurrentSensoryDistance;
}

void AAnimalBase::SetSensoryDistanceMultiplierHT(const float& SensoryDistanceMultiplierHT)
{
	_SensoryDistanceMultiplierHT = FMath::Clamp(SensoryDistanceMultiplierHT, 0.0f, 100.0f);
}

float AAnimalBase::GetSensoryDistanceMultiplierHT() const
{
	return _SensoryDistanceMultiplierHT;
}

void AAnimalBase::SetResistance(const float& Resistance)
{
	_Resistance = FMath::Clamp(Resistance, 0.0f, 100.0f);
}

float AAnimalBase::GetResistance() const
{
	return _Resistance;
}

void AAnimalBase::SetGender(const EAnimalGender& Gender)
{
	_Gender = Gender;
}

EAnimalGender AAnimalBase::GetGender() const
{
	return _Gender;
}

void AAnimalBase::SetNutrients(const float& Nutrients)
{
	_Nutrients = Nutrients;
}

float AAnimalBase::GetNutrients() const
{
	return _Nutrients;
}

void AAnimalBase::SetIsEatingPlants(const bool& IsEatingPlants)
{
	_IsEatingPlants = IsEatingPlants;
}

bool AAnimalBase::GetIsEatingPlants() const
{
	return _IsEatingPlants;
}

void AAnimalBase::SetIsEatingAnimals(const bool& IsEatingAnimals)
{
	_IsEatingAnimals = IsEatingAnimals;
}

bool AAnimalBase::GetIsEatingAnimals() const
{
	return _IsEatingAnimals;
}

#pragma endregion

#pragma region Environment Setters/Getters

void AAnimalBase::SetEnvironmentStatusesAppliementSeconds(const float& EnvironmentStatusAppliementSeconds)
{
	_EnvironmentStatusesAppliementSeconds = FMath::Max(EnvironmentStatusAppliementSeconds, 0.0f);
}

float AAnimalBase::GetEnvironmentStatusesAppliementSeconds() const
{
	return _EnvironmentStatusesAppliementSeconds;
}

void AAnimalBase::SetEnvironmentTemperature(const float& EnvironmentTemperature)
{
	_EnvironmentTemperature = FMath::Clamp(EnvironmentTemperature, 0.0f, 1.0f);
}

float AAnimalBase::GetEnvironmentTemperature() const
{
	return _EnvironmentTemperature;
}

void AAnimalBase::SetEnvironmentHumidity(const float& EnvironmentHumidity)
{
	_EnvironmentHumidity = FMath::Clamp(EnvironmentHumidity, 0.0f, 1.0f);
}

float AAnimalBase::GetEnvironmentHumidity() const
{
	return _EnvironmentHumidity;
}

void AAnimalBase::SetMinTemperature(const float& MinTemperature)
{
	_MinTemperature = FMath::Clamp(MinTemperature, 0.0f, _MaxTemperature);
}

float AAnimalBase::GetMinTemperature() const
{
	return _MinTemperature;
}

void AAnimalBase::SetMaxTemperature(const float& MaxTemperature)
{
	_MaxTemperature = FMath::Clamp(MaxTemperature, _MinTemperature, 1.0f);
}

float AAnimalBase::GetMaxTemperature() const
{
	return _MaxTemperature;
}

void AAnimalBase::SetIsInOptimalTemperature(const bool& IsInOptimalTemperature)
{
	_IsInOptimalTemperature = IsInOptimalTemperature;
}

bool AAnimalBase::GetIsInOptimalTemperature() const
{
	return _IsInOptimalTemperature;
}

void AAnimalBase::SetMinHumidity(const float& MinHumidity)
{
	_MinHumidity = FMath::Clamp(MinHumidity, 0.0f, _MaxHumidity);
}

float AAnimalBase::GetMinHumidity() const
{
	return _MinHumidity;
}

void AAnimalBase::SetMaxHumidity(const float& MaxHumidity)
{
	_MaxHumidity = FMath::Clamp(MaxHumidity, _MinHumidity, 1.0f);
}

float AAnimalBase::GetMaxHumidity() const
{
	return _MaxHumidity;
}

void AAnimalBase::SetIsInOptimalHumidity(const bool& IsInOptimalHumidity)
{
	_IsInOptimalHumidity = IsInOptimalHumidity;
}

bool AAnimalBase::GetIsInOptimalHumidity() const
{
	return _IsInOptimalHumidity;
}

#pragma endregion