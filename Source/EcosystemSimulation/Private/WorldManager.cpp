// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldManager::SetTerrainGenerators()
{
	
	// Spawns Actors responsible for Terrain Generation.
	for (const TSubclassOf<ATerrainGenerator>& Generator : _GeneratorsToBeSpawned)
	{
		FVector Location(0.0f, 0.0f, 0.0f);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		GetWorld()->SpawnActor<ATerrainGenerator>(Generator, Location, Rotation);
	}
	
}

void AWorldManager::SetInitialPlants()
{
	// Initialize Array
	FPlantsTerrain PlantsTerrainInit;
	_TerrainPlants.Empty();
	_TerrainPlants.Init(PlantsTerrainInit, _PlantsToBeSpawned.Num());

	// Get Terrain that is suitable for plants
	for (int32 Idx = 0; Idx < _PlantsToBeSpawned.Num(); Idx++)
	{
		for (FTerrainData& ChunkData : _TerrainData)
		{
			if (_PlantsToBeSpawned[Idx].StartHeight <= ChunkData.Height && ChunkData.Height <= _PlantsToBeSpawned[Idx].EndHeight)
			{
				if ((_PlantsToBeSpawned[Idx].StartTemperature <= ChunkData.Temperature && ChunkData.Temperature <= _PlantsToBeSpawned[Idx].EndTemperature)
					&&
					(_PlantsToBeSpawned[Idx].StartHumidity <= ChunkData.Humidity && ChunkData.Humidity <= _PlantsToBeSpawned[Idx].EndHumidity))
				{
					_TerrainPlants[Idx].TerrainData.Add(ChunkData);
				}
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Array Size: %d, %d"), Idx, _TerrainPlants[Idx].TerrainData.Num());
	}
	
	// Calculate number of object to be spawned
	TArray<int32> InitialPlantSpawnQuantity;
	InitialPlantSpawnQuantity.Empty();
	InitialPlantSpawnQuantity.Init(0, _PlantsToBeSpawned.Num());

	for (int32 Idx = 0; Idx < _PlantsToBeSpawned.Num(); Idx++)
	{
		InitialPlantSpawnQuantity[Idx] = FGenericPlatformMath::RoundToInt(_TerrainPlants[Idx].TerrainData.Num() * (_PlantsToBeSpawned[Idx].SpawnChance / 100.0f));

		UE_LOG(LogTemp, Warning, TEXT("Initial quantity: %d, %d"), Idx, InitialPlantSpawnQuantity[Idx]);
	}
	
	// Spawn plants
	for (int32 Idx = 0; Idx < _PlantsToBeSpawned.Num(); Idx++)
	{
		TArray<AActor*> FoundActors;
		FoundActors.Empty();

		int32 MissingPlantQuantity = InitialPlantSpawnQuantity[Idx];
		TArray<int32> IterationSpawnQuantity;
		IterationSpawnQuantity.Empty();

		// Spawn Plants until plants occupied percentage of fields equal to plant spawn chance percentage
		while (FoundActors.Num() < InitialPlantSpawnQuantity[Idx] && MissingPlantQuantity <= _TerrainPlants[Idx].TerrainData.Num())
		{
			// List of chunks that were used in current loop iteration
			TArray<FTerrainData> UsedChunks;

			// Get random index - plants will be spawned at chunk with that index
			for (int32 i = 0; i < MissingPlantQuantity; i++)
			{
				const int32 RandomIdx = FMath::RandRange(0, _TerrainPlants[Idx].TerrainData.Num() - 1);
				const FTerrainData& ChunkData = _TerrainPlants[Idx].TerrainData[RandomIdx];

				UsedChunks.Add(ChunkData);

				// Location of the Plant
				FVector Location(_WorldScale * ChunkData.PosX, _WorldScale * ChunkData.PosY, _OffsetZ);

				// Rotation of the Plant
				FRotator Rotation(0.0f, 0.0f, 0.0f);
				Rotation.Yaw = FMath::FRandRange(-180.0f, 180.0f);

				// Spawn plant
				APlant* SpawnedPlant = GetWorld()->SpawnActor<APlant>(_PlantsToBeSpawned[Idx].PlantToBeSpawned, Location, Rotation);

				// Set random grow status for newly spawned plant -> CPU usage optimization
				if (FMath::RandRange(0, 1) == 1)
				{
					SpawnedPlant->SetPlantStatus(EPlantStatus::GROWING);
				}
				else
				{
					SpawnedPlant->SetPlantStatus(EPlantStatus::REPRODUCING);
				}
				
				if (SpawnedPlant->GetPlantStatus() == EPlantStatus::GROWING)
				{
					SpawnedPlant->SetTimeSinceStartedGrowingSeconds(FMath::FRandRange(0.0f, SpawnedPlant->GetTimeToGrowSeconds()));
				}
				else if (SpawnedPlant->GetPlantStatus() == EPlantStatus::REPRODUCING)
				{
					SpawnedPlant->SetTimeSinceStartedReproductionAttemptSeconds(FMath::FRandRange(0.0f, SpawnedPlant->GetTimeToReproductionAttemptSeconds()));
				}
			}

			// Removde used chunks from the list
			for (FTerrainData& Chunk : UsedChunks)
			{
				_TerrainPlants[Idx].TerrainData.Remove(Chunk);
			}

			// Get number of spawned plants
			FoundActors.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), _PlantsToBeSpawned[Idx].PlantToBeSpawned, FoundActors);

			// Get number of spawned plants in currrent iteration
			int32 PreviouslySpawned = 0;
			for (int32 Quantity : IterationSpawnQuantity)
			{
				PreviouslySpawned += Quantity;
			}
			IterationSpawnQuantity.Add(FoundActors.Num() - PreviouslySpawned);

			// Decrease number of plants that have to be spawned in next iteration
			MissingPlantQuantity -= FoundActors.Num() - PreviouslySpawned;
			
			UE_LOG(LogTemp, Warning, TEXT("=============================="));
			UE_LOG(LogTemp, Warning, TEXT("Found Actors after: %d, %d"), Idx, FoundActors.Num());
			UE_LOG(LogTemp, Warning, TEXT("Missing Actors after: %d, %d"), Idx, MissingPlantQuantity);
		}
	}
}

