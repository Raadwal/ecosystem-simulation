// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../DataStructures.h"
#include "PlantBase.h"

#include "Components/BoxComponent.h"

#include "Plant.generated.h"

UCLASS()
class ECOSYSTEMSIMULATION_API APlant final: public APlantBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlant();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Set Temperature and Humidity data based on current location
	*/
	UFUNCTION(BlueprintCallable)
	void SetEnvironmentData(const TArray<FTerrainData>& TerrainData);

private:
	
	/*
	* Method called in Tick method
	* 
	* Responsible for plant grow phase
	*/
	void Grow(const float& DeltaTime);

	/*
	* Method called in Tick method
	*
	* Responsible for reproduction phase
	*/
	void Reproduce(const float& DeltaTime);

	/*
	* Method called in Tick Method
	*
	* Responsible for dealing envirnonment damage to plant
	*/
	void TakeEnviromentDamage(const float& DeltaTime);

	/*
	* Method called in Reproduce method
	*
	* When plant is ready to reproduce, the reproduction attempt is made
	*/
	void TryToReproduce();

	/*
	* Methoid is called in Reproduce method
	*
	* When plant is ready to reproduce, the mutation is possible
	*/
	void TryToMutate();

	/*
	* Method is called in TryToReproduce and TryToMutate Methods
	* 
	* Applying mutation to plant passed as argument
	*/
	void ApplyMutation(APlant* const Plant, const float& MinChange, const float& MaxChange);

	/*
	* Method called in TryToReproduce method
	*
	*  When the reproduction attempt is successful, the ancestor is gaining plant traits + mutations
	*/
	void AncestorSetup(APlant* const Ancestor);

	/*
	* Method called in TryToReproduce method
	*
	* When the reproduction attempt is successful, the offset for ancestor location is generated 
	*/
	FVector CreateLocationOffset();

	/*
	* Method responsible for applying damage to plant and destroying it
	*/
	void ApplyDamage(const float& Damage);

	/*
	* Method needed to check if plant is spawned on water
	*/
	UFUNCTION(BlueprintCallable)
	bool CheckIfAboveGivenTerrainHeight(const TArray<FTerrainData>& WaterData, const float WaterLevelEnds) const;

	/*
	* Get Index based on APlant position from TerrainData Array
	*/
	int32 GetIndexFromTerrainData(const TArray<FTerrainData>& TerrainData) const;


private:
	/*
	* Distance between centers of chunks - scale from word generator
	*/
	UPROPERTY(EditDefaultsOnly)
	float _WorldScale = 100.0f;

	/*
	* Ancestor to be spawned -> Same class as parent
	*/
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlant> _Self;

#pragma region Components

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* _StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* _CollisionMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _SceneComponent = nullptr;

#pragma endregion
};
