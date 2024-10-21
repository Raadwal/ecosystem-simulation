// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/Animal.h"

// Sets default values
AAnimal::AAnimal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	// Set up timers

	// All timers won't fire in the same moment - CPU usage optimatization
	const float TimeDelay = FMath::FRandRange(0.0f, 1.0f);

	GetWorldTimerManager().SetTimer(_EnvironmentStatusesTimer, this, &AAnimal::ApplyEnvironmentStatuses, GetEnvironmentStatusesAppliementSeconds(), true, TimeDelay);
	GetWorldTimerManager().SetTimer(_HungerTimer, this, &AAnimal::GainHunger, 1.0f, true, TimeDelay);
	GetWorldTimerManager().SetTimer(_ThirstTimer, this, &AAnimal::GainThirst, 1.0f, true, TimeDelay);
	GetWorldTimerManager().SetTimer(_ReproductiveUrgeTimer, this, &AAnimal::GainReproductiveUrge, 1.0f, true, TimeDelay);
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Grow if is a child
	if (GetIsChild())
	{
		Grow(DeltaTime);
	}

	CheckNextAction();
	UpdateEnvironmentData(DeltaTime);
}

const EAnimalState AAnimal::CheckNextAction()
{
	// Array of allowed states
	TArray<TPair<const EAnimalState, const float>> AllowedActions;
	AllowedActions.Add(TPair<const EAnimalState, const float>(EAnimalState::HUNGRY, GetHungerPct()));
	AllowedActions.Add(TPair<const EAnimalState, const float>(EAnimalState::THIRSTY, GetThirstPct()));
	AllowedActions.Add(TPair<const EAnimalState, const float>(EAnimalState::REPRODUCTION, GetReproductiveUrgePct()));

	// Variable to store most urgent state
	TPair<EAnimalState, float> MaximumValue(EAnimalState::NONE, 0.0f);

	// Looking for most urgent state
	for (const TPair<const EAnimalState, const float> ActionValue : AllowedActions)
	{
		if (MaximumValue.Value > ActionValue.Value)
			continue;

		MaximumValue = ActionValue;
	}

	_State = MaximumValue.Key;

	return MaximumValue.Key;
}

void AAnimal::SetEnvironmentData(const TArray<FTerrainData>& TerrainData)
{
	// Initialize Arrays
	_TemperatureMap.Init(0.0f, TerrainData.Num());
	_HumidiyMap.Init(0.0f, TerrainData.Num());

	_WaterMap.Empty();

	// Copy needed data
	for (int32 Idx = 0; Idx < TerrainData.Num(); Idx++)
	{
		_TemperatureMap[Idx] = TerrainData[Idx].Temperature;
		_HumidiyMap[Idx] = TerrainData[Idx].Humidity;

		if (TerrainData[Idx].Height <= _WaterHeight)
		{
			_WaterMap.Add(FVector2D(TerrainData[Idx].PosX * _WorldScale, TerrainData[Idx].PosY * _WorldScale));
		}
	}
}

FVector2D AAnimal::FindWaterPosition() const
{
	float PosX = GetActorLocation().X;
	float PosY = GetActorLocation().Y;

	float LowestDistance = TNumericLimits<float>::Max();

	for (FVector2D Position : _WaterMap)
	{
		float DiffX = GetActorLocation().X - Position.X;
		float DiffY = GetActorLocation().Y - Position.Y;

		float Distance = FMath::Sqrt(FMath::Square(DiffX) + FMath::Square(DiffY));

		if (LowestDistance > Distance)
		{
			LowestDistance = Distance;
			PosX = Position.X;
			PosY = Position.Y;
		}
	}

	return FVector2D(PosX, PosY);
}

void AAnimal::SetState(const EAnimalState& State)
{
	_State = State;
}

EAnimalState AAnimal::GetState() const
{
	return _State;
}

void AAnimal::Reproduce()
{
	// Remebmer to calculate!
	// _SpeedMultiplierHT
	// _SensoryDistanceMultiplierHT
}

#pragma region Biomes Effects

