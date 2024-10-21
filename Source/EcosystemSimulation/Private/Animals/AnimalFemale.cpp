// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/AnimalFemale.h"

AAnimalFemale::AAnimalFemale()
{
	// Empty
}

void AAnimalFemale::BeginPlay()
{
	Super::BeginPlay();

	SetGender(EAnimalGender::FEMALE);
}

// Called every frame
void AAnimalFemale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_IsPregnant)
	{
		_PregnancyTimerSeconds += DeltaTime;
		SetPregnancyPct(_PregnancyTimerSeconds / _PregnancyLengthSeconds * 100.0f);


		if (_PregnancyTimerSeconds >= _PregnancyLengthSeconds)
		{
			SpawnOffsprings();

			_IsPregnant = false;
			_PregnancyTimerSeconds = 0.0f;
			SetPregnancyPct(0.0f);
		}
	}
}

void AAnimalFemale::SpawnOffsprings()
{
	int32 OffspringQuantity = FMath::RandRange(1, _MaxOffspringsQuantity);

	for (int32 i = 0; i < OffspringQuantity; i++)
	{
		AAnimal* SpawnedAncestor = nullptr;
		int32 AttemptsCount = 0;

		do
		{
			FVector SpawnLocation = GetActorLocation() + CreateLocationOffset();
			FRotator SpawnRotation = GetActorRotation();

			bool _IsMale = FMath::RandBool();

			if (_IsMale)
			{
				SpawnedAncestor = GetWorld()->SpawnActor<AAnimal>(_SelfMale, SpawnLocation, SpawnRotation);
			}

			if (!_IsMale)
			{
				SpawnedAncestor = GetWorld()->SpawnActor<AAnimal>(_SelfFemale, SpawnLocation, SpawnRotation);
			}

			AttemptsCount++;
		} while (!SpawnedAncestor && AttemptsCount < 5);

		if (SpawnedAncestor)
		{
			AncestorSetup(SpawnedAncestor);
		}
	}
}

