// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerTest.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"

void ATimerTest::FShittyFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Tester Worked!"));
}

void ATimerTest::FUCKOFF()
{
	FTimerHandle TimerHandlePre;
	FTimerDelegate TimerDelPre;
	TimerDelPre.BindUFunction(this, FName("FShittyFunctionBuildPit"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandlePre, TimerDelPre, 10, false);
}

// Sets default values
ATimerTest::ATimerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimerTest::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Tester Reporting!"));
	Super::BeginPlay();
	BCanStartTrials = true;
}

// Called every frame
void ATimerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (BCanStartTrials)
	{
		UE_LOG(LogTemp, Warning, TEXT("Timer Tester starting timer maybe..."));
		BCanStartTrials = false;
		//FUCKOFF();
		/*
		FTimerHandle TimerHandlePre;
		FTimerDelegate TimerDelPre;
		TimerDelPre.BindUFunction(this, FName("FShittyFunctionBuildPit"));
		//GetWorld()->GetTimerManager().SetTimer(TimerHandlePre, TimerDelPre, 10, false);
		GetWorldTimerManager.SetTimer(TimerHandlePre, this, &ATimerTest::FShittyFunction, 10, false);
		*/
	}
}

