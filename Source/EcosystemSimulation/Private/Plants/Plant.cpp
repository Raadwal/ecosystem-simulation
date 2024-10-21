// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants/Plant.h"

// Sets default values
APlant::APlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating defaul scene component
	_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(_SceneComponent);

	// Create Static Mesh Component
	_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_StaticMeshComponent->AttachToComponent(_SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Changing properties of the Static Mesh Component
	_StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	_StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	_StaticMeshComponent->SetGenerateOverlapEvents(false);

	// Create Collision Mesh Component
	_CollisionMeshComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	_CollisionMeshComponent->AttachToComponent(_SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Changing propertied of Collision Mesh Component
	_CollisionMeshComponent->SetMobility(EComponentMobility::Movable);
	_CollisionMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	_CollisionMeshComponent->SetGenerateOverlapEvents(true);

	// CPU usage optimatization
	SetTimeSinceEnvironmentEffectAppliement(FMath::FRandRange(0.0f, 1.0f));
}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();

	// Set Current Health
	SetCurrentHealth(GetInitialHealth());

	SetCurrentHealthLose(GetInitialHealthLose());
}

// Called every frame
void APlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TakeEnviromentDamage(DeltaTime);

	if (GetPlantStatus()  == EPlantStatus::GROWING)
	{
		Grow(DeltaTime);
	}
	else if (GetPlantStatus() == EPlantStatus::REPRODUCING)
	{
		Reproduce(DeltaTime);
	}
}