void AAnimal::ApplyDesertBiomeEffects()
{
	//if (_AreDesertBiomeEffectsApplied)
		//return;

	// Reset other biome effects
	ResetModifiers();

	_AreSnowBiomeEffectsApplied = false;
	_AreForestBiomeEffectsApplied = false;
	_AreGrasslandsBiomeEffectsApplied = false;
	_AreJungleBiomeEffectsApplied = false;

	_AreDesertBiomeEffectsApplied = true;

	float BuffsMultiplier = 1.0f;
	float DebuffsMultiplier = 1.0f;
	SetEnvironmentBuffsMultipliers(BuffsMultiplier, DebuffsMultiplier);

	// Buffs
	_SightModifier += _SignificantlyChangeValue * BuffsMultiplier;
	_HungerModifier -= _SlightlyChangeValue * BuffsMultiplier;

	// Debuffs
	_ThirstModifier += _SignificantlyChangeValue * DebuffsMultiplier;
	_SpeedModifier -= _SlightlyChangeValue * DebuffsMultiplier;
}

void AAnimal::ApplyJungleBiomeEffects()
{
	//if (_AreJungleBiomeEffectsApplied)
		//return;

	// Reset other biome effects
	ResetModifiers();

	_AreSnowBiomeEffectsApplied = false;
	_AreForestBiomeEffectsApplied = false;
	_AreGrasslandsBiomeEffectsApplied = false;
	_AreDesertBiomeEffectsApplied = false;

	_AreJungleBiomeEffectsApplied = true;

	float BuffsMultiplier = 1.0f;
	float DebuffsMultiplier = 1.0f;
	SetEnvironmentBuffsMultipliers(BuffsMultiplier, DebuffsMultiplier);

	// Buffs
	_ThirstModifier -= _SlightlyChangeValue * BuffsMultiplier;;
	_HungerModifier -= _SlightlyChangeValue * BuffsMultiplier;;
	_ReproductiveUrgeModifier += _SlightlyChangeValue * BuffsMultiplier;;

	// Debuffs
	_SpeedModifier -= _SlightlyChangeValue * DebuffsMultiplier;
	_SightModifier -= _SignificantlyChangeValue * DebuffsMultiplier;
}

void AAnimal::ApplyGrasslandsEffects()
{
	//if (_AreGrasslandsBiomeEffectsApplied)
		//return;

	// Reset other biome effects
	ResetModifiers();

	_AreSnowBiomeEffectsApplied = false;
	_AreForestBiomeEffectsApplied = false;
	_AreDesertBiomeEffectsApplied = false;
	_AreJungleBiomeEffectsApplied = false;

	_AreGrasslandsBiomeEffectsApplied = true;

	float BuffsMultiplier = 1.0f;
	float DebuffsMultiplier = 1.0f;
	SetEnvironmentBuffsMultipliers(BuffsMultiplier, DebuffsMultiplier);

	// Buffs
	_SightModifier += _SignificantlyChangeValue * BuffsMultiplier;;
	_ReproductiveUrgeModifier += _SignificantlyChangeValue * BuffsMultiplier;

	// Debuffs
	// None
}

void AAnimal::ApplySnowBiomeEffects()
{
	//if (_AreSnowBiomeEffectsApplied)
		//return;

	// Reset other biome effects
	ResetModifiers();

	_AreForestBiomeEffectsApplied = false;
	_AreGrasslandsBiomeEffectsApplied = false;
	_AreDesertBiomeEffectsApplied = false;
	_AreJungleBiomeEffectsApplied = false;

	_AreSnowBiomeEffectsApplied = true;

	float BuffsMultiplier = 1.0f;
	float DebuffsMultiplier = 1.0f;
	SetEnvironmentBuffsMultipliers(BuffsMultiplier, DebuffsMultiplier);

	// Buffs
	_SightModifier += _SignificantlyChangeValue * BuffsMultiplier;;
	_ThirstModifier -= _SlightlyChangeValue * BuffsMultiplier;;

	// Debuffs
	_HungerModifier += _SignificantlyChangeValue * DebuffsMultiplier;
	_SpeedModifier -= _SignificantlyChangeValue * DebuffsMultiplier;
}

