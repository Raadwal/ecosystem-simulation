// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGeneration/NoiseGenerator.h"

// Sets default values for this component's properties
UNoiseGenerator::UNoiseGenerator()
{
	// Disabling tick - unnecessary
	PrimaryComponentTick.bCanEverTick = false;

	//Initializing arrays
	int32 ArraySize = _Size * _Size;

	_NoiseMapTerrain.Init(0.0f, _Size * _Size);
	_NoiseMapTemperature.Init(0.0f, _Size * _Size);
	_NoiseMapHumidity.Init(0.0f, _Size * _Size);
	_FalloffMask.Init(0.0f, _Size * _Size);
}


// Called when the game starts
void UNoiseGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Modified version of Sebastian Lague (Procedural Terrain Generation Series)
// https://www.youtube.com/watch?v=wbpMiKiSKm8&list=PLFt_AvWsXl0eBW2EiBtl_sxmDtSgZBxB3
void UNoiseGenerator::GenerateNoises()
{
	// Calculating arrays size
	int32 ArraysSize = _Size * _Size;

	//Check if FalloffMask is generated properly
	if (ArraysSize != _FalloffMask.Num())
		GenerateFalloffMask();

	// Variables to store min and max generated Height - needed for noise normalization
	float MinNoiseHeightTerrain = std::numeric_limits<float>::max();
	float MaxNoiseHeightTerrain = std::numeric_limits<float>::min();

	float MinNoiseHeightTemperature = std::numeric_limits<float>::max();
	float MaxNoiseHeightTemperature = std::numeric_limits<float>::min();

	float MinNoiseHeightHumidity = std::numeric_limits<float>::max();
	float MaxNoiseHeightHumidity = std::numeric_limits<float>::min();

	// Center of the noise
	float HalfWidth = _Size / 2.0f;
	float HalfHeight = _Size / 2.0f;

	// Scale is higher for Temperature and Humidity (Bigger Biomes) -> 32 minimal allowed Size of the Map
	float TemperatureScale = _Scale * _TemperatureScaleMultiplier;
	float HumidityScale = _Scale * _HumidityScaleMultiplier;

	// Initializing arrays storing noise maps
	TArray<float> NoiseMapTerrain;
	NoiseMapTerrain.Init(0.0f, ArraysSize);

	TArray<float> NoiseMapTemperature;
	NoiseMapTemperature.Init(0.0f, ArraysSize);

	TArray<float> NoiseMapHumidity;
	NoiseMapHumidity.Init(0.0f, ArraysSize);

	//Initializing Number Generation
	FRandomStream RandomNumberGeneratorTerrain(_Seed);
	FRandomStream RandomNumberGeneratorTemperature(_Seed + 1);
	FRandomStream RandomNumberGeneratorHumidity(_Seed + 2);

	// Initializing array storing offset of each octave
	TArray<FVector2D> OctaveOffestsTerrain;
	OctaveOffestsTerrain.Init(FVector2D(0, 0), _Octaves);

	TArray<FVector2D> OctaveOffestsTemperature;
	OctaveOffestsTemperature.Init(FVector2D(0, 0), _Octaves);

	TArray<FVector2D> OctaveOffestsHumidity;
	OctaveOffestsHumidity.Init(FVector2D(0, 0), _Octaves);

	// Calculating offset of each octave
	for (int32 i = 0; i < _Octaves; i++)
	{
		float OffsetXTerrain = RandomNumberGeneratorTerrain.FRandRange(-100000, 100000) + _Offset.X;
		float OffsetYTerrain = RandomNumberGeneratorTerrain.FRandRange(-100000, 100000) + _Offset.Y;

		OctaveOffestsTerrain[i] = FVector2D(OffsetXTerrain, OffsetYTerrain);

		float OffsetXTemperature = RandomNumberGeneratorTemperature.FRandRange(-100000, 100000) + _Offset.X;
		float OffsetYTemperature = RandomNumberGeneratorTemperature.FRandRange(-100000, 100000) + _Offset.Y;

		OctaveOffestsTemperature[i] = FVector2D(OffsetXTemperature, OffsetYTemperature);

		float OffsetXHumidity = RandomNumberGeneratorHumidity.FRandRange(-100000, 100000) + _Offset.X;
		float OffsetYHumidity = RandomNumberGeneratorHumidity.FRandRange(-100000, 100000) + _Offset.Y;

		OctaveOffestsHumidity[i] = FVector2D(OffsetXHumidity, OffsetYHumidity);
	}

	// Noise Generation Algorithm
	ParallelFor(ArraysSize, [&](int32 Idx)
	{
		const int32 x = Idx / _Size;
		const int32 y = Idx % _Size;
		const int32 ArrayIdx = ((y * _Size) + x);

		float Amplitude = 1;
		float Frequency = 1;
		float NoiseHeightTerrain = 0;
		float NoiseHeightTemperature = 0;
		float NoiseHeightHumidity = 0;

		for (int i = 0; i < _Octaves; i++)
		{
			const float SampleTerrainX = (x - HalfWidth) / _Scale * Frequency + OctaveOffestsTerrain[i].X;
			const float SampleTerrainY = (y - HalfHeight) / _Scale * Frequency + OctaveOffestsTerrain[i].Y;

			const float SampleTemperatureX = (x - HalfWidth) / TemperatureScale * Frequency + OctaveOffestsTemperature[i].X;
			const float SampleTemperatureY = (y - HalfHeight) / TemperatureScale * Frequency + OctaveOffestsTemperature[i].Y;

			const float SampleHumidityX = (x - HalfWidth) / HumidityScale * Frequency + OctaveOffestsHumidity[i].X;
			const float SampleHumidityY = (y - HalfHeight) / HumidityScale * Frequency + OctaveOffestsHumidity[i].Y;

			const FVector2D PerlinPositionTerrain(SampleTerrainX, SampleTerrainY);
			const FVector2D PerlinPositionTemperature(SampleTemperatureX, SampleTemperatureY);
			const FVector2D PerlinPositionHumidity(SampleHumidityX, SampleHumidityY);

			const float PerlinValueTerrain = FMath::PerlinNoise2D(PerlinPositionTerrain);
			const float PerlinValueTemperature = FMath::PerlinNoise2D(PerlinPositionTemperature);
			const float PerlinValueHumidity = FMath::PerlinNoise2D(PerlinPositionHumidity);

			NoiseHeightTerrain += PerlinValueTerrain * Amplitude;
			NoiseHeightTemperature += PerlinValueTemperature * Amplitude;
			NoiseHeightHumidity += PerlinValueHumidity * Amplitude;

			Amplitude *= _Persistance;
			Frequency *= _Lacunarity;
		}

		if (NoiseHeightTerrain > MaxNoiseHeightTerrain)
			MaxNoiseHeightTerrain = NoiseHeightTerrain;
		else if (NoiseHeightTerrain < MinNoiseHeightTerrain)
			MinNoiseHeightTerrain = NoiseHeightTerrain;

		if (NoiseHeightTemperature > MaxNoiseHeightTemperature)
			MaxNoiseHeightTemperature = NoiseHeightTemperature;
		else if (NoiseHeightTemperature < MinNoiseHeightTemperature)
			MinNoiseHeightTemperature = NoiseHeightTemperature;

		if (NoiseHeightHumidity > MaxNoiseHeightHumidity)
			MaxNoiseHeightHumidity = NoiseHeightHumidity;
		else if (NoiseHeightHumidity < MinNoiseHeightHumidity)
			MinNoiseHeightHumidity = NoiseHeightHumidity;

		NoiseMapTerrain[ArrayIdx] = NoiseHeightTerrain;
		NoiseMapTemperature[ArrayIdx] = NoiseHeightTemperature;
		NoiseMapHumidity[ArrayIdx] = NoiseHeightHumidity;
	});

	// Normalizaing generated Noise Maps
	ParallelFor(ArraysSize, [&](int32 Idx)
	{
		const int32 x = Idx / _Size;
		const int32 y = Idx % _Size;
		const int32 ArrayIdx = ((y * _Size) + x);

		NoiseMapTerrain[ArrayIdx] = FMath::GetMappedRangeValueClamped(FVector2D(MinNoiseHeightTerrain, MaxNoiseHeightTerrain), FVector2D(0, 1), NoiseMapTerrain[ArrayIdx]);
		NoiseMapTemperature[ArrayIdx] = FMath::GetMappedRangeValueClamped(FVector2D(MinNoiseHeightTemperature, MaxNoiseHeightTemperature), FVector2D(0, 1), NoiseMapTemperature[ArrayIdx]);
		NoiseMapHumidity[ArrayIdx] = FMath::GetMappedRangeValueClamped(FVector2D(MinNoiseHeightHumidity, MaxNoiseHeightHumidity), FVector2D(0, 1), NoiseMapHumidity[ArrayIdx]);

		if (_IsGeneratingIslandNoise)
			NoiseMapTerrain[ArrayIdx] = FMath::Max(0.0f, NoiseMapTerrain[ArrayIdx] - _FalloffMask[ArrayIdx]);
	});

	// Saving generated Noise Maps
	_NoiseMapTerrain = NoiseMapTerrain;
	_NoiseMapTemperature = NoiseMapTemperature;
	_NoiseMapHumidity = NoiseMapHumidity;
}

