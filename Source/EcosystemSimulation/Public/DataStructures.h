// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/InstancedStaticMeshComponent.h"

#include "DataStructures.generated.h"

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API  FBiomeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float StartHeight = 0.0f;

	UPROPERTY(EditAnywhere)
	float EndHeight = 0.0f;

	UPROPERTY(EditAnywhere)
	float StartTemperature = 0.0f;

	UPROPERTY(EditAnywhere)
	float EndTemperature = 0.0f;

	UPROPERTY(EditAnywhere)
	float StartHumidity = 0.0f;

	UPROPERTY(EditAnywhere)
	float EndHumidity = 0.0f;
};

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FMapBiomeData : public FBiomeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Name = "";

	UPROPERTY(EditAnywhere)
	FColor MapColor = FColor(0.0f, 0.0f, 0.0f);
};

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FTerrainData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int32 PosX = 0;

	UPROPERTY(EditAnywhere)
	int32 PosY = 0;

	UPROPERTY(EditAnywhere)
	float Height = 0.0f;

	UPROPERTY(EditAnywhere)
	float Temperature = 0.0f;

	UPROPERTY(EditAnywhere)
	float Humidity = 0.0f;


	bool operator==(const FTerrainData& TerrainData) const
	{
		return
			PosX == TerrainData.PosX && PosY == TerrainData.PosY &&
			Height == TerrainData.Height && Temperature == TerrainData.Temperature && Humidity == TerrainData.Humidity;
	}
};

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FTerrainObjectData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float SpawnChancePct;

	UPROPERTY(EditAnywhere)
	float OffsetZ;

	UPROPERTY(EditAnywhere)
	float MinScale;

	UPROPERTY(EditAnywhere)
	float MaxScale;
};


USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FTerrainObjectDataTransforms
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient)
	TArray<FTransform> Transforms;
};

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FPlantsTerrain
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient)
	TArray<FTerrainData> TerrainData;
};

class APlant;

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FPlantSpawnInfo : public FBiomeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlant> PlantToBeSpawned;

	UPROPERTY(EditDefaultsOnly)
	float SpawnChance = 0.0f;
};

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FAnimalsTerrain
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(Transient)
	TArray<FTerrainData> TerrainData;
};

class AAnimalMale;
class AAnimalFemale;

USTRUCT(BlueprintType)
struct ECOSYSTEMSIMULATION_API FAnimalSpawnInfo : public FBiomeData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAnimalMale> MaleToBeSpawned;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAnimalFemale> FemaleToBeSpawned;

	/**
	* Spawn quantity will be qualy divided into malesand females.
	* If number is odd, the gender of the last animal will be selected randomly.
	*/
	UPROPERTY(EditDefaultsOnly)
	int32 InitialSpawnQuantity = 0;
};

USTRUCT()
struct ECOSYSTEMSIMULATION_API FFatherTraits
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float SmallMutationChance = 0.0f;

	UPROPERTY()
	float MediumMutationChance = 0.0f;

	UPROPERTY()
	float LargeMutationChance = 0.0f;

	UPROPERTY()
	float TimeToGrowSeconds = 0.0f;

	UPROPERTY()
	float Attack = 0.0f;

	UPROPERTY()
	float InitialHealth = 0.0f;

	UPROPERTY()
	float HungerMax = 0.0f;

	UPROPERTY()
	float HungerGainSecond = 0.0f;

	UPROPERTY()
	float ThirstMax = 0.0f;

	UPROPERTY()
	float ThirstGainSecond = 0.0f;

	UPROPERTY()
	float ReproductiveUrgeMax = 0.0f;

	UPROPERTY()
	float ReproductiveUrgeGainSecond = 0.0f;

	UPROPERTY()
	float CurrentSpeed = 0.0f;

	UPROPERTY()
	float CurrentSensoryDistance = 0.0f;

	UPROPERTY()
	float Resistance = 0.0f;

	UPROPERTY()
	float Nutrients = 0.0f;

	UPROPERTY()
	float EnvironmentStatusesAppliementSeconds = 0.0f;

	UPROPERTY()
	float MinHumidity = 0.0f;

	UPROPERTY()
	float MaxHumidity = 0.0f;

	UPROPERTY()
	float MinTemperature = 0.0f;

	UPROPERTY()
	float MaxTemperature = 0.0f;

	UPROPERTY()
	float MutationsCount = 0.0f;
};