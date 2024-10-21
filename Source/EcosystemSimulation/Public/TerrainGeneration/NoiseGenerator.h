// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Async/ParallelFor.h"

#include "NoiseGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECOSYSTEMSIMULATION_API UNoiseGenerator final: public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNoiseGenerator();

	// Generating noises: Terrain, Temperature, Humidity
	void GenerateNoises();

	TArray<float> GetNoiseMapTerrain() const;

	TArray<float> GetNoiseMapTemperature() const;

	TArray<float> getNoiseMapHumidity() const;

	// Generating falloff mask -> square mask
	void GenerateFalloffMask();
	
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSize(const int32& Size);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetSize() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetSeed(const int32& Seed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetSeed() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetOffset(const FVector2D& Offset);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FVector2D GetOffset() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetScale(const float& Scale);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetScale() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetOctaves(const int32& Octaves);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	int32 GetOctaves() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetPersistance(const float& Persistance);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetPersistance() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetLacunarity(const float& Lacunarity);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetLacunarity() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetIsGeneratingIslandNoise(const bool& bIsGeneratingIslandNoise);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	bool GetIsGeneratingIslandNoise();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Variables responsible for noise generation
	UPROPERTY(BlueprintSetter = SetSize, BlueprintGetter = GetSize, EditAnywhere, Category = "Noise Generation")
	int32 _Size = 128;

	UPROPERTY(BlueprintSetter = SetSeed, BlueprintGetter = GetSeed, EditAnywhere, Category = "Noise Generation")
	int32 _Seed = 1;

	UPROPERTY(BlueprintSetter = SetOffset, BlueprintGetter = GetOffset, EditAnywhere, Category = "Noise Generation")
	FVector2D _Offset = FVector2D(0, 0);

	UPROPERTY(BlueprintSetter = SetScale, BlueprintGetter = GetScale, EditAnywhere, Category = "Noise Generation")
	float _Scale = 27.4f;

	UPROPERTY(BlueprintSetter = SetOctaves, BlueprintGetter = GetOctaves, EditAnywhere, Category = "Noise Generation")
	int32 _Octaves = 4;

	UPROPERTY(BlueprintSetter = SetPersistance, BlueprintGetter = GetPersistance, EditAnywhere, Category = "Noise Generation")
	float _Persistance = 0.5f;

	UPROPERTY(BlueprintSetter = SetLacunarity, BlueprintGetter = GetLacunarity, EditAnywhere, Category = "Noise Generation")
	float _Lacunarity = 2.0f;

	UPROPERTY(BlueprintSetter = SetIsGeneratingIslandNoise, BlueprintGetter = GetIsGeneratingIslandNoise, EditAnywhere, Category = "Noise Generation")
	bool _IsGeneratingIslandNoise = true;

	// Varaibles responsible for Biomes Size
	UPROPERTY(EditAnywhere, Category = "Noise Generation")
	float _TemperatureScaleMultiplier = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Noise Generation")
	float _HumidityScaleMultiplier = 3.0f;

	// Arrays storing information about terrain, temperature and humidity
	TArray<float> _NoiseMapTerrain;
	TArray<float> _NoiseMapTemperature;
	TArray<float> _NoiseMapHumidity;

	// Array storing information about falloff mask
	TArray<float> _FalloffMask;
};
