// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../DataStructures.h"

#include "Components/InstancedStaticMeshComponent.h"

#include "TerrainGenerator.generated.h"

UCLASS()
class ECOSYSTEMSIMULATION_API ATerrainGenerator final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called when an instance of this class is placed(in editor) or spawned.
	virtual void OnConstruction(const FTransform& Transform) override;

	// Generate Terrain
	UFUNCTION(BlueprintCallable)
	void GenerateTerrain();

	// Returning terrain chunks where none objects are generated
	UFUNCTION(BlueprintCallable)
	TArray<FTerrainData> GetUnoccupoiedTerrainData();

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTerrainScale(const float& TerrainScale);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetTerrainScale() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetOffsetZ(const float& OffsetZ);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetOffsetZ() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetBiomeData(const FBiomeData& BiomeData);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	FBiomeData GetBiomeData() const;

	UFUNCTION(BlueprintCallable)
	float GetBiomeEndHeight() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTerrainData(const TArray<FTerrainData>& TerrainData);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	TArray<FTerrainData> GetTerrainData() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSeed(const int32& Seed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetSeed() const;

protected:
	// Generate Terrain Objects
	// IMPORTANT: size of _InstancedStaticMeshArray has to be equal to _TerrainObjectsData
	// _InstancedStaticMeshArray - UInstancedStaticMeshComponent children of the actor (Root doesn't count)
	// _TerrainObjectsData - Variable with Objects Data
	void GenerateTerrainObject();

	UPROPERTY(BlueprintSetter = SetTerrainScale, BlueprintGetter = GetTerrainScale, EditAnywhere, Category = "Terrain Generator")
	float _TerrainScale = 1.0f;

	UPROPERTY(BlueprintSetter = SetOffsetZ, BlueprintGetter = GetOffsetZ, EditAnywhere, Category = "Terrain Generator")
	float _OffsetZ = 0.0f;

	// Information about biome which is generated
	UPROPERTY(BlueprintSetter = SetBiomeData, BlueprintGetter = GetBiomeData, EditAnywhere, Category = "Terrain Generator")
	FBiomeData _BiomeData;

	// Information about Terrain Objects of biome which is generated
	// First Object in the list will be generated as first and will occupy the chunk of terrain
	// Other objects can't be generated at occupied chunk of terrain
	UPROPERTY(EditAnywhere, Category = "Terrain Generator")
	TArray<FTerrainObjectData> _TerrainObjectsData;

	// Terrain Data - Whole Map
	UPROPERTY(BlueprintSetter = SetTerrainData, BlueprintGetter = GetTerrainData)
	TArray<FTerrainData> _TerrainData;

	UPROPERTY(BlueprintSetter = SetSeed, BlueprintGetter = GetSeed)
	int32 _Seed = 0;

	// Generated terrain - Terrain of the generated Biome -> Based on _TerrainData and _BiomeData
	// Information about terrain chunk where nothing was generated
	UPROPERTY(Transient)
	TArray<FTerrainData> _GeneratedUnoccupiedTerrainData;

	// Transforms of the terrain
	UPROPERTY(Transient)
	TArray<FTransform> _TransformsTerrain;

	// Transforms of the Terrain Objects
	UPROPERTY(Transient)
	TArray<FTerrainObjectDataTransforms> _TransformsTerrainObjects;

	#pragma region Components

	// ISMC of Terrain
	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* _InstancedStaticMeshComponentTerrain;

	// ISMC of Terrain Objects
	UPROPERTY(VisibleAnywhere)
	TArray<UInstancedStaticMeshComponent*> _InstancedStaticMeshArray;

	#pragma endregion
};