// Modified version of Sebastian Lague (Procedural Terrain Generation Series)
// https://www.youtube.com/watch?v=wbpMiKiSKm8&list=PLFt_AvWsXl0eBW2EiBtl_sxmDtSgZBxB3
void UNoiseGenerator::GenerateFalloffMask()
{
	// Calculating arrays size
	const int32 ArraySize = _Size * _Size;

	// Initializing array storing FalloffMask
	TArray<float> FalloffMask;
	FalloffMask.Init(0.0f, ArraySize);

	// Function arguments (Island Size)
	const float A = 3.0f; // 3.0f => 1 is MAX
	const float B = 6.0f; // Higher value => More black

	//Square Mask
	ParallelFor(ArraySize, [&](int32 Idx)
	{
		const int32 x = Idx / _Size;
		const int32 y = Idx % _Size;
		const int32 ArrayIdx = ((y * _Size) + x);

		const float XValue = static_cast<float>(x) / static_cast<float>(_Size) * 2.0f - 1.0f;
		const float YValue = static_cast<float>(y) / static_cast<float>(_Size) * 2.0f - 1.0f;

		const float Gradient = FMath::Max(FMath::Abs(XValue), FMath::Abs(YValue));
		// Value is always from range <0; 1>
		FalloffMask[ArrayIdx] = FMath::Pow(Gradient, A) / (FMath::Pow(Gradient, A) + FMath::Pow(B - B * Gradient, A));
	});

	_FalloffMask = FalloffMask;
}