void AAnimalFemale::AncestorSetup(AAnimal* const Ancestor)
{
	// Copy parents traits to its ancestor
	// It's also a list which traits can mutate!
	
	int32 TraitsQuantity = 21;
	int32 TraitsFromOneParentQuantity = static_cast<int32>(TraitsQuantity / 2) + 1;

	// Which traits is from which parent
	int32 TraitsFromFatherCount = 0;
	int32 TraitsFromMotherCount = 0;
	
	// Parents values
	TArray<float> FatherTraitsValues;
	FatherTraitsValues.Init(0.0f, TraitsQuantity);

	TArray<float> MotherTraitsValues;
	MotherTraitsValues.Init(0.0f, TraitsQuantity);

	FatherTraitsValues[0] = _FatherTraits.SmallMutationChance;
	MotherTraitsValues[0] = GetSmallMutationChance();

	FatherTraitsValues[1] = _FatherTraits.MediumMutationChance;
	MotherTraitsValues[1] = GetMediumMutationChance();

	FatherTraitsValues[2] = _FatherTraits.LargeMutationChance;
	MotherTraitsValues[2] = GetLargeMutationChance();

	FatherTraitsValues[3] = _FatherTraits.TimeToGrowSeconds;
	MotherTraitsValues[3] = GetTimeToGrowSeconds();

	FatherTraitsValues[4] = _FatherTraits.Attack;
	MotherTraitsValues[4] = GetAttack();

	FatherTraitsValues[5] = _FatherTraits.InitialHealth;
	MotherTraitsValues[5] = GetInitialHealth();

	FatherTraitsValues[6] = _FatherTraits.HungerMax;
	MotherTraitsValues[6] = GetHungerMax();

	FatherTraitsValues[7] = _FatherTraits.HungerGainSecond;
	MotherTraitsValues[7] = GetHungerGainSecond();

	FatherTraitsValues[8] = _FatherTraits.ThirstMax;
	MotherTraitsValues[8] = GetThirstMax();

	FatherTraitsValues[9] = _FatherTraits.ThirstGainSecond;
	MotherTraitsValues[9] = GetThirstGainSecond();

	FatherTraitsValues[10] = _FatherTraits.ReproductiveUrgeMax;
	MotherTraitsValues[10] = GetReproductiveUrgeMax();

	FatherTraitsValues[11] = _FatherTraits.ReproductiveUrgeGainSecond;
	MotherTraitsValues[11] = GetReproductiveUrgeGainSecond();

	FatherTraitsValues[12] = _FatherTraits.CurrentSpeed;
	MotherTraitsValues[12] = GetCurrentSpeed();

	FatherTraitsValues[13] = _FatherTraits.CurrentSensoryDistance;
	MotherTraitsValues[13] = GetCurrentSensoryDistance();

	FatherTraitsValues[14] = _FatherTraits.Resistance;
	MotherTraitsValues[14] = GetResistance();

	FatherTraitsValues[15] = _FatherTraits.Nutrients;
	MotherTraitsValues[15] = GetNutrients();

	FatherTraitsValues[16] = _FatherTraits.EnvironmentStatusesAppliementSeconds;
	MotherTraitsValues[16] = GetEnvironmentStatusesAppliementSeconds();

	FatherTraitsValues[17] = _FatherTraits.MinHumidity;
	MotherTraitsValues[17] = GetMinHumidity();

	FatherTraitsValues[18] = _FatherTraits.MaxHumidity;
	MotherTraitsValues[18] = GetMaxHumidity();

	FatherTraitsValues[19] = _FatherTraits.MinTemperature;
	MotherTraitsValues[19] = GetMinTemperature();

	FatherTraitsValues[20] = _FatherTraits.MaxTemperature;
	MotherTraitsValues[20] = GetMaxTemperature();

	// List of function connected with mutable traits
	TArray<TFunction<void(const float&)>> TraitFunctionSettersArray;
	// Number of mutable traits
	TraitFunctionSettersArray.Init(nullptr, 21);

	TraitFunctionSettersArray[0] = [=](const float& value) {
		Ancestor->SetSmallMutationChance(value);
	};

	TraitFunctionSettersArray[1] = [=](const float& value) {
		Ancestor->SetMediumMutationChance(value);
	};

	TraitFunctionSettersArray[2] = [=](const float& value) {
		Ancestor->SetLargeMutationChance(value);
	};

	// Growth
	TraitFunctionSettersArray[3] = [=](const float& value) {
		Ancestor->SetTimeToGrowSeconds(value);
	};

	// Tratits
	TraitFunctionSettersArray[4] = [=](const float& value) {
		Ancestor->SetAttack(value);
	};

	TraitFunctionSettersArray[5] = [=](const float& value) {
		Ancestor->SetInitialHealth(value);
		Ancestor->SetCurrentHealth(value);
	};

	TraitFunctionSettersArray[6] = [=](const float& value) {
		Ancestor->SetHungerMax(value);
	};

	TraitFunctionSettersArray[7] = [=](const float& value) {
		Ancestor->SetHungerGainSecond(value);
	};

	TraitFunctionSettersArray[8] = [=](const float& value) {
		Ancestor->SetThirstMax(value);
	};

	TraitFunctionSettersArray[9] = [=](const float& value) {
		Ancestor->SetThirstGainSecond(value);
	};

	TraitFunctionSettersArray[10] = [=](const float& value) {
		Ancestor->SetReproductiveUrgeMax(value);
	};

	TraitFunctionSettersArray[11] = [=](const float& value) {
		Ancestor->SetReproductiveUrgeGainSecond(value);
	};

	TraitFunctionSettersArray[12] = [=](const float& value) {
		Ancestor->SetCurrentSpeed(value);
	};

	TraitFunctionSettersArray[13] = [=](const float& value) {
		Ancestor->SetCurrentSensoryDistance(value);
	};

	TraitFunctionSettersArray[14] = [=](const float& value) {
		Ancestor->SetResistance(value);
	};

	TraitFunctionSettersArray[15] = [=](const float& value) {
		Ancestor->SetNutrients(value);
	};

	// Environment
	TraitFunctionSettersArray[16] = [=](const float& value) {
		Ancestor->SetEnvironmentStatusesAppliementSeconds(value);
	};

	TraitFunctionSettersArray[17] = [=](const float& value) {
		Ancestor->SetMinHumidity(value);
	};

	TraitFunctionSettersArray[18] = [=](const float& value) {
		Ancestor->SetMaxHumidity(value);
	};

	TraitFunctionSettersArray[19] = [=](const float& value) {
		Ancestor->SetMinTemperature(value);
	};

	TraitFunctionSettersArray[20] = [=](const float& value) {
		Ancestor->SetMaxTemperature(value);
	};

	// Choosing which parent's trait will be used
	Ancestor->SetMutationsCount(GetMutationsCount() + _FatherTraits.MutationsCount);

	for (int32 i = 0; i < TraitsQuantity; i++)
	{
		bool FatherTrait = FMath::RandBool();

		if (FatherTrait && TraitsFromFatherCount < TraitsFromOneParentQuantity)
		{
			TraitFunctionSettersArray[i](FatherTraitsValues[i]);
			TraitsFromFatherCount++;
		}
		else if (!FatherTrait && TraitsFromMotherCount < TraitsFromOneParentQuantity)
		{
			TraitFunctionSettersArray[i](MotherTraitsValues[i]);
			TraitsFromMotherCount++;
		}
		else
		{
			TraitFunctionSettersArray[i](FatherTraitsValues[i]);
			TraitsFromFatherCount++;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Mother %d, Father %d"), TraitsFromFatherCount, TraitsFromMotherCount);

	float RandomNumber = 0.0f;
	RandomNumber = FMath::FRandRange(0.0f, 100.0f);

	if (RandomNumber <= GetLargeMutationChance())
	{
		ApplyMutation(Ancestor, GetLargeMutationChangeMin(), GetLargeMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetMediumMutationChance())
	{
		ApplyMutation(Ancestor, GetMediumMutationChangeMin(), GetMediumMutationChangeMax());
		return;
	}

	RandomNumber = FMath::FRandRange(0.0f, 100.0f);
	if (RandomNumber <= GetSmallMutationChance())
	{
		ApplyMutation(Ancestor, GetSmallMutationChangeMin(), GetSmallMutationChangeMax());
		return;
	}
}

bool AAnimalFemale::SetPregnancy(AAnimalMale* const Father)
{
	if (_IsPregnant)
	{
		return false;
	}

	_FatherTraits = FFatherTraits();

	_FatherTraits.SmallMutationChance = Father->GetSmallMutationChance();
	_FatherTraits.MediumMutationChance = Father->GetMediumMutationChance();
	_FatherTraits.LargeMutationChance = Father->GetLargeMutationChance();

	_FatherTraits.TimeToGrowSeconds = Father->GetTimeToGrowSeconds();

	_FatherTraits.Attack = Father->GetAttack();
	_FatherTraits.InitialHealth = Father->GetInitialHealth();

	_FatherTraits.HungerMax = Father->GetHungerMax();
	_FatherTraits.HungerGainSecond = Father->GetHungerGainSecond();

	_FatherTraits.ThirstMax = Father->GetThirstMax();
	_FatherTraits.ThirstGainSecond = Father->GetThirstGainSecond();

	_FatherTraits.ReproductiveUrgeMax = Father->GetReproductiveUrgeMax();
	_FatherTraits.ReproductiveUrgeGainSecond = Father->GetReproductiveUrgeGainSecond();

	_FatherTraits.CurrentSpeed = Father->GetCurrentSpeed();
	_FatherTraits.CurrentSensoryDistance = Father->GetCurrentSensoryDistance();

	_FatherTraits.Resistance = Father->GetResistance();
	_FatherTraits.Nutrients = Father->GetNutrients();

	_FatherTraits.MinHumidity = Father->GetMinHumidity();
	_FatherTraits.MaxHumidity = Father->GetMaxHumidity();
	_FatherTraits.MinTemperature = Father->GetMinTemperature();
	_FatherTraits.MaxTemperature = Father->GetMaxTemperature();
	_FatherTraits.MutationsCount = Father->GetMutationsCount();

	_IsPregnant = true;
	Father->SetReproductiveUrgeCurrent(0);
	SetReproductiveUrgeCurrent(0);

	return true;
}

void AAnimalFemale::ApplyMutation(AAnimal* const Ancestor, const float& MinChange, const float& MaxChange)
{
	Ancestor->SetMutationsCount(Ancestor->GetMutationsCount() + 1);

	// List of function connected with mutable traits
	TArray<TFunction<void(const float&)>> TraitFunctionSettersArray;
	// Number of mutable traits
	TraitFunctionSettersArray.Init(nullptr, 21);

	// Mutations
	TraitFunctionSettersArray[0] = [=](const float& value) {
		Ancestor->SetSmallMutationChance(Ancestor->GetSmallMutationChance() * value);
	};

	TraitFunctionSettersArray[1] = [=](const float& value) {
		Ancestor->SetMediumMutationChance(Ancestor->GetMediumMutationChance() * value);
	};

	TraitFunctionSettersArray[2] = [=](const float& value) {
		Ancestor->SetLargeMutationChance(Ancestor->GetLargeMutationChance() * value);
	};

	// Growth
	TraitFunctionSettersArray[3] = [=](const float& value) {
		Ancestor->SetTimeToGrowSeconds(Ancestor->GetTimeToGrowSeconds() * value);
	};

	// Tratits
	TraitFunctionSettersArray[4] = [=](const float& value) {
		Ancestor->SetAttack(Ancestor->GetAttack() * value);
	};

	TraitFunctionSettersArray[5] = [=](const float& value) {
		Ancestor->SetInitialHealth(Ancestor->GetInitialHealth() * value);
	};

	TraitFunctionSettersArray[6] = [=](const float& value) {
		Ancestor->SetHungerMax(Ancestor->GetHungerMax() * value);
	};

	TraitFunctionSettersArray[7] = [=](const float& value) {
		Ancestor->SetHungerGainSecond(Ancestor->GetHungerGainSecond() * value);
	};

	TraitFunctionSettersArray[8] = [=](const float& value) {
		Ancestor->SetThirstMax(Ancestor->GetThirstMax() * value);
	};

	TraitFunctionSettersArray[9] = [=](const float& value) {
		Ancestor->SetThirstGainSecond(Ancestor->GetThirstGainSecond() * value);
	};

	TraitFunctionSettersArray[10] = [=](const float& value) {
		Ancestor->SetReproductiveUrgeMax(Ancestor->GetReproductiveUrgeMax() * value);
	};

	TraitFunctionSettersArray[11] = [=](const float& value) {
		Ancestor->SetReproductiveUrgeGainSecond(Ancestor->GetReproductiveUrgeGainSecond() * value);
	};

	TraitFunctionSettersArray[12] = [=](const float& value) {
		Ancestor->SetCurrentSpeed(Ancestor->GetCurrentSpeed() * value);
	};

	TraitFunctionSettersArray[13] = [=](const float& value) {
		Ancestor->SetCurrentSensoryDistance(Ancestor->GetCurrentSensoryDistance() * value);
	};

	TraitFunctionSettersArray[14] = [=](const float& value) {
		Ancestor->SetResistance(Ancestor->GetResistance() * value);
	};

	TraitFunctionSettersArray[15] = [=](const float& value) {
		Ancestor->SetNutrients(Ancestor->GetNutrients() * value);
	};

	// Environment
	TraitFunctionSettersArray[16] = [=](const float& value) {
		Ancestor->SetEnvironmentStatusesAppliementSeconds(Ancestor->GetEnvironmentStatusesAppliementSeconds() * value);
	};

	TraitFunctionSettersArray[17] = [=](const float& value) {
		Ancestor->SetMinHumidity(Ancestor->GetMinHumidity() * value);
	};

	TraitFunctionSettersArray[18] = [=](const float& value) {
		Ancestor->SetMaxHumidity(Ancestor->GetMaxHumidity() * value);
	};

	TraitFunctionSettersArray[19] = [=](const float& value) {
		Ancestor->SetMinTemperature(Ancestor->GetMinTemperature() * value);
	};

	TraitFunctionSettersArray[20] = [=](const float& value) {
		Ancestor->SetMaxTemperature(Ancestor->GetMaxTemperature() * value);
	};

	// Trait draw, which will be mutated
	const float RandomIndex = FMath::RandRange(0, TraitFunctionSettersArray.Num() - 1);
	const float RandomValue = FMath::FRandRange(MinChange, MaxChange);
	int32 RandomSign = 0;

	while (RandomSign == 0)
	{
		RandomSign = FMath::RandRange(-1, 1);
	}

	TraitFunctionSettersArray[RandomIndex](((RandomSign* RandomValue) + 100.0f) / 100.0f);
}

FVector AAnimalFemale::CreateLocationOffset()
{
	int32 TopDown = 0;
	int32 RightLeft = 0;

	// Ancestor can't spawn at the parent spot
	while (TopDown == 0 && RightLeft == 0)
	{
		// negative = Down, positive = Top, 0 = No Change
		TopDown = FMath::RandRange(-2, 2);
		// negative = Left, 1 = positive, 0 = No Change
		RightLeft = FMath::RandRange(-2, 2);
	}

	return FVector(TopDown * 100, RightLeft * 100, 0);
}

void AAnimalFemale::SetMaxOffspringsQuantity(const int32& MaxOffspringsQuantity)
{
	_MaxOffspringsQuantity = FMath::Max(1, MaxOffspringsQuantity);
}

int32 AAnimalFemale::GetMaxOffspringsQuantity() const
{
	return _MaxOffspringsQuantity;
}

void AAnimalFemale::SetPregnancyLengthSeconds(const float& PregnancyLengthSeconds)
{
	_PregnancyLengthSeconds = FMath::Max(0.0f, PregnancyLengthSeconds);
}

float AAnimalFemale::GetPregnancyLengthSeconds() const
{
	return _PregnancyLengthSeconds;
}

void AAnimalFemale::SetPregnancyPct(const float& PregnancyPct)
{
	_PregnancyPct = FMath::Clamp(PregnancyPct, 0.0f, 100.0f);
}

float AAnimalFemale::GetPregnancyPct() const
{
	return _PregnancyPct;
}

void AAnimalFemale::SetIsPregnant(const bool& IsPregnant)
{
	_IsPregnant = IsPregnant;
}

bool AAnimalFemale::GetIsPregnant() const
{
	return _IsPregnant;
}