// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include "Engine/Engine.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("TestActor BeginPlay"));
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1, 5.f, FColor::Green,
			TEXT("Hello from Test Module! (TestActor Spawned)"));
	}
}


