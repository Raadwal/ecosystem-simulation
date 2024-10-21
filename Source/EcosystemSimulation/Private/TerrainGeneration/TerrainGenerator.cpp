// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGeneration/TerrainGenerator.h"

// Sets default values
ATerrainGenerator::ATerrainGenerator()
{
	// Disabling tick - unnecessary
	PrimaryActorTick.bCanEverTick = false;

	// Creating Root component - ISMC for terrain
	_InstancedStaticMeshComponentTerrain = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Static Mesh Terrain"));
	SetRootComponent(_InstancedStaticMeshComponentTerrain);

	// Changing properties of the component
	_InstancedStaticMeshComponentTerrain->SetMobility(EComponentMobility::Movable);
	_InstancedStaticMeshComponentTerrain->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	_InstancedStaticMeshComponentTerrain->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATerrainGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void ATerrainGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void  ATerrainGenerator::GenerateTerrain()
{
	// Generate only if none istance exist
	if (_InstancedStaticMeshComponentTerrain->GetInstanceCount() == 0)
	{
		// Clear transforms array
		_TransformsTerrain.Empty(_TerrainData.Num());

		// Initialize Size of the map (Map always should be in shape of square)
		int32 Size = static_cast<int32>(FMath::Sqrt(static_cast<double>(_TerrainData.Num())));
		
		// Loop which is generating transforms for terrain
		for (int Idx = 0; Idx < _TerrainData.Num(); Idx++)
		{
			int x = Idx / Size;
			int y = Idx % Size;

			int CurrentIdx = (y * Size) + x;
			
			// Checking if Terrain Chunk is part of the Biome
			if (_BiomeData.StartHeight <= _TerrainData[CurrentIdx].Height && _TerrainData[CurrentIdx].Height <= _BiomeData.EndHeight)
			{
				if ((_BiomeData.StartTemperature <= _TerrainData[CurrentIdx].Temperature && _TerrainData[CurrentIdx].Temperature <= _BiomeData.EndTemperature)
					&&
					(_BiomeData.StartHumidity <= _TerrainData[CurrentIdx].Humidity && _TerrainData[CurrentIdx].Humidity <= _BiomeData.EndHumidity))
				{
					// Adding Transform to the Array of Transforms 
					_TransformsTerrain.Add(FTransform(FVector(_TerrainScale * _TerrainData[CurrentIdx].PosX, _TerrainScale * _TerrainData[CurrentIdx].PosY, _OffsetZ)));

					// Adding _TerrainData[CurrentIdx] to _GeneratedTerrainData
					// Less loops iterations during Terrain's Objects generation
					_GeneratedUnoccupiedTerrainData.Add(_TerrainData[CurrentIdx]);
				}
			}
		}

		// Add Transforms Array to ISMC Component (Terrain is visible)
		_InstancedStaticMeshComponentTerrain->AddInstances(_TransformsTerrain, false);
	}

	// After Terrain Generation, Terrain's Objects can be generated
	GenerateTerrainObject();

	// Change location for the moment (That's allow NavMesh to build!)
	FVector CurrentLocation = GetActorLocation();
	FVector LocationOffset(0.0f, 0.0f, -1000.0f);

	SetActorLocation(CurrentLocation + LocationOffset);
	SetActorLocation(CurrentLocation);
}

void ATerrainGenerator::GenerateTerrainObject()
{
	// Getting all Instanced Statis Meshes assigned to Actor
	TArray<UInstancedStaticMeshComponent*> InstancedStaticMeshComponents;
	GetComponents<UInstancedStaticMeshComponent>(InstancedStaticMeshComponents);

	// Removing RootComponent -> This component is responsible for terrain generation
	InstancedStaticMeshComponents.Remove(Cast<UInstancedStaticMeshComponent>(GetRootComponent()));

	// Number of _InstancedStaticMeshArray has to be equal to number of _TerrainObjectsData
	// Each index of _InstancedStaticMeshArray is also index of _TerrainObjectsData
	if (InstancedStaticMeshComponents.Num() != _TerrainObjectsData.Num())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Terrain Generator: number of ISMC children doesn't equal number of TerrainObjectsData"));

		return;
	}

	// Initializing Random Number Generator
	FRandomStream RandomNumberGenerator(_Seed);

	// Number of generated chunks - needed for spawn chance correction;
	const int32 InitiallyUnoccupiedChunks = _GeneratedUnoccupiedTerrainData.Num();

	// Index is needed -> _TransformsTerrainObjects
	for (int32 Idx = 0; Idx < InstancedStaticMeshComponents.Num(); Idx++)
	{
		// If default number of instances is not 0 go to next ISM
		if (InstancedStaticMeshComponents[Idx]->GetInstanceCount() != 0)
			break;

		// Changing properties of the component
		InstancedStaticMeshComponents[Idx]->SetMobility(EComponentMobility::Movable);
		InstancedStaticMeshComponents[Idx]->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
		InstancedStaticMeshComponents[Idx]->SetGenerateOverlapEvents(true);

		// Temporary object with transforms of current ISMC
		FTerrainObjectDataTransforms GeneratedTerrainTransorms;

		// Temporary terrain data containing information about fields that was generated
		TArray<FTerrainData> OccupiedTerrainData;

		// Loop through each terrain's chunk's data
		for (const FTerrainData& TerrainChunkData : _GeneratedUnoccupiedTerrainData)
		{
			const float RandomNumber = RandomNumberGenerator.FRandRange(0.0f, 100.0f);

			// _TerrainObjectsData with the same index as InstancedStaticMeshComponents
			float SpawnChance = _TerrainObjectsData[Idx].SpawnChancePct * (static_cast<float>(InitiallyUnoccupiedChunks) / static_cast<float>(_GeneratedUnoccupiedTerrainData.Num()));

			if (RandomNumber <= SpawnChance)
			{
				FTransform CurrentTransform;
				// Location of the Static Mesh
				CurrentTransform.SetLocation(FVector(_TerrainScale * TerrainChunkData.PosX, _TerrainScale * TerrainChunkData.PosY, _OffsetZ + _TerrainObjectsData[Idx].OffsetZ));

				// Scale of the Static Mesh
				const float RandomScale = RandomNumberGenerator.FRandRange(_TerrainObjectsData[Idx].MinScale, _TerrainObjectsData[Idx].MaxScale);
				CurrentTransform.SetScale3D(FVector(RandomScale, RandomScale, RandomScale));

				// Rotation of the Static Mesh
				const float RandomRotation = RandomNumberGenerator.FRandRange(-180.0f, 180.0f);
				FQuat NewRotation;
				NewRotation = CurrentTransform.GetRotation();
				NewRotation.Z = FMath::GetMappedRangeValueClamped(FVector2D(-180.0f, 180.0f), FVector2D(-1.0f, 1.0f), RandomRotation);
				NewRotation.Normalize();
				CurrentTransform.SetRotation(NewRotation);

				GeneratedTerrainTransorms.Transforms.Add(CurrentTransform);
				OccupiedTerrainData.Add(TerrainChunkData);
			}
		}

		// Add Transforms to the Array of Transforms for each object
		_TransformsTerrainObjects.Add(GeneratedTerrainTransorms);

		// Add Transforms Array to ISMC Component (Object is visible)
		InstancedStaticMeshComponents[Idx]->AddInstances(GeneratedTerrainTransorms.Transforms, false);

		// Removing terrain from _GeneratedUnoccupiedTerrainData where objects were generated
		for (FTerrainData& TerrainChunkData : OccupiedTerrainData)
		{
			_GeneratedUnoccupiedTerrainData.Remove(TerrainChunkData);
		}
	}
}

