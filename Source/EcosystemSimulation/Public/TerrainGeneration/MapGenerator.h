// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../DataStructures.h"
#include "NoiseGenerator.h"

#include "MapGenerator.generated.h"

UCLASS(Blueprintable)
class ECOSYSTEMSIMULATION_API AMapGenerator final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

	// Function generating Map Texture based on noise generated by Noise Generator Component
	UFUNCTION(BlueprintCallable)
	UTexture2D* GenerateMapTexture() const;

	// Function preparing terrain data, which will be send to Simulation Level
	UFUNCTION(BlueprintCallable)
	TArray<FTerrainData> GetTerrainData();

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetNoiseGeneratorComponent(UNoiseGenerator* NoiseGenerator);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	UNoiseGenerator* GetNoiseGeneratorComponent();

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetAreColorsApplied(const bool& AreColorsApplied);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetAreColorsApplied();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	#pragma region Components

	UPROPERTY(BlueprintSetter = SetNoiseGeneratorComponent, BlueprintGetter = GetNoiseGeneratorComponent)
	UNoiseGenerator* _NoiseGenerator = nullptr;

	#pragma endregion

	UPROPERTY(BlueprintSetter = SetAreColorsApplied, BlueprintGetter = GetAreColorsApplied)
	bool _AreColorsApplied = true;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
	TArray<FMapBiomeData> _BiomesData;
};