void UNoiseGenerator::SetSize(const int32& Size)
{
	_Size = Size;

	// Generate Always after map size change;
	GenerateFalloffMask();
}

int32 UNoiseGenerator::GetSize() const
{
	return _Size;
}
void UNoiseGenerator::SetSeed(const int32& Seed)
{
	_Seed = Seed;
}

int32 UNoiseGenerator::GetSeed() const
{
	return _Seed;
}

void UNoiseGenerator::SetOffset(const FVector2D& Offset)
{
	_Offset = Offset;
}

FVector2D UNoiseGenerator::GetOffset() const
{
	return _Offset;
}

void UNoiseGenerator::SetScale(const float& Scale)
{

	_Scale = Scale;
}

float UNoiseGenerator::GetScale() const
{
	return _Scale;
}

void UNoiseGenerator::SetOctaves(const int32& Octaves)
{
	_Octaves = Octaves;
}

int32 UNoiseGenerator::GetOctaves() const
{
	return _Octaves;
}

void UNoiseGenerator::SetPersistance(const float& Persistance)
{
	_Persistance = Persistance;
}

float UNoiseGenerator::GetPersistance() const
{
	return _Persistance;
}

void UNoiseGenerator::SetLacunarity(const float& Lacunarity)
{
	_Lacunarity = Lacunarity;
}

float UNoiseGenerator::GetLacunarity() const
{
	return _Lacunarity;
}

void UNoiseGenerator::SetIsGeneratingIslandNoise(const bool& IsGeneratingIslandNoise)
{
	_IsGeneratingIslandNoise = IsGeneratingIslandNoise;
}

bool UNoiseGenerator::GetIsGeneratingIslandNoise()
{
	return _IsGeneratingIslandNoise;
}

TArray<float> UNoiseGenerator::GetNoiseMapTerrain() const
{
	return _NoiseMapTerrain;
}

TArray<float> UNoiseGenerator::GetNoiseMapTemperature() const
{
	return _NoiseMapTemperature;
}

TArray<float> UNoiseGenerator::getNoiseMapHumidity() const
{
	return _NoiseMapHumidity;
}