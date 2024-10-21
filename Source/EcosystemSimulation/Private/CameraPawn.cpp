// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating defaul scene component
	_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Component"));
	SetRootComponent(_SceneComponent);

	// Creating and attaching Spring Arm Component
	_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	_SpringArmComponent->AttachToComponent(_SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);

	_SpringArmComponent->bDoCollisionTest = false;

	// Creating and attachin Camera Component
	_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	_CameraComponent->AttachToComponent(_SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void  ACameraPawn::SetCameraPoistionBoundaries(const TArray<FTerrainData>& TerrainData)
{
	const int32 Size = static_cast<int32>(FMath::Sqrt(static_cast<float>(TerrainData.Num())));

	_MaxPosX =  static_cast<float>(Size / 2) * _WorldScale;
	_MinPosX = -_MaxPosX;

	_MaxPosY = static_cast<float>(Size / 2) * _WorldScale;
	_MinPosY = -_MaxPosY;
}

void ACameraPawn::SetCameraSpeed(const float& CameraSpeed)
{
	_CameraSpeed = FMath::Max(0.0f, CameraSpeed);
}

float ACameraPawn::GetCameraSpeed() const
{
	return _CameraSpeed;
}

void ACameraPawn::SetZoomSpeed(const float& ZoomSpeed)
{
	_ZoomSpeed = FMath::Max(0.0f, ZoomSpeed);
}

float ACameraPawn::GetZoomSpeed() const
{
	return _ZoomSpeed;
}

void ACameraPawn::SetMinZoom(const float& MinZoom)
{
	_MinZoom = FMath::Clamp(MinZoom, 0.0f, _MaxZoom);
}

float ACameraPawn::GetMinZoom() const
{
	return _MinZoom;
}

void ACameraPawn::SetMaxZoom(const float& MaxZoom)
{
	_MaxZoom = FMath::Max(MaxZoom, _MinZoom);
}

float ACameraPawn::GetMaxZoom() const
{
	return _MaxZoom;
}

#pragma region Camera Boundaries

void ACameraPawn::SetMinPosX(const float& MinPosX)
{
	_MinPosX = MinPosX;
}

float ACameraPawn::GetMinPosX() const
{
	return _MinPosX;
}

void ACameraPawn::SetMaxPosX(const float& MaxPosX)
{
	_MaxPosX = MaxPosX;
}

float ACameraPawn::GetMaxPosX() const
{
	return _MaxPosX;
}

void ACameraPawn::SetMinPosY(const float& MinPosY)
{
	_MinPosY = MinPosY;
}

float ACameraPawn::GetMinPosY() const
{
	return _MinPosY;
}

void ACameraPawn::SetMaxPosY(const float& MaxPosY)
{
	_MaxPosY = MaxPosY;
}

float ACameraPawn::GetMaxPosY() const
{
	return _MaxPosY;
}

#pragma endregion

#pragma region Components

USpringArmComponent* ACameraPawn::GetSpringArmComponent() const
{
	return _SpringArmComponent;
}

#pragma endregion