void AAnimal::ApplyForestBiomeEffects()
{
	//if (_AreForestBiomeEffectsApplied)
		//return;

	// Reset other biome effects
	ResetModifiers();

	_AreSnowBiomeEffectsApplied = false;
	_AreGrasslandsBiomeEffectsApplied = false;
	_AreDesertBiomeEffectsApplied = false;
	_AreJungleBiomeEffectsApplied = false;

	_AreForestBiomeEffectsApplied = true;

	float BuffsMultiplier = 1.0f;
	float DebuffsMultiplier = 1.0f;
	SetEnvironmentBuffsMultipliers(BuffsMultiplier, DebuffsMultiplier);

	// Buffs
	_ThirstModifier -= _SlightlyChangeValue * BuffsMultiplier;
	_HungerModifier -= _SlightlyChangeValue * BuffsMultiplier;
	_ReproductiveUrgeModifier += _SlightlyChangeValue * BuffsMultiplier;

	// Debuffs
	_SightModifier -= _SlightlyChangeValue * DebuffsMultiplier;
}

void AAnimal::ResetModifiers()
{
	_SpeedModifier = 1.0f;
	_SightModifier = 1.0f;
	_HungerModifier = 1.0f;
	_ThirstModifier = 1.0f;
	_ReproductiveUrgeModifier = 1.0f;
}

void AAnimal::SetEnvironmentBuffsMultipliers(float& BuffsMultipliers, float& DebuffsMultpliers)
{
	if (GetIsInOptimalTemperature() && GetIsInOptimalHumidity())
	{
		BuffsMultipliers = 1.25f;
		DebuffsMultpliers = 0.0f;
	}
	else if (!GetIsInOptimalTemperature() && !GetIsInOptimalHumidity())
	{
		BuffsMultipliers = 0.0f;
		DebuffsMultpliers = 1.25f;
	}
	else
	{
		BuffsMultipliers = 1.0f;
		DebuffsMultpliers = 1.0f;
	}
}

#pragma endregion

#pragma region Time

void AAnimal::UpdateEnvironmentData(const float& DeltaTime)
{
	// Calculate time passed from last environment data update
	_UpdateEnvironmentDataTimer += DeltaTime;

	if (_UpdateEnvironmentDataTimer <= 0.25f)
	{
		return;
	}

	// Reset timer and execute update
	_UpdateEnvironmentDataTimer = 0.0f;

	// Rounding actor position to nearest hundreds
	const int32 PosX = static_cast<int32>(GetActorLocation().X / 100) * 100;
	const int32 PosY = static_cast<int32>(GetActorLocation().Y / 100) * 100;

	// Get information about array
	if (_TemperatureMap.Num() != _HumidiyMap.Num())
		return;
	
	const int32 ArraySize = _TemperatureMap.Num();
	const int32 Size = static_cast<int32>(FMath::Sqrt(static_cast<float>(ArraySize)));
	const int32 Center = Size / 2;

	// Inverse indexing from MapGenerator::GetTerrainData()
	const int32 x = static_cast<int32>(PosX / _WorldScale) + Center;
	const int32 y = static_cast<int32>(PosY / _WorldScale) + Center;

	// Calculate index in array
	const int32 Idx = (y * Size) + x;

	// Set Environment Data
	if (0 <= Idx && Idx < ArraySize)
	{
		SetEnvironmentTemperature(_TemperatureMap[Idx]);
		SetEnvironmentHumidity(_HumidiyMap[Idx]);

		if (GetMinTemperature() <= GetEnvironmentTemperature() && GetEnvironmentTemperature() <= GetMaxTemperature())
		{
			SetIsInOptimalTemperature(true);
		}
		else
		{
			SetIsInOptimalTemperature(false);
		}

		if (GetMinHumidity() <= GetEnvironmentHumidity() && GetEnvironmentHumidity() <= GetMaxHumidity())
		{
			SetIsInOptimalHumidity(true);
		}
		else
		{
			SetIsInOptimalHumidity(false);
		}
	}
}

void AAnimal::Grow(const float& DeltaTime)
{
	SetGrowthTimerSeconds(GetGrowthTimerSeconds() + DeltaTime);
	SetGrowthPct(GetGrowthTimerSeconds() / GetTimeToGrowSeconds() * 100.0f);


	if (GetTimeToGrowSeconds() > GetGrowthTimerSeconds())
	{
		
		return;
	}

	SetIsChild(false);
}

