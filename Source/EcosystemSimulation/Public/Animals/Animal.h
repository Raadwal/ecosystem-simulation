// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animals/AnimalBase.h"

#include "../DataStructures.h"

#include "Math/NumericLimits.h" 

#include "Animal.generated.h"

UENUM(BlueprintType)
enum class EAnimalState : uint8
{
	NONE = 0 UMETA(DisplayName = "EMPTY"),
	THIRSTY = 1 UMETA(DisplayName = "THIRSTY"),
	HUNGRY = 2  UMETA(DisplayName = "HUNGRY"),
	REPRODUCTION = 3 UMETA(DisplayName = "REPRODUCTION"),
	RUNNING_AWAY = 4 UMETA(DisplayName = "RUNNING_AWAY")
};

/**
 * 
 */
UCLASS()
class ECOSYSTEMSIMULATION_API AAnimal : public AAnimalBase
{
	GENERATED_BODY()
	
public: 
	AAnimal();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Check which action has higher priority
	virtual const EAnimalState CheckNextAction();

	UFUNCTION(BluePrintCallable)
	virtual void Reproduce();

	UFUNCTION(BlueprintCallable)
	void SetEnvironmentData(const TArray<FTerrainData>& TerrainData);

	UFUNCTION(BlueprintCallable)
	FVector2D FindWaterPosition() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetState(const EAnimalState& State);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	EAnimalState GetState() const;

#pragma region Biomes Modifiers
	/**
	* If Animal is in optimal environment (temperature and humididty)
	* buffs are multiplied by 1.25 and debuffs are not applied
	*
	* If Animal is partially in optimal environment (temperature or humididty)
	* buffs and debuffs are normally applied
	* 
	* If Animal is not partially in optimal environment (temperature and humididty)
	* buffs are not applied and debuffs are multiplied by 1.25;
	*/

	/**
	* Buffs:
	*	- Significantly sight range increase
	*	- Slightly slower hunger gain
	* 
	* Debuffs:
	*	- Significantly faster thirst gain
	*	- Slightly movement speed decrease
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ApplyDesertBiomeEffects();

	/**
	* Buffs:
	*	- Slightly slower thirst gain
	*	- Slightly slower hunger gain
	*   - Slightly faster reproduction urge gain
	* 
	* Debuffs:
	*	- Slightly movement speed decrease
	*	- Significantly sight range decrease
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ApplyJungleBiomeEffects();

	/**
	*	Buffs:
	*	- Significantly sight range increase
	*	- Significantly reproductive urge gain increase
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ApplyGrasslandsEffects();

	/**
	* Buffs:
	*	- Significantly sight range increase
	*	- Slightly slower thirst gain
	* 
	* Debuffs:
	*	- Significantly faster hunger gain
	*	- Significantly movement speed decrease
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ApplySnowBiomeEffects();

	/**
	* Buffs:
	*	- Slightly slower thirst gain
	*	- Slightly slower hunger gain
	*	- Slightly reproductive urge gain increase
	* Debuffs:
	*	- Slightly sight range decrease
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ApplyForestBiomeEffects();

#pragma endregion

private:
	UPROPERTY(EditDefaultsOnly)
	float _WorldScale = 100.0f;

	UPROPERTY(Transient)
	float _UpdateEnvironmentDataTimer = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float _WaterHeight = 0.3f;

	UPROPERTY(Transient)
	TArray<float> _TemperatureMap;

	UPROPERTY(Transient)
	TArray<float> _HumidiyMap;

	UPROPERTY(Transient)
	TArray<FVector2D> _WaterMap;

	UPROPERTY(BlueprintSetter = SetState, BlueprintGetter = GetState, VisibleAnywhere)
	EAnimalState _State = EAnimalState::NONE;

#pragma region Timers
	
	UPROPERTY(Transient)
	FTimerHandle _EnvironmentStatusesTimer;

	UPROPERTY(Transient)
	FTimerHandle _HungerTimer;

	UPROPERTY(Transient)
	FTimerHandle _ThirstTimer;

	UPROPERTY(Transient)
	FTimerHandle _ReproductiveUrgeTimer;

#pragma endregion

#pragma region Biomes Modifiers

	UPROPERTY(EditDefaultsOnly)
	float _SlightlyChangeValue = 0.1f;

	UPROPERTY(EditDefaultsOnly)
	float _SignificantlyChangeValue = 0.25f;

	UPROPERTY(VisibleAnywhere)
	float _SpeedModifier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float _SightModifier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float _HungerModifier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float _ThirstModifier = 1.0f;

	UPROPERTY(VisibleAnywhere)
	float _ReproductiveUrgeModifier = 1.0f;

	void ResetModifiers();

	void SetEnvironmentBuffsMultipliers(float& BuffsMultipliers, float& DebuffsMultpliers);

#pragma endregion

#pragma region Biomes Collision

	UPROPERTY(VisibleAnywhere)
	bool _AreSnowBiomeEffectsApplied = false;

	UPROPERTY(VisibleAnywhere)
	bool _AreForestBiomeEffectsApplied = false;

	UPROPERTY(VisibleAnywhere)
	bool _AreGrasslandsBiomeEffectsApplied = false;

	UPROPERTY(VisibleAnywhere)
	bool _AreDesertBiomeEffectsApplied = false;

	UPROPERTY(VisibleAnywhere)
	bool _AreJungleBiomeEffectsApplied = false;

#pragma endregion

#pragma region Time

	void UpdateEnvironmentData(const float& DeltaTime);

	void Grow(const float& DeltaTime);

	void ApplyEnvironmentStatuses();

	void GainHunger();

	void GainThirst();

	void GainReproductiveUrge();

#pragma endregion

	void ApplyDamage(const float& Damage);

	void QuickLog(const FColor Color, const FString Message) const;
};