void APlant::SetEnvironmentData(const TArray<FTerrainData>& TerrainData)
{
	const int32 Idx = GetIndexFromTerrainData(TerrainData);

	// Set environmet data
	if(0 <= Idx && Idx < TerrainData.Num())
	{
		SetEnvironmentTemperature(TerrainData[Idx].Temperature);
		SetEnvironmentHumidity(TerrainData[Idx].Humidity);

		if (GetMinTemperature() <= GetEnvironmentTemperature() && GetEnvironmentTemperature() <= GetMaxTemperature())
		{
			SetIsInOptimalTemperature(true);
		}

		if (GetMinHumidity() <= GetEnvironmentHumidity() && GetEnvironmentHumidity() <= GetMaxHumidity())
		{
			SetIsInOptimalHumidity(true);
		}

		// Setting bonuses for optimal temperature
		if (GetIsInOptimalTemperature())
		{
			const float Center = (GetMinTemperature() + GetMaxTemperature()) / 2.0f;
			const float OptimalScale = FMath::Abs(Center - GetEnvironmentTemperature());
			SetEnvironmentMultiplier(GetEnvironmentMultiplier() * 1.25 - FMath::Clamp(OptimalScale, 0.0f, 0.25f));
		}

		// Setting bonuses for optimal humidity
		if (GetIsInOptimalTemperature())
		{
			const float Center = (GetMinHumidity() + GetMaxHumidity()) / 2.0f;
			const float OptimalScale = FMath::Abs(Center - GetEnvironmentHumidity());
			SetEnvironmentMultiplier(GetEnvironmentMultiplier() * 1.25 - FMath::Clamp(OptimalScale, 0.0f, 0.25f));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Plant couldn't get environment data -> Wrong Index: %d, Terrain Array Size: %d"), Idx, TerrainData.Num());
	}
}

void APlant::Grow(const float& DeltaTime)
{
	SetTimeSinceStartedGrowingSeconds(GetTimeSinceStartedGrowingSeconds() + (DeltaTime * _EnvironmentMultiplier));
	SetGrowPct(GetTimeSinceStartedGrowingSeconds() / GetTimeToGrowSeconds() * 100.0f);

	if (GetTimeToGrowSeconds() <= GetTimeSinceStartedGrowingSeconds())
	{
		SetPlantStatus(EPlantStatus::REPRODUCING);
	}
}


void APlant::Reproduce(const float& DeltaTime)
{
	SetTimeSinceStartedReproductionAttemptSeconds(GetTimeSinceStartedReproductionAttemptSeconds() + DeltaTime);
	SetReproductionPct(GetTimeSinceStartedReproductionAttemptSeconds() / GetTimeToReproductionAttemptSeconds() * 100.0f);

	if (GetTimeToReproductionAttemptSeconds() <= GetTimeSinceStartedReproductionAttemptSeconds())
	{
		TryToReproduce();
		TryToMutate();
		ApplyDamage(GetCurrentHealthLose());
		SetCurrentHealthLose(GetCurrentHealthLose() * GetHealthLoseMultiplier());

		SetTimeSinceStartedReproductionAttemptSeconds(0.0f);
	}
}

void APlant::TakeEnviromentDamage(const float& DeltaTime)
{
	// Update time since last environment effect appliement
	SetTimeSinceEnvironmentEffectAppliement(GetTimeSinceEnvironmentEffectAppliement() + DeltaTime);

	// If time since last environment effect appliement is lower than time since each appliement than exit from function
	if (GetTimeSinceEnvironmentEffectAppliement() < GetTimeToApplyEnvironmentEffectsSeconds())
		return;

	// Reset time since last environment effect appliement
	SetTimeSinceEnvironmentEffectAppliement(0.0f);

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
		HumidityDamage = FMath::Pow(HumidityDamage, 1.0f / 3.0f) - 1.0f;

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

void APlant::TryToReproduce()
{
	if(FMath::FRandRange(0.0f, 100.0f) <= FMath::Clamp(GetReproductionChancePct() * FMath::Sqrt(GetEnvironmentMultiplier()), 0.0f, 100.0f))
	{
		FVector SpawnLocation = GetActorLocation() + CreateLocationOffset();
		FRotator SpawnRotation = GetActorRotation();
	
		APlant* SpawnedAncestor = GetWorld()->SpawnActor<APlant>(_Self, SpawnLocation, SpawnRotation);
		
		if (SpawnedAncestor)
		{
			AncestorSetup(SpawnedAncestor);
		}
	}
}

void APlant::TryToMutate()
{
	float RandomNumber = 0.0f;

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetLargeMutationChanceSelf())
	{
		ApplyMutation(this, GetLargeMutationChangeMin(), GetLargeMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetMediumMutationChanceSelf())
	{
		ApplyMutation(this, GetMediumMutationChangeMin(), GetMediumMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetSmallMutationChanceSelf())
	{
		ApplyMutation(this, GetSmallMutationChangeMin(), GetSmallMutationChangeMax());
		return;
	}
}

void APlant::AncestorSetup(APlant* const Ancestor)
{
	// Copy parent's traits to its ancestor
	// It's also a list which traits can mutate!

	// Traits connected with mutations
	Ancestor->SetSmallMutationChanceSelf(GetSmallMutationChanceSelf());
	Ancestor->SetMediumMutationChanceSelf(GetMediumMutationChanceSelf());
	Ancestor->SetLargeMutationChanceSelf(GetLargeMutationChanceSelf());

	Ancestor->SetSmallMutationChanceAncestor(GetSmallMutationChanceAncestor());
	Ancestor->SetMediumMutationChanceAncestor(GetMediumMutationChanceAncestor());
	Ancestor->SetLargeMutationChanceAncestor(GetLargeMutationChanceAncestor());

	Ancestor->SetMutationsCount(GetMutationsCount());
	// Traits connected with growth
	Ancestor->SetTimeToGrowSeconds(GetTimeToGrowSeconds());
	Ancestor->SetTimeToReproductionAttemptSeconds(GetTimeToReproductionAttemptSeconds());

	// Traits connected with statistics
	Ancestor->SetInitialHealth(GetInitialHealth());
	Ancestor->SetCurrentHealth(Ancestor->GetInitialHealth());
	Ancestor->SetInitialHealthLose(GetInitialHealthLose());
	Ancestor->SetHealthLoseMultiplier(GetHealthLoseMultiplier());
	Ancestor->SetResistance(GetResistance());
	Ancestor->SetReproductionChancePct(GetReproductionChancePct());
	Ancestor->SetReproductionRange(GetReproductionRange());
	Ancestor->SetNutrients(GetNutrients());

	// Traits connected with environment
	Ancestor->SetTimeToApplyEnvironmentEffectsSeconds(GetTimeToApplyEnvironmentEffectsSeconds());
	Ancestor->SetMinTemperature(GetMinTemperature());
	Ancestor->SetMaxTemperature(GetMaxTemperature());
	Ancestor->SetMinHumidity(GetMinHumidity());
	Ancestor->SetMaxHumidity(GetMaxHumidity());

	float RandomNumber = 0.0f;

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetLargeMutationChanceAncestor())
	{
		ApplyMutation(Ancestor, GetLargeMutationChangeMin(), GetLargeMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetMediumMutationChanceAncestor())
	{
		ApplyMutation(Ancestor, GetMediumMutationChangeMin(), GetMediumMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetSmallMutationChanceAncestor())
	{
		ApplyMutation(Ancestor, GetSmallMutationChangeMin(), GetSmallMutationChangeMax());
		return;
	}
}

void APlant::ApplyMutation(APlant* const Plant, const float& MinChange, const float& MaxChange)
{
	Plant->SetMutationsCount(GetMutationsCount() + 1);

	// List of function connected with mutable traits
	TArray<TFunction<void(const float&)>> TraitFunctionSettersArray;
	// Number of mutable traits
	TraitFunctionSettersArray.Init(nullptr, 20);

	// Traits connected with mutations
	TraitFunctionSettersArray[0] = [=](const float& value) {
		Plant->SetSmallMutationChanceSelf(GetSmallMutationChanceSelf() * value);
	};

	TraitFunctionSettersArray[1] = [=](const float& value) {
		Plant->SetMediumMutationChanceSelf(GetMediumMutationChanceSelf() * value);
	};

	TraitFunctionSettersArray[2] = [=](const float& value) {
		Plant->SetLargeMutationChanceSelf(GetLargeMutationChanceSelf() * value);
	};

	TraitFunctionSettersArray[3] = [=](const float& value) {
		Plant->SetSmallMutationChanceAncestor(GetSmallMutationChanceAncestor() * value);
	};

	TraitFunctionSettersArray[4] = [=](const float& value) {
		Plant->SetMediumMutationChanceAncestor(GetMediumMutationChanceAncestor() * value);
	};

	TraitFunctionSettersArray[5] = [=](const float& value) {
		Plant->SetLargeMutationChanceAncestor(GetLargeMutationChanceAncestor() * value);
	};

	// Traits connected with growth
	TraitFunctionSettersArray[6] = [=](const float& value) {
		Plant->SetTimeToGrowSeconds(GetTimeToGrowSeconds() * value);
	};

	TraitFunctionSettersArray[7] = [=](const float& value) {
		Plant->SetTimeToReproductionAttemptSeconds(GetTimeToReproductionAttemptSeconds() * value);
	};

	// Traits connected with statistics
	TraitFunctionSettersArray[8] = [=](const float& value) {
		Plant->SetInitialHealth(GetInitialHealth() * value);
		Plant->SetCurrentHealth(Plant->GetInitialHealth());
	};

	TraitFunctionSettersArray[9] = [=](const float& value) {
		Plant->SetInitialHealthLose(GetInitialHealthLose() * value);
	};

	TraitFunctionSettersArray[10] = [=](const float& value) {
		Plant->SetHealthLoseMultiplier(GetHealthLoseMultiplier() * value);
	};

	TraitFunctionSettersArray[11] = [=](const float& value) {
		Plant->SetResistance(GetResistance() * value);
	};

	TraitFunctionSettersArray[12] = [=](const float& value) {
		Plant->SetReproductionChancePct(GetReproductionChancePct() * value);
	};

	TraitFunctionSettersArray[13] = [=](const float& value) {
		Plant->SetReproductionRange(FGenericPlatformMath::RoundToInt(GetReproductionRange() * value));
	};

	TraitFunctionSettersArray[14] = [=](const float& value) {
		Plant->SetNutrients(GetNutrients() * value);
	};

	// Traits connected with environment
	TraitFunctionSettersArray[15] = [=](const float& value) {
		Plant->SetTimeToApplyEnvironmentEffectsSeconds(GetTimeToApplyEnvironmentEffectsSeconds() * value);
	};

	TraitFunctionSettersArray[16] = [=](const float& value) {
		Plant->SetMinTemperature(GetMinTemperature() * value);
	};

	TraitFunctionSettersArray[17] = [=](const float& value) {
		Plant->SetMaxTemperature(GetMaxTemperature() * value);
	};

	TraitFunctionSettersArray[18] = [=](const float& value) {
		Plant->SetMinHumidity(GetMinHumidity() * value);
	};

	TraitFunctionSettersArray[19] = [=](const float& value) {
		Plant->SetMaxHumidity(GetMaxHumidity() * value);
	};

	// Trait draw, which will be mutated
	const float RandomIndex = FMath::RandRange(0, TraitFunctionSettersArray.Num() - 1);
	const float RandomValue = FMath::FRandRange(MinChange, MaxChange);
	int32 RandomSign = 0;

	while (RandomSign == 0)
	{ 
		RandomSign = FMath::RandRange(-1, 1);
	}

	TraitFunctionSettersArray[RandomIndex](((RandomSign * RandomValue) + 100.0f) / 100.0f);
}


FVector APlant::CreateLocationOffset()
{
	int32 TopDown = 0;
	int32 RightLeft = 0;

	// Ancestor can't spawn at the parent spot
	while(TopDown == 0 && RightLeft == 0)
	{
		// negative = Down, positive = Top, 0 = No Change
		TopDown = FMath::RandRange(-GetReproductionRange(), GetReproductionRange());
		// negative = Left, 1 = positive, 0 = No Change
		RightLeft = FMath::RandRange(-GetReproductionRange(), GetReproductionRange());
	}

	return FVector(TopDown * _WorldScale, RightLeft * _WorldScale, 0);
}


void APlant::ApplyDamage(const float& Damage)
{
	SetCurrentHealth(GetCurrentHealth() - Damage);

	if (GetCurrentHealth() <= 0.0f)
	{
		Destroy();
	}
}

bool APlant::CheckIfAboveGivenTerrainHeight(const TArray<FTerrainData>& TerrainData, const float BeachLevelEnds) const
{
	const int32 Idx = GetIndexFromTerrainData(TerrainData);

	// Prevent from Index Out of Range during Testing
	if (Idx < 0 || TerrainData.Num() <= Idx)
	{
		return true;
	}

	if (TerrainData[Idx].Height <= BeachLevelEnds)
	{
		return false;
	}

	return true;
}

int32 APlant::GetIndexFromTerrainData(const TArray<FTerrainData>& TerrainData) const
{
	// Get information about array
	const int32 ArraySize = TerrainData.Num();
	const int32 Size = static_cast<int32>(FMath::Sqrt(static_cast<float>(ArraySize)));
	const int32 Center = Size / 2;

	// Get plant position:
	const float PosX = GetActorLocation().X;
	const float PosY = GetActorLocation().Y;

	// Inverse indexing from MapGenerator::GetTerrainData()
	const int32 x = static_cast<int32>(PosX / _WorldScale) + Center;
	const int32 y = static_cast<int32>(PosY / _WorldScale) + Center;

	// Calculate index in array
	const int32 Idx = (y * Size) + x;

	return Idx;
}