void AAnimal::GainHunger()
{
	const float Multipliers = GetSpeedMultiplierHT() * GetSensoryDistanceMultiplierHT() * _HungerModifier;

	SetHungerCurrent(GetHungerCurrent() + (GetHungerGainSecond() * Multipliers));
	SetHungerPct(GetHungerCurrent() / GetHungerMax() * 100.0f);

	if (GetHungerCurrent() >= GetHungerMax())
	{
		ApplyDamage(GetCurrentHealth());
	}
}

void AAnimal::GainThirst()
{
	const float Multipliers = GetSpeedMultiplierHT() * GetSensoryDistanceMultiplierHT() * _ThirstModifier;

	SetThirstCurrent(GetThirstCurrent() + (GetThirstGainSecond() * Multipliers));
	SetThirstPct(GetThirstCurrent() / GetThirstMax() * 100.0f);

	if (GetThirstCurrent() >= GetThirstMax())
	{
		ApplyDamage(GetCurrentHealth());
	}
}

void AAnimal::GainReproductiveUrge()
{
	SetReproductiveUrgeCurrent(GetReproductiveUrgeCurrent() + (GetReproductiveUrgeGainSecond() * _ReproductiveUrgeModifier));
	SetReproductiveUrgePct(GetReproductiveUrgeCurrent() / GetReproductiveUrgeMax() * 100.0f);
}

void AAnimal::ApplyEnvironmentStatuses()
{
	float TemperatureDamage = 0.0f;
	float HumidityDamage = 0.0f;

	if (!GetIsInOptimalTemperature())
	{
		float TemperatureDifference = 0.0f;

		if (GetEnvironmentTemperature() < GetMinTemperature())
		{
			TemperatureDifference = FMath::Abs(GetMinTemperature() - GetEnvironmentTemperature());
		}
		else if (GetMaxTemperature() < GetEnvironmentTemperature())
		{
			TemperatureDifference = FMath::Abs(GetEnvironmentTemperature() - GetMaxTemperature());
		}

		// Changing range from 0.X to X.X
		TemperatureDifference *= 10;

		// Calculation
		TemperatureDamage = FMath::Pow(2, TemperatureDifference);
		TemperatureDamage = FMath::Pow(TemperatureDamage, 1.0f / 3.0f) - 1.0f;

		// Apply Resistance
		TemperatureDamage -= TemperatureDamage * (GetResistance() / 100.0f);
	}

	if (!GetIsInOptimalHumidity())
	{
		float HumidityDifference = 0.0f;

		if (GetEnvironmentHumidity() < GetMinHumidity())
		{
			HumidityDifference = FMath::Abs(GetMinHumidity() - GetEnvironmentHumidity());
		}
		else if (GetMaxHumidity() < GetEnvironmentHumidity())
		{
			HumidityDifference = FMath::Abs(GetEnvironmentHumidity() - GetMaxHumidity());
		}

		// Changing range from 0.X to X.X
		HumidityDifference *= 10.0f;

		if (HumidityDifference < 1.0f)
		{
			HumidityDifference = 1.0f;
		}

		// Calculation
		HumidityDamage = FMath::Pow(2, HumidityDifference);
		HumidityDamage = FMath::Pow(HumidityDamage, 1.0f / 2.0f) - 1.0f;

		// Apply Resistance
		HumidityDamage -= HumidityDamage * (GetResistance() / 100.0f);
	}

	// Double damage if plant isn't growing in optimal Temperature and Humidity
	if (!GetIsInOptimalTemperature() && !GetIsInOptimalHumidity())
	{
		TemperatureDamage *= 2;
		HumidityDamage *= 2;
	}

	// Damage has to be positive number
	ApplyDamage(FMath::Abs(TemperatureDamage + HumidityDamage));
}

#pragma endregion

void AAnimal::ApplyDamage(const float& Damage)
{
	SetCurrentHealth(GetCurrentHealth() - Damage);

	if (GetCurrentHealth() <= 0)
	{
		Destroy();
	}
}

void AAnimal::QuickLog(const FColor Color, const FString Message) const
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color, Message);
}