TArray<FTerrainData> ATerrainGenerator::GetUnoccupoiedTerrainData()
{
	return _GeneratedUnoccupiedTerrainData;
}

void ATerrainGenerator::SetTerrainScale(const float& TerrainScale)
{
	_TerrainScale = TerrainScale;
}

float ATerrainGenerator::GetTerrainScale() const
{
	return _TerrainScale;
}

void ATerrainGenerator::SetOffsetZ(const float& OffsetZ)
{
	_OffsetZ = OffsetZ;
}

float ATerrainGenerator::GetOffsetZ() const
{
	return _OffsetZ;
}

void ATerrainGenerator::SetBiomeData(const FBiomeData& BiomeData)
{
	_BiomeData = BiomeData;
}

FBiomeData ATerrainGenerator::GetBiomeData() const
{
	return _BiomeData;
}

float ATerrainGenerator::GetBiomeEndHeight() const
{
	return _BiomeData.EndHeight;
}

void ATerrainGenerator::SetTerrainData(const TArray<FTerrainData>& TerrainData)
{
	_TerrainData = TerrainData;
}

TArray<FTerrainData> ATerrainGenerator::GetTerrainData() const
{
	return _TerrainData;
}

void ATerrainGenerator::SetSeed(const int32& Seed)
{
	_Seed = Seed;
}

int32 ATerrainGenerator::GetSeed() const
{
	return _Seed;
}