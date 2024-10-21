// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TerrainGeneration/TerrainGenerator.h"
#include "Plants/Plant.h"
#include "Animals/AnimalFemale.h"
#include "Animals/AnimalMale.h"
#include "DataStructures.h"

#include "Kismet/GameplayStatics.h"

#include "WorldManager.generated.h"

UCLASS()
class ECOSYSTEMSIMULATION_API AWorldManager final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetTerrainGenerators();

	// Initial plants spawn only in optimal condition
	UFUNCTION(BlueprintCallable)
	void SetInitialPlants();

	UFUNCTION(BlueprintCallable)
	void SetInitialAnimals();

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetTerrainData(const TArray<FTerrainData>& TerrainData);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	TArray<FTerrainData> GetTerrainData() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetGeneratorsToBeSpawned(TArray<TSubclassOf<ATerrainGenerator>> GeneratorsToBeSpawned);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	TArray<TSubclassOf<ATerrainGenerator>> GetGeneratorsToBeSpawned();

private:
	UPROPERTY(BlueprintSetter = SetTerrainData, BlueprintGetter = GetTerrainData, Transient)
	TArray<FTerrainData> _TerrainData;

	UPROPERTY(BlueprintSetter = SetGeneratorsToBeSpawned, BlueprintGetter = GetGeneratorsToBeSpawned, EditDefaultsOnly, Category = "Terrain Generation")
	TArray<TSubclassOf<ATerrainGenerator>> _GeneratorsToBeSpawned;

#pragma region Plants Spawn

	UPROPERTY(EditDefaultsOnly, Category = "Plants Spawn")
	TArray<FPlantSpawnInfo> _PlantsToBeSpawned;

	UPROPERTY(Transient)
	TArray<FPlantsTerrain> _TerrainPlants;

#pragma endregion

#pragma region Animal Spawn

	UPROPERTY(EditDefaultsOnly, Category = "Animal Spawn")
	TArray<FAnimalSpawnInfo> _AnimalsToBeSpawned;

	UPROPERTY(Transient)
	TArray<FAnimalsTerrain> _TerrainAnimals;

#pragma endregion

	UPROPERTY(EditDefaultsOnly)
	float _OffsetZ = 50.0f;

	UPROPERTY(EditDefaultsOnly)
	float _WorldScale = 100.0f;
};
