// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DataStructures.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 

#include "CameraPawn.generated.h"

UCLASS()
class ECOSYSTEMSIMULATION_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Set camera position boundaries
	UFUNCTION(BluePrintCallable)
	void SetCameraPoistionBoundaries(const TArray<FTerrainData>& TerrainData);

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetCameraSpeed(const float& CameraSpeed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetCameraSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetZoomSpeed(const float& ZoomSpeed);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetZoomSpeed() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMinZoom(const float& MinZoom);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMinZoom() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxZoom(const float& MaxZoom);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxZoom() const;

#pragma region Camera Boundaries

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMinPosX(const float& MinPosX);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMinPosX() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxPosX(const float& MaxPosX);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxPosX() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMinPosY(const float& MinPosY);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMinPosY() const;

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void SetMaxPosY(const float& MaxPosY);

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	float GetMaxPosY() const;

#pragma endregion

#pragma region Components

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	USpringArmComponent* GetSpringArmComponent() const;

#pragma endregion

private:

	UPROPERTY(EditDefaultsOnly)
	float _WorldScale = 100.0f;

	UPROPERTY(BlueprintSetter = SetCameraSpeed, BlueprintGetter = GetCameraSpeed, EditDefaultsOnly)
	float _CameraSpeed = 20.0f;
	
	UPROPERTY(BlueprintSetter = SetZoomSpeed, BlueprintGetter = GetZoomSpeed, EditDefaultsOnly)
	float _ZoomSpeed = 200.0f;

	UPROPERTY(BlueprintSetter = SetMinZoom, BlueprintGetter = GetMinZoom, EditDefaultsOnly)
	float _MinZoom = 1000.0f;

	UPROPERTY(BlueprintSetter = SetMaxZoom, BlueprintGetter = GetMaxZoom, EditDefaultsOnly)
	float _MaxZoom = 5000.0f;

#pragma region Camera Boundaries

	UPROPERTY(BlueprintSetter = SetMinPosX, BlueprintGetter = GetMinPosX, VisibleAnywhere)
	float _MinPosX = 0.0f;

	UPROPERTY(BlueprintSetter = SetMaxPosX, BlueprintGetter = GetMaxPosX, VisibleAnywhere)
	float _MaxPosX = 0.0f;

	UPROPERTY(BlueprintSetter = SetMinPosY, BlueprintGetter = GetMinPosY, VisibleAnywhere)
	float _MinPosY = 0.0f;

	UPROPERTY(BlueprintSetter = SetMaxPosY, BlueprintGetter = GetMaxPosY, VisibleAnywhere)
	float _MaxPosY = 0.0f;

#pragma endregion

#pragma region Components

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _SceneComponent;

	UPROPERTY(BlueprintGetter = GetSpringArmComponent, EditDefaultsOnly)
	USpringArmComponent* _SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* _CameraComponent;

#pragma endregion
};
