// Fill out your copyright notice in the Description page of Project Settings.


#include "Animals/AnimalMale.h"

AAnimalMale::AAnimalMale()
{
	// Empty
}

void AAnimalMale::BeginPlay()
{
	Super::BeginPlay();

	SetGender(EAnimalGender::MALE);
}

// Called every frame
void AAnimalMale::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!_CanReproduce)
	{
		_ReproductionDelayTimerSeconds += DeltaTime;

		if (_ReproductionDelayTimerSeconds >= _ReproductionDelaySeconds)
		{
			_CanReproduce = true;
			_ReproductionDelayTimerSeconds = 0.0f;
		}
	}
}

void AAnimalMale::SetDesirability(const float& Desirability)
{
	_Desirability = FMath::Clamp(Desirability, 0.0f, 100.0f);
}

float AAnimalMale::GetDesirability() const
{
	return _Desirability;
}