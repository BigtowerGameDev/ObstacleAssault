// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	enum DirectionAxis {UP = 1, DOWN, RIGHT, LEFT, FORWARD, BACKWARD};

	FVector InitPos;

	FVector MyVelocity = FVector(0,0,0);

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float speed = 100;

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float maxDistance = 0;

	bool changeDir = false;

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	int dirAxis = FORWARD;

	UPROPERTY(VisibleAnywhere, Category = "Moving Platform")
	float distanceMoved;

	UPROPERTY(EditAnywhere, Category = "Rotating Platform")
	bool rotate = false;

	UPROPERTY(EditAnywhere, Category = "Rotating Platform")
	bool clockWise = false;

	UPROPERTY(EditAnywhere, Category = "Rotating Platform")
	FRotator rotationVelocity;

	void MovePlatform(float DeltaTime);

	void RotatePlatform(float DeltaTime);

	float DistanceMoved() const;
};
