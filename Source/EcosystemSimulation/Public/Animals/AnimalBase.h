// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimalBase.generated.h"

UENUM(BlueprintType)
enum class EAnimalGender : uint8
{
	NONE = 0 UMETA(DisplayName = "EMPTY"),
	MALE = 1 UMETA(DisplayName = "MALE"),
	FEMALE = 2  UMETA(DisplayName = "FEMALE"),
};

UCLASS()
class ECOSYSTEMSIMULATION_API AAnimalBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimalBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Mutations Setters/Getters

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSmallMutationChance(const float& SmallMutationChance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSmallMutationChance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMediumMutationChance(const float& MediumMutationChance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMediumMutationChance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLargeMutationChance(const float& LargeMutationChance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLargeMutationChance() const;

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

#pragma region Growth Setters/Getters

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsChild(const bool& IsChild);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsChild() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTimeToGrowSeconds(const float& TimeToGrowSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTimeToGrowSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetGrowthTimerSeconds(const float& GrowTimerSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetGrowthTimerSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetGrowthPct(const float& GrowthPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetGrowthPct() const;

#pragma endregion

#pragma region Traits Setters/Getters

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSpeciesName(const FString& SpeciesName);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FString GetSpeciesName() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetAttack(const float& Attack);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetAttack() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetInitialHealth(const float& InitialHealth);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetInitialHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCurrentHealth(const float& CurrentHealth);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetHungerMax(const float& HungerMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetHungerMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetHungerCurrent(const float& HungerCurrent);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetHungerCurrent() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetHungerGainSecond(const float& HungerGainSecond);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetHungerGainSecond() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetHungerPct(const float& HungerPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetHungerPct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetThirstMax(const float& ThirstMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetThirstMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetThirstCurrent(const float& ThirstCurrent);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetThirstCurrent() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetThirstGainSecond(const float& ThirstGainSecond);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetThirstGainSecond() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetThirstPct(const float& ThirstPct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetThirstPct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductiveUrgeMax(const float& ReproductiveUrgeMax);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductiveUrgeMax() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductiveUrgeCurrent(const float& ReproductiveUrgeCurrent);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductiveUrgeCurrent() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductiveUrgeGainSecond(const float& ReproductiveUrgeGainSecond);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductiveUrgeGainSecond() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetReproductiveUrgePct(const float& ReproductiveUrgePct);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetReproductiveUrgePct() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetInitialSpeed(const float& InitialSpeed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetInitialSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCurrentSpeed(const float& CurrentSpeed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCurrentSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSpeedMultiplierHT(const float& SpeedMultiplierHT);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSpeedMultiplierHT() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetInitialSensoryDistance(const float& InitialSensoryDistance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetInitialSensoryDistance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCurrentSensoryDistance(const float& CurrentSensoryDistance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCurrentSensoryDistance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSensoryDistanceMultiplierHT(const float& SensoryDistanceMultiplierHT);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetSensoryDistanceMultiplierHT() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetResistance(const float& Resistance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetResistance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetGender(const EAnimalGender& Gender);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	EAnimalGender GetGender() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetNutrients(const float& Nutrients);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetNutrients() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsEatingPlants(const bool& IsEatingPlants);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsEatingPlants() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsEatingAnimals(const bool& IsEatingAnimals);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsEatingAnimals() const;

#pragma endregion

#pragma region Environment Setters/Getters

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentStatusesAppliementSeconds(const float& EnvironmentStatusAppliementSeconds);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentStatusesAppliementSeconds() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentTemperature(const float& EnvironmentTemperature);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentTemperature() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetEnvironmentHumidity(const float& EnvironmentHumidity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetEnvironmentHumidity() const;

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

private:

#pragma region Mutations

	// Chance of ancestor small mutation
	UPROPERTY(BlueprintSetter = SetSmallMutationChance, BlueprintGetter = GetSmallMutationChance, EditAnywhere, Category = "Mutations")
	float _SmallMutationChance = 5.0f;

	// Chance of ancestor medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChance, BlueprintGetter = GetMediumMutationChance, EditAnywhere, Category = "Mutations")
	float _MediumMutationChance= 2.0f;

	// Chance of ancestor large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChance, BlueprintGetter = GetLargeMutationChance, EditAnywhere, Category = "Mutations")
	float _LargeMutationChance = 0.5f;

	// Minimum percentage value that value can change during small mutation
	UPROPERTY(BlueprintSetter = SetSmallMutationChangeMin, BlueprintGetter = GetSmallMutationChangeMin, EditAnywhere, Category = "Mutations")
	float _SmallMutationChangeMin = 0.0f;

	// Maximum percentage value that value can change during small mutation
	UPROPERTY(BlueprintSetter = SetSmallMutationChangeMax, BlueprintGetter = GetSmallMutationChangeMax, EditAnywhere, Category = "Mutations")
	float _SmallMutationChangeMax = 5.0f;

	// Minimum percentage value that value can change during medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChangeMin, BlueprintGetter = GetMediumMutationChangeMin, EditAnywhere, Category = "Mutations")
	float _MediumMutationChangeMin = 0.0f;

	// Maximum percentage value that value can change during medium mutation
	UPROPERTY(BlueprintSetter = SetMediumMutationChangeMax, BlueprintGetter = GetMediumMutationChangeMax, EditAnywhere, Category = "Mutations")
	float _MediumMutationChangeMax = 25.0f;

	// Minimum percentage value that value can change during large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChangeMin, BlueprintGetter = GetLargeMutationChangeMin, EditAnywhere, Category = "Mutations")
	float _LargeMutationChangeMin = 0.0f;

	// Maximum percentage value that value can change during large mutation
	UPROPERTY(BlueprintSetter = SetLargeMutationChangeMax, BlueprintGetter = GetLargeMutationChangeMax, EditAnywhere, Category = "Mutations")
	float _LargeMutationChangeMax = 50.0f;

	// Number of animal mutation since beginning of the simulation
	UPROPERTY(BlueprintSetter = SetMutationsCount, BlueprintGetter = GetMutationsCount, VisibleAnywhere, Category = "Mutations")
	int32 _MutationsCount = 0;

#pragma endregion

#pragma region Growth
	// Idicates if the animal is still a child
	UPROPERTY(BlueprintSetter = SetIsChild, BlueprintGetter = GetIsChild, VisibleAnywhere, Category = "Growth")
	bool _IsChild = true;
	
	// Time the animal need to grow up
	UPROPERTY(BlueprintSetter = SetTimeToGrowSeconds, BlueprintGetter = GetTimeToGrowSeconds, EditAnywhere, Category = "Growth")
	float _TimeToGrowSeconds = 60.0f;

	// Store time that passed since animal birth to grow up
	UPROPERTY(BlueprintSetter = SetGrowthTimerSeconds, BlueprintGetter = GetGrowthTimerSeconds, VisibleAnywhere, Category = "Growth")
	float _GrowthTimerSeconds = 0.0f;

	// Indicates Percentage value of animal growth
	UPROPERTY(BlueprintSetter = SetGrowthPct, BlueprintGetter = GetGrowthPct, VisibleAnywhere, Category = "Growth")
	float _GrowthPct = 0.0f;

#pragma endregion

#pragma region Traits
	
	UPROPERTY(BlueprintSetter = SetSpeciesName, BlueprintGetter = GetSpeciesName, EditAnywhere, Category = "Traits")
	FString _SpeciesName = "";
	
	UPROPERTY(BlueprintSetter = SetAttack, BlueprintGetter = GetAttack, EditAnywhere, Category = "Traits")
	float _Attack = 0.0f;

	// Initial Animal Health
	UPROPERTY(BlueprintSetter = SetInitialHealth, BlueprintGetter = GetInitialHealth, EditAnywhere, Category = "Traits")
	float _InitialHealth = 100.0f;

	// CurrentAnimalHealth
	UPROPERTY(BlueprintSetter = SetCurrentHealth, BlueprintGetter = GetCurrentHealth, EditAnywhere, Category = "Traits")
	float _CurrentHealth = 0.0f;

	// Maximum hunger. Higher value means that animal can survive longer without food
	UPROPERTY(BlueprintSetter = SetHungerMax, BlueprintGetter = GetHungerMax, EditAnywhere, Category = "Traits")
	float _HungerMax = 100.0f;

	// Current value of hunger
	UPROPERTY(BlueprintSetter = SetHungerCurrent, BlueprintGetter = GetHungerCurrent, VisibleAnywhere, Category = "Traits")
	float _HungerCurrent = 0.0f;

	// Indicates how more hungry the animal will become every second
	UPROPERTY(BlueprintSetter = SetHungerGainSecond, BlueprintGetter = GetHungerGainSecond, EditAnywhere, Category = "Traits")
	float _HungerGainSecond = 2.0f;

	// Indicates percentage value of animal hunger
	UPROPERTY(BlueprintSetter = SetHungerPct, BlueprintGetter = GetHungerPct, EditAnywhere, Category = "Traits")
	float _HungerPct = 0.0f;

	// Maximum hunger. Higher value means that animal can survive longer without water
	UPROPERTY(BlueprintSetter = SetThirstMax, BlueprintGetter = GetThirstMax, EditAnywhere, Category = "Traits")
	float _ThirstMax = 100.0f;

	// Current value of thirst
	UPROPERTY(BlueprintSetter = SetThirstCurrent, BlueprintGetter = GetThirstCurrent, VisibleAnywhere, Category = "Traits")
	float _ThirstCurrent = 0.0f;

	// Indicates how more thirsty the animal will become every second
	UPROPERTY(BlueprintSetter = SetThirstGainSecond, BlueprintGetter = GetThirstGainSecond, EditAnywhere, Category = "Traits")
	float _ThirstGainSecond = 2.0f;

	// Indicates percentage value of animal thirst
	UPROPERTY(BlueprintSetter = SetThirstPct, BlueprintGetter = GetThirstPct, EditAnywhere, Category = "Traits")
	float _ThirstPct = 0.0f;

	// Reproduction urge. Higher value means the animal will need more time start reproducing
	UPROPERTY(BlueprintSetter = SetReproductiveUrgeMax, BlueprintGetter = GetReproductiveUrgeMax, EditAnywhere, Category = "Traits")
	float _ReproductiveUrgeMax = 100.0f;

	// Current value of reproductive urge
	UPROPERTY(BlueprintSetter = SetReproductiveUrgeCurrent, BlueprintGetter = GetReproductiveUrgeCurrent, VisibleAnywhere, Category = "Traits")
	float _ReproductiveUrgeCurrent = 0.0f;

	// Indicates Reproductive Urge Gain every secons
	UPROPERTY(BlueprintSetter = SetReproductiveUrgeGainSecond, BlueprintGetter = GetReproductiveUrgeGainSecond, EditAnywhere, Category = "Traits")
	float _ReproductiveUrgeGainSecond = 1.0f;

	// Indicates percentage value of animal reproductive urge
	UPROPERTY(BlueprintSetter = SetReproductiveUrgePct, BlueprintGetter = GetReproductiveUrgePct, EditAnywhere, Category = "Traits")
	float _ReproductiveUrgePct = 0.0f;

	// Indicates initial speed of the animal. Faster animal -> faster hunger and thirst gain
	UPROPERTY(BlueprintSetter = SetInitialSpeed, BlueprintGetter = GetGrowthPct, EditAnywhere, Category = "Traits")
	float _InitialSpeed = 100.0f;

	// Current speed is equal to Initial Speed at the beginning of the simulation, but can change after mutation
	UPROPERTY(BlueprintSetter = SetCurrentSpeed, BlueprintGetter = GetCurrentSpeed, VisibleAnywhere, Category = "Traits")
	float _CurrentSpeed = 0.0f;

	// _CurrentSpeed / _InitialSpeed -> Multiplier for hunger and thirst gain calculations
	UPROPERTY(BlueprintSetter = SetSpeedMultiplierHT, BlueprintGetter = GetSpeedMultiplierHT, VisibleAnywhere, Category = "Traits")
	float _SpeedMultiplierHT = 1.0f;

	// Indicates how far the animal can see. Logner Sensory Distance -> faster hunger and thirst gain
	UPROPERTY(BlueprintSetter = SetInitialSensoryDistance, BlueprintGetter = GetInitialSensoryDistance, EditAnywhere, Category = "Traits")
	float _InitialSensoryDistance = 100.0f;

	// Current Sensory Distance is equal to Initial Sensory Distance at the beginning of the simulation, but can change after mutation
	UPROPERTY(BlueprintSetter = SetCurrentSensoryDistance, BlueprintGetter = GetCurrentSensoryDistance, VisibleAnywhere, Category = "Traits")
	float _CurrentSensoryDistance = 0.0f;

	// _CurrentSensoryDistance / _InitialSensoryDistance -> Multiplier for hunger and thirst gain calculations
	UPROPERTY(BlueprintSetter = SetSensoryDistanceMultiplierHT, BlueprintGetter = GetSensoryDistanceMultiplierHT, VisibleAnywhere, Category = "Traits")
	float _SensoryDistanceMultiplierHT = 1.0f;

	// Indicates the percentage value that every damage income will be lower
	UPROPERTY(BlueprintSetter = SetResistance, BlueprintGetter = GetResistance, EditAnywhere, Category = "Traits")
	float _Resistance = 10.0f;

	// Gender of the Animal
	UPROPERTY(BlueprintSetter = SetGender, BlueprintGetter = GetGender, VisibleAnywhere, Category = "Traits")
	EAnimalGender _Gender = EAnimalGender::NONE;

	UPROPERTY(BlueprintSetter = SetNutrients, BlueprintGetter = GetNutrients, EditAnywhere, Category = "Traits")
	float _Nutrients = 0.0f;

	UPROPERTY(BlueprintSetter = SetIsEatingPlants, BlueprintGetter = GetIsEatingPlants, EditAnywhere, Category = "Traits")
	bool _IsEatingPlants = true;

	UPROPERTY(BlueprintSetter = SetIsEatingAnimals, BlueprintGetter = GetIsEatingAnimals, EditAnywhere, Category = "Traits")
	bool _IsEatingAnimals = true;

#pragma endregion

#pragma region Environment

	// Indicates how often buffs and debuffs from environment are applied to the animal
	UPROPERTY(BlueprintSetter = SetEnvironmentStatusesAppliementSeconds, BlueprintGetter = GetEnvironmentStatusesAppliementSeconds, EditAnywhere, Category = "Environment")
	float _EnvironmentStatusesAppliementSeconds = 5.0f;

	// Environment Temperature in which the animal is staying
	UPROPERTY(BlueprintSetter = SetEnvironmentTemperature, BlueprintGetter = GetEnvironmentTemperature, VisibleAnywhere, Category = "Environment")
	float _EnvironmentTemperature = 0.5f;

	// Environment Humidity in which the animal is staying
	UPROPERTY(BlueprintSetter = SetEnvironmentHumidity, BlueprintGetter = GetEnvironmentHumidity, VisibleAnywhere, Category = "Environment")
	float _EnvironmentHumidity = 0.5f;

	// Minimum Temperature in which the animal can survive
	UPROPERTY(BlueprintSetter = SetMinTemperature, BlueprintGetter = GetMinTemperature, EditAnywhere, Category = "Environment")
	float _MinTemperature = 0.0f;

	// Maximum Temperature in which the animal can survive
	UPROPERTY(BlueprintSetter = SetMaxTemperature, BlueprintGetter = GetMaxTemperature, EditAnywhere, Category = "Environment")
	float _MaxTemperature = 1.0f;

	// Indicates if the animal is staying in optimal temperature
	UPROPERTY(BlueprintSetter = SetIsInOptimalTemperature, BlueprintGetter = GetIsInOptimalTemperature, VisibleAnywhere, Category = "Environment")
	bool _IsInOptimalTemperature = false;

	// Minimum Humidity in which the animal can survive
	UPROPERTY(BlueprintSetter = SetMinHumidity, BlueprintGetter = GetMinHumidity, EditAnywhere, Category = "Environment")
	float _MinHumidity = 0.0f;

	// Maximum Temperature in which the animal can survive
	UPROPERTY(BlueprintSetter = SetMaxHumidity, BlueprintGetter = GetMaxHumidity, EditAnywhere, Category = "Environment")
	float _MaxHumidity = 1.0f;

	// Indicates if the animal is staying in optimal humidity
	UPROPERTY(BlueprintSetter = SetIsInOptimalHumidity, BlueprintGetter = GetIsInOptimalHumidity, VisibleAnywhere, Category = "Environment")
	bool _IsInOptimalHumidity = false;

#pragma endregion

};
