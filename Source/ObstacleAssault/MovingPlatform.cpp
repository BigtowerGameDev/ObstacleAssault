// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	//Own code
	InitPos = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Own code
	MovePlatform(DeltaTime);

	//Rotate
	RotatePlatform(DeltaTime);

	//Distance moved
	distanceMoved = DistanceMoved();
}

void AMovingPlatform::MovePlatform (float DeltaTime){
	FVector loc = GetActorLocation();
	float dest = 0;
	float start = 0;
	float actual = 0;
	MyVelocity = FVector(0,0,0);

	//Apply axis direction config
	switch(dirAxis){
		case UP:
		MyVelocity.Z = speed;
		//dest = InitPos.Z + maxDistance;
		dest = (InitPos + (MyVelocity.GetSafeNormal() * maxDistance)).Z;
		start = InitPos.Z;
		actual = loc.Z;
		break;
		case DOWN:
		MyVelocity.Z = speed;
		dest = InitPos.Z;
		//start = InitPos.Z - maxDistance;
		start = (InitPos - (MyVelocity.GetSafeNormal() * maxDistance)).Z;
		actual = loc.Z;		
		break;
		case RIGHT:
		MyVelocity.Y = speed;
		//dest = InitPos.Y + maxDistance;
		dest = (InitPos + (MyVelocity.GetSafeNormal() * maxDistance)).Y;
		start = InitPos.Y;
		actual = loc.Y;
		break;
		case LEFT:
		MyVelocity.Y = speed;
		dest = InitPos.Y;
		//start = InitPos.Y - maxDistance;
		start = (InitPos - (MyVelocity.GetSafeNormal() * maxDistance)).Y;
		actual = loc.Y;
		break;
		case FORWARD:
		MyVelocity.X = speed;
		//dest = InitPos.X + maxDistance;
		dest = (InitPos + (MyVelocity.GetSafeNormal() * maxDistance)).X;
		start = InitPos.X;
		actual = loc.X;
		break;
		case BACKWARD:
		MyVelocity.X = speed;
		dest = InitPos.X;
		//start = InitPos.X - maxDistance;
		start = (InitPos - (MyVelocity.GetSafeNormal() * maxDistance)).X;
		actual = loc.X;
		break;
		default://FORWARD by default
		MyVelocity.X = speed;
		//dest = InitPos.X + maxDistance;
		dest = (InitPos + (MyVelocity.GetSafeNormal() * maxDistance)).X;
		start = InitPos.X;
		actual = loc.X;
		break;

	}
	//Check if we reached and "end point" and the platform has to change it's direction
	if(actual >= dest && !changeDir){
		changeDir = true;		
	}
	else if(actual <= start && changeDir){
		changeDir = false;
	}
	
	//New platform  position
	if(!changeDir){
		loc += (MyVelocity * DeltaTime);
	}else{
		loc -= (MyVelocity * DeltaTime);
	}

	//Fix Overshooting
	switch(dirAxis){
		case UP:
		case DOWN:
		if(!changeDir && (loc.Z > dest)) loc.Z = dest;
		if(changeDir && (loc.Z < start)) loc.Z = start;
		break;
		case RIGHT:
		case LEFT:
		if(!changeDir && (loc.Y > dest)) loc.Y = dest;
		if(changeDir && (loc.Y < start)) loc.Y = start;
		break;
		case FORWARD:
		case BACKWARD:
		default:
		if(!changeDir && (loc.X > dest)) loc.X = dest;
		if(changeDir && (loc.X < start)) loc.X = start;
		break;
	}

	//Move platform
	SetActorLocation(loc);
}

void AMovingPlatform::RotatePlatform(float DeltaTime){

	if(rotate){
		if(clockWise){
			AddActorLocalRotation(rotationVelocity * DeltaTime);
		}else{
			AddActorLocalRotation(-1 * rotationVelocity * DeltaTime);
		}   
	}
}

float AMovingPlatform::DistanceMoved() const{
	return FVector::Dist(InitPos,GetActorLocation());
}