void AWorldManager::SetInitialAnimals()
{
	// Initialize Array
	FAnimalsTerrain AnimalsTerrainInit;
	_TerrainAnimals.Empty();
	_TerrainAnimals.Init(AnimalsTerrainInit, _AnimalsToBeSpawned.Num());

	// Get Terrain that is suitable for animals
	for (int32 Idx = 0; Idx < _AnimalsToBeSpawned.Num(); Idx++)
	{
		for (FTerrainData& ChunkData : _TerrainData)
		{
			if (_AnimalsToBeSpawned[Idx].StartHeight <= ChunkData.Height && ChunkData.Height <= _AnimalsToBeSpawned[Idx].EndHeight)
			{
				if ((_AnimalsToBeSpawned[Idx].StartTemperature <= ChunkData.Temperature && ChunkData.Temperature <= _AnimalsToBeSpawned[Idx].EndTemperature)
					&&
					(_AnimalsToBeSpawned[Idx].StartHumidity <= ChunkData.Humidity && ChunkData.Humidity <= _AnimalsToBeSpawned[Idx].EndHumidity))
				{
					_TerrainAnimals[Idx].TerrainData.Add(ChunkData);
				}
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Array Size: %d, %d"), Idx, _TerrainAnimals[Idx].TerrainData.Num());
	}

	// Spawn plants
	for (int32 Idx = 0; Idx < _AnimalsToBeSpawned.Num(); Idx++)
	{
		TArray<AActor*> FoundMaleActors;
		TArray<AActor*> FoundFemaleActors;
		FoundMaleActors.Empty();
		FoundFemaleActors.Empty();

		// Dividing given number of animal into equal number of males and females
		int32 MissingMaleQuantity = static_cast<int32>(_AnimalsToBeSpawned[Idx].InitialSpawnQuantity / 2);
		int32 MissingFemaleQuantity = static_cast<int32>(_AnimalsToBeSpawned[Idx].InitialSpawnQuantity / 2);

		// Matching given number of animals
		if (_AnimalsToBeSpawned[Idx].InitialSpawnQuantity % 2 != 0)
		{
			(FMath::RandRange(0, 1) == 1) ? MissingMaleQuantity++ : MissingFemaleQuantity++;
		}

		const int32 InitialMaleSpawnQuantity = MissingMaleQuantity;
		const int32 InitialFemaleSpawnQuantity = MissingFemaleQuantity;

		TArray<int32> IterationSpawnMaleQuantity;
		IterationSpawnMaleQuantity.Empty();

		TArray<int32> IterationSpawnFemaleQuantity;
		IterationSpawnFemaleQuantity.Empty();

		// Spawn animals until initial given animals quantity will be reached
		while ((FoundMaleActors.Num() < InitialMaleSpawnQuantity || FoundFemaleActors.Num() < InitialFemaleSpawnQuantity)
			   &&
			   (MissingMaleQuantity + MissingFemaleQuantity) <= _TerrainAnimals[Idx].TerrainData.Num())
		{
			// List of chunks that were used in current loop iteration
			TArray<FTerrainData> UsedChunks;

			if (FoundMaleActors.Num() < InitialMaleSpawnQuantity && MissingMaleQuantity <= _TerrainAnimals[Idx].TerrainData.Num())
			{
				UsedChunks.Empty();

				// Get random index - male animal will be spawned at chunk with that index
				for (int32 i = 0; i < MissingMaleQuantity; i++)
				{
					const int32 RandomIdx = FMath::RandRange(0, _TerrainAnimals[Idx].TerrainData.Num() - 1);
					const FTerrainData& ChunkData = _TerrainAnimals[Idx].TerrainData[RandomIdx];

					UsedChunks.Add(ChunkData);

					// Location of the animal
					FVector Location(_WorldScale * ChunkData.PosX, _WorldScale * ChunkData.PosY, _OffsetZ);

					// Rotation of the animal
					FRotator Rotation(0.0f, 0.0f, 0.0f);
					Rotation.Yaw = FMath::FRandRange(-180.0f, 180.0f);

					// Spawn plant
					AAnimal* SpawnedPlant = GetWorld()->SpawnActor<AAnimal>(_AnimalsToBeSpawned[Idx].MaleToBeSpawned, Location, Rotation);	
				}
			}

			// Removde used chunks from the list
			for (FTerrainData& Chunk : UsedChunks)
			{
				_TerrainAnimals[Idx].TerrainData.Remove(Chunk);
			}


			if (FoundFemaleActors.Num() < InitialFemaleSpawnQuantity && MissingFemaleQuantity <= _TerrainAnimals[Idx].TerrainData.Num())
			{
				UsedChunks.Empty();

				// Get random index - female animal will be spawned at chunk with that index
				for (int32 i = 0; i < MissingFemaleQuantity; i++)
				{
					const int32 RandomIdx = FMath::RandRange(0, _TerrainAnimals[Idx].TerrainData.Num() - 1);
					const FTerrainData& ChunkData = _TerrainAnimals[Idx].TerrainData[RandomIdx];

					UsedChunks.Add(ChunkData);

					// Location of the animal
					FVector Location(_WorldScale * ChunkData.PosX, _WorldScale * ChunkData.PosY, _OffsetZ);

					// Rotation of the animal
					FRotator Rotation(0.0f, 0.0f, 0.0f);
					Rotation.Yaw = FMath::FRandRange(-180.0f, 180.0f);

					// Spawn plant
					AAnimal* SpawnedPlant = GetWorld()->SpawnActor<AAnimal>(_AnimalsToBeSpawned[Idx].FemaleToBeSpawned, Location, Rotation);
				}
			}

			// Removde used chunks from the list
			for (FTerrainData& Chunk : UsedChunks)
			{
				_TerrainAnimals[Idx].TerrainData.Remove(Chunk);
			}

			// Get number of spawned animals
			FoundMaleActors.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), _AnimalsToBeSpawned[Idx].MaleToBeSpawned, FoundMaleActors);

			FoundFemaleActors.Empty();
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), _AnimalsToBeSpawned[Idx].FemaleToBeSpawned, FoundFemaleActors);

			// Get number of spawned animals in currrent iteration
			int32 PreviouslySpawnedMales = 0;
			for (int32 Quantity : IterationSpawnMaleQuantity)
			{
				PreviouslySpawnedMales += Quantity;
			}
			IterationSpawnMaleQuantity.Add(FoundMaleActors.Num() - PreviouslySpawnedMales);

			int32 PreviouslySpawnedFemales = 0;
			for (int32 Quantity : IterationSpawnFemaleQuantity)
			{
				PreviouslySpawnedFemales += Quantity;
			}
			IterationSpawnFemaleQuantity.Add(FoundFemaleActors.Num() - PreviouslySpawnedFemales);

			// Decrease number of animals that have to be spawned in next iteration
			MissingMaleQuantity -= FoundMaleActors.Num() - PreviouslySpawnedMales;
			MissingFemaleQuantity -= FoundFemaleActors.Num() - PreviouslySpawnedFemales;

			UE_LOG(LogTemp, Warning, TEXT("=============================="));
			UE_LOG(LogTemp, Warning, TEXT("Found Males/Females after: %d, %d/%d"), Idx, FoundMaleActors.Num(), FoundFemaleActors.Num());
			UE_LOG(LogTemp, Warning, TEXT("Missing Males/Females after: %d, %d/%d"), Idx, MissingMaleQuantity, MissingFemaleQuantity);
		}
	}
}

TArray<TSubclassOf<ATerrainGenerator>> AWorldManager::GetGeneratorsToBeSpawned()
{
	return _GeneratorsToBeSpawned;
}

void AWorldManager::SetGeneratorsToBeSpawned(TArray<TSubclassOf<ATerrainGenerator>> GeneratorsToBeSpawned)
{
	_GeneratorsToBeSpawned = GeneratorsToBeSpawned;
}

void AWorldManager::SetTerrainData(const TArray<FTerrainData>& TerrainData)
{
	_TerrainData = TerrainData;
}

TArray<FTerrainData> AWorldManager::GetTerrainData() const
{
	return _TerrainData;
}