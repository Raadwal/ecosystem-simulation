// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGeneration/MapGenerator.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
	// Disabling tick - unnecessary
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

UTexture2D* AMapGenerator::GenerateMapTexture() const
{
	// Noises have to be generated in order to create proper texture
	_NoiseGenerator->GenerateNoises();

	// Calculating ArraySize
	const int32 Size = _NoiseGenerator->GetSize();
	const int32 ArraySize = Size * Size;
	
	// Creating texture and locking bulk data.
	UTexture2D* NewTexture = UTexture2D::CreateTransient(Size, Size, PF_B8G8R8A8);
	uint8* MipData = static_cast<uint8*>(NewTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
	

	// Parallel For Loop Preparation
	const TArray<float> NoiseMapTerrain = _NoiseGenerator->GetNoiseMapTerrain();
	const TArray<float> NoiseMapTemperature = _NoiseGenerator->GetNoiseMapTemperature();
	const TArray<float> NoiseMapHumidity = _NoiseGenerator->getNoiseMapHumidity();
	const TArray<FMapBiomeData> BiomesData = _BiomesData;
	const bool AreColorsApplied = _AreColorsApplied;
	
	// Applying colors to texture, which are depend on selected options
	ParallelFor(ArraySize, [&MipData, Size, NoiseMapTerrain, NoiseMapTemperature, NoiseMapHumidity, BiomesData, AreColorsApplied](int32 Idx)
	{
		int32 x = Idx / Size;
		int32 y = Idx % Size;

		uint8* DestPtr = &MipData[((y * Size) + x) * sizeof(FColor)];

		float CurrentHeight = NoiseMapTerrain[(y * Size) + x];
		float CurrentTemperature = NoiseMapTemperature[(y * Size) + x];
		float CurrentHumidity = NoiseMapHumidity[(y * Size) + x];

		//FColor PixelColor(CurrentHeight * 255, CurrentHeight * 255, CurrentHeight * 255);
		FColor PixelColor(0, 0, 0);

		if (AreColorsApplied)
		{
			for (FMapBiomeData Biome : BiomesData)
			{
				if (Biome.StartHeight <= CurrentHeight && CurrentHeight <= Biome.EndHeight)
				{
					if (Biome.StartTemperature <= CurrentTemperature && CurrentTemperature <= Biome.EndTemperature
						&&
						Biome.StartHumidity <= CurrentHumidity && CurrentHumidity <= Biome.EndHumidity)
					{
						PixelColor = Biome.MapColor;
						break;
					}
				}
			}
		}
		else
		{
			uint8 PixelValue = static_cast<uint8>(CurrentHeight * 255);
			PixelColor = FColor(PixelValue, PixelValue, PixelValue);
		}
		
		DestPtr[0] = PixelColor.B;
		DestPtr[1] = PixelColor.G;
		DestPtr[2] = PixelColor.R;
		DestPtr[3] = 0xFF;
	});
	
	// Unlocking texture data and updating it
	NewTexture->GetPlatformData()->Mips[0].BulkData.Unlock();
	NewTexture->UpdateResource();
	
	return NewTexture;
}

TArray<FTerrainData> AMapGenerator::GetTerrainData()
{
	// Calculating Array Size
	const int32 Size = _NoiseGenerator->GetSize();
	const int32 ArraySize = Size * Size;

	// Noises should be generated, but as precautions they are generated once more
	_NoiseGenerator->GenerateNoises();

	// Getting generated noises
	const TArray<float> NoiseMapTerrain = _NoiseGenerator->GetNoiseMapTerrain();
	const TArray<float> NoiseMapTemperature = _NoiseGenerator->GetNoiseMapTemperature();
	const TArray<float> NoiseMapHumidity = _NoiseGenerator->getNoiseMapHumidity();

	// Initializing array storing biomes data
	TArray<FTerrainData> TerrainData;
	const FTerrainData InitData;
	TerrainData.Init(InitData, ArraySize);

	// Calculating map's center
	const int32 Center = Size / 2;

	ParallelFor(ArraySize, [&](int32 Idx)
	{
		const int32 x = Idx / Size;
		const int32 y = Idx % Size;

		const int32 CurrentIndex = (y * Size) + x;

		// Center of the map should be at position = (0, 0)
		TerrainData[CurrentIndex].PosX = x - Center;
		TerrainData[CurrentIndex].PosY = y - Center;

		TerrainData[CurrentIndex].Height = NoiseMapTerrain[CurrentIndex];
		TerrainData[CurrentIndex].Temperature = NoiseMapTemperature[CurrentIndex];
		TerrainData[CurrentIndex].Humidity = NoiseMapHumidity[CurrentIndex];
	});

	return TerrainData;
}

void AMapGenerator::SetNoiseGeneratorComponent(UNoiseGenerator* NoiseGenerator)
{
	_NoiseGenerator = NoiseGenerator;
}

UNoiseGenerator* AMapGenerator::GetNoiseGeneratorComponent()
{
	return _NoiseGenerator;
}

void AMapGenerator::SetAreColorsApplied(const bool& AreColorsApplied)
{
	_AreColorsApplied = AreColorsApplied;
}

bool AMapGenerator::GetAreColorsApplied()
{
	return _AreColorsApplied;
}