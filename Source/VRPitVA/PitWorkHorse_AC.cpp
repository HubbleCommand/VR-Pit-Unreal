// Fill out your copyright notice in the Description page of Project Settings.

#include "PitWorkHorse_AC.h"
#include <iostream>
#include <stdio.h>
#include <string>
//NEED #include <windows.h>, equivalent in UE4 is:
#include "Windows/MinWindows.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformProcess.h"
#include "Async.h"
#include "Runtime/Engine/Classes/Engine/PointLight.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"

class UPitWorkHorse_AC::UPitData
{
public:
	int NumberOfTrials;
	TArray<bool> Falling;
	TArray<FString> Platforms;
	TArray<float> Lengths;
	TArray<float> Widths;
	TArray<float> Spaces;
	TArray<float> DurationPre;
	TArray<float> DurationExposure;
	TArray<float> DurationPost;
	TArray<float> Depth;
	
	bool VerifyElements()	{
		float expected = Falling.Num() + Platforms.Num() + Lengths.Num() +
			Widths.Num() + Spaces.Num() + DurationPre.Num() +
			DurationExposure.Num() + DurationPost.Num() + Depth.Num();
		expected = expected/ 9;
		if (floor(expected) == expected)	{
			UE_LOG(LogTemp, Warning, TEXT("All Pit Data elements are the same length!"));
			if (Falling.Num() > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else	{
			return false;
		}
	}

	void LogElements()	{
	FString result = "";
		int length = Lengths.Num();
		for (int q = 0; q <= (length - 1); q++) {
			if (Falling[q]) { result += "true, "; }
			else { result += "false, "; }		}
		UE_LOG(LogTemp, Warning, TEXT("Falling: %s"), *result);
		UE_LOG(LogTemp, Warning, TEXT("Platforms: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(Lengths[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("Lengths: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(Widths[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("Widths: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(DurationPre[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("Spaces: %s"), *result);
		UE_LOG(LogTemp, Warning, TEXT("DurationPre: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(DurationExposure[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("DurationExposure: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(DurationPost[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("DurationPost: %s"), *result);
	result = "";
		for (int q = 0; q <= (length - 1); q++) {
			result += (FString::SanitizeFloat(Depth[q]));
			result += ", ";		}
		UE_LOG(LogTemp, Warning, TEXT("Depth: %s"), *result);
	}
};

UPitWorkHorse_AC::UPitData pitdata;

UPitWorkHorse_AC::UPitData UPitWorkHorse_AC::GetPitData(TArray<FString> lines)
{
	UPitData data;
	int a = 0;
	int trials = lines.Num()-1;
	data.NumberOfTrials = trials;
	for (a = 0; a <= trials; a += 1)
	{
		TArray<FString> line;
		lines[a].ParseIntoArray(line, TEXT(","), true);
		
		//Adds if falling is enabled or not
		if (line[0] == "true") { data.Falling.Add(true); }
		else if (line[0] == "false") { data.Falling.Add(false); }
		else { data.Falling.Add(false); }

		//Adds type of platform
		if (line[1] == "plank") { data.Platforms.Add("plank"); }
		else if (line[1].Contains("track")) { data.Platforms.Add("track"); }
		else { data.Platforms.Add("plank"); }

		//Adds platform characteristics
		data.Lengths.Add(FCString::Atof(*line[2]));
		data.Widths.Add(FCString::Atof(*line[3]));
		data.Spaces.Add(FCString::Atof(*line[4]));

		//Adds durations
		data.DurationPre.Add(FCString::Atof(*line[5]));
		data.DurationExposure.Add(FCString::Atof(*line[6]));
		data.DurationPost.Add(FCString::Atof(*line[7]));

		//Adds pit depth
		float depth = FCString::Atof(*line[8]);
		data.Depth.Add(depth);
	}
	return data;
}

// Sets default values for this component's properties
UPitWorkHorse_AC::UPitWorkHorse_AC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPitWorkHorse_AC::ToggleActor(AActor* toHide, bool toggle) {
	toHide->SetActorHiddenInGame(!toggle);
	toHide->SetActorEnableCollision(toggle);
	toHide->SetActorTickEnabled(toggle);
}
void UPitWorkHorse_AC::CD1() {
	ToggleActor(Number1, true);
	ToggleActor(Number2, false);
	ToggleActor(Number3, false);
}
void UPitWorkHorse_AC::CD2() {
	ToggleActor(Number1, false);
	ToggleActor(Number2, true);
	ToggleActor(Number3, false);
}
void UPitWorkHorse_AC::CD3() {
	ToggleActor(Number1, false);
	ToggleActor(Number2, false);
	ToggleActor(Number3, true);
}
void UPitWorkHorse_AC::CDAll() {
	ToggleActor(Number1, false);
	ToggleActor(Number2, false);
	ToggleActor(Number3, false);
}
void UPitWorkHorse_AC::ExecuteTrials()
{
	int trials = pitdata.NumberOfTrials;
	int a = 0;

	float sum_time = 0;
	//Trials
	for (a = 0; a <= trials; a++)	//for each trials
	{
		//Countdown timers
		//3
		FTimerHandle TimerHandlePre3;
		FTimerDelegate TimerDelPre3;
		TimerDelPre3.BindUFunction(this, FName("CD3"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePre3, TimerDelPre3, (pitdata.DurationPre[a] + sum_time - 3), false);

		FTimerHandle TimerHandlePre2;
		FTimerDelegate TimerDelPre2;
		TimerDelPre2.BindUFunction(this, FName("CD2"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePre2, TimerDelPre2, (pitdata.DurationPre[a] + sum_time - 2), false);

		FTimerHandle TimerHandlePre1;
		FTimerDelegate TimerDelPre1;
		TimerDelPre1.BindUFunction(this, FName("CD1"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePre1, TimerDelPre1, (pitdata.DurationPre[a] + sum_time - 1), false);

		FTimerHandle TimerHandlePreA;
		FTimerDelegate TimerDelPreA;
		TimerDelPreA.BindUFunction(this, FName("CDAll"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePreA, TimerDelPreA, (pitdata.DurationPre[a] + sum_time), false);

		//Build pit timers
		FTimerHandle TimerHandlePre;
		FTimerDelegate TimerDelPre;
		TimerDelPre.BindUFunction(this, FName("BuildPit"), pitdata.Depth[a], pitdata.Platforms[a], pitdata.Falling[a]);
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePre, TimerDelPre, (pitdata.DurationPre[a] + sum_time), false);
		sum_time += pitdata.DurationPre[a];

		//fade floor back in
		FTimerHandle TimerHandleFade;
		FTimerDelegate TimerDelFade;
		TimerDelFade.BindUFunction(this, FName("Fade"));
		UE_LOG(LogTemp, Warning, TEXT("Got here"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandleFade, TimerDelFade, (pitdata.DurationExposure[a] + sum_time - 1), false);

		//destroy pit
		FTimerHandle TimerHandleExp;
		FTimerDelegate TimerDelExp;
		TimerDelExp.BindUFunction(this, FName("DestroyPit"));
		GetWorld()->GetTimerManager().SetTimer(TimerHandleExp, TimerDelExp, (pitdata.DurationExposure[a] + sum_time), false);
		sum_time += pitdata.DurationExposure[a];

		//port output
		sum_time += pitdata.DurationPost[a];
	}
}

void UPitWorkHorse_AC::Fade() {
	FOutputDeviceNull ar;
	FloorBarrier->CallFunctionByNameWithArguments(TEXT("FadeFloor"), ar, NULL, true);
}

int UPitWorkHorse_AC::PortOutput(float duration, int32 output)
{
	output = 0b0000; //output is 0
	output = 0b0010; //output is 2
	output = 0b0100; //output is 4
	output = 0b1000; //output is 8

	//send and chek if good

	return 0;
}

void UPitWorkHorse_AC::BuildPit(float depth, FString platform, bool falling_status)
{
	//sets pit floor
	FloorDroppable->SetActorLocation(FVector(1000.0f, 0.0f, ((-depth * 100) + 20.0)));

	//sets pit scale
	Pit->SetActorScale3D(FVector(4.9f, 4.8f, depth));

	//builds pit plank
	if (platform == "plank")		{Platform_plank->SetActorLocation(FVector(500.0f, 0.0f, 20.0f));}
	else if (platform == "track")	{Platform_track->SetActorLocation(FVector(500.0f, 0.0f, 20.0f));}
	else							{Platform_plank->SetActorLocation(FVector(500.0f, 0.0f, 20.0f));}

	//puts pit lights
	/* int number_of_lights = (depth / 10);
	for (int q = 0; q < number_of_lights; q++)
	{
		FVector Location(1000.0f, 0.0f, -((q*1000)+500.0f));
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		APointLight* light = GetWorld()->SpawnActor<APointLight>(Location, Rotation, SpawnInfo);
	}	*/

	//enables/disables falling
	FOutputDeviceNull ar;
	FloorBarrier->CallFunctionByNameWithArguments(TEXT("FadeFloor"), ar, NULL, true);
	if (falling_status) {
		FloorBarrier->SetActorEnableCollision(false);
	}
	else {
		FloorBarrier->SetActorEnableCollision(true);
	}

	//FadableF
}

void UPitWorkHorse_AC::DestroyPit()
{
	//reset player position (vertically)
	FOutputDeviceNull ar;
	GetWorld()->GetFirstPlayerController()->GetPawn()->CallFunctionByNameWithArguments(TEXT("ResetPositionEvent"), ar, NULL, true);

	//sets pit floor and scale
	FloorDroppable->SetActorLocation(FVector(1000.0f, 0.0f, 0.0f));
	Pit->SetActorScale3D(FVector(4.9f, 4.8f, 0.f));
	Platform_plank->SetActorLocation(FVector(500.0f, 0.0f, 500.0f));
	Platform_track->SetActorLocation(FVector(500.0f, 0.0f, 500.0f));

	//Reset floor barrier collision box
	FloorBarrier->SetActorEnableCollision(true);

	//FloorBarrier->CallFunctionByNameWithArguments(TEXT("FadeFloor"), ar, NULL, true);
}

// Called when the game starts
void UPitWorkHorse_AC::BeginPlay()
{
	Super::BeginPlay();

	//Gets the owner
	Pit = GetOwner();

	FString Result;
	//FString godpleaseohy = "C:/Users/Sasha Poirier/Desktop/test.txt";
	FString godpleaseohy = "C:/Users/Sasha Poirier/Desktop/test.txt";
	FString path = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	godpleaseohy = path + "Content/ExtraDat/test.txt";
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *path);
	const TCHAR * Filename = *godpleaseohy;
	uint32 VerifyFlags = 0;
	if (FFileHelper::LoadFileToString(Result, Filename))	{
		UE_LOG(LogTemp, Warning, TEXT("Huzzah! Got file contents! \n Contents: %s"), *Result);
		TArray<FString> Lines;
		Result.ParseIntoArrayLines(Lines);
		UPitData Pits;
		Pits = GetPitData(Lines);
		
		if (Pits.VerifyElements())	{
			pitdata = Pits;
			Pits.LogElements();
			//ExecuteTrials();
		}
		else    {UE_LOG(LogTemp, Warning, TEXT("Oops! Couldn't properly store the pit data, or the file wasn't written properly!"));}
	}
	else { UE_LOG(LogTemp, Error, TEXT("Could not load trial data file!")); }
	//Hide numbers
	ToggleActor(Number1, false);
	ToggleActor(Number2, false);
	ToggleActor(Number3, false);
}

// Called every frame
/*
void UPitWorkHorse_AC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FOR THE TIME BEING
	//all the waiting is done here, as I can't for the life of me find a real equivalent to Coroutines in Unreal

}*/


int UPitWorkHorse_AC::SetUpPort() {
	HANDLE commPort;
	//DWORD read;
	DWORD written;
	LPCWSTR port = L"\\\\.\\COM3";
	commPort = CreateFile
	(
		port,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (commPort == INVALID_HANDLE_VALUE)
	{
		//std::cout << "Error opening serial port! \n\n";
		UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n"));
		return -1;
	}
	else { std::cout << "Set up serial port... \n\n"; }

	//Setting DCB Settings (rate, parity, data, etc.)
	DCB dcbSerialParams;
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(commPort, &dcbSerialParams))
	{
		//std::cout << "Error getting comm state!\n";
		UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n"));
	}
	if (!BuildCommDCB(L"baud=9600 parity=n data=8 stop=1", &dcbSerialParams))
	{
		//std::cout << "Error building comm state!\n";
		UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n"));
	}
	if (!SetCommState(commPort, &dcbSerialParams))
	{
		//std::cout << "Error setting up DCB!\n";
		UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n"));
		return -1;
	}
	else { std::cout << "Set up DCB... \n\n"; }

	//Setting Timeouts
	COMMTIMEOUTS commTimeOut;
	commTimeOut.ReadIntervalTimeout = 3;
	commTimeOut.ReadTotalTimeoutMultiplier = 5;
	commTimeOut.ReadTotalTimeoutConstant = 2;
	commTimeOut.WriteTotalTimeoutMultiplier = 3;
	commTimeOut.WriteTotalTimeoutMultiplier = 2;
	if (!SetCommTimeouts(commPort, &commTimeOut))
	{
		//std::cout << "Error setting Timeouts!\n";
		UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n"));
		return -1;
	}
	else { /*std::cout << "Set up timeouts...\n\n";*/ UE_LOG(LogTemp, Error, TEXT("Error opening serial port! \n\n")); }


	//Sending Data
	if (WriteFile(
		commPort,
		"hello\n",
		sizeof("hello\n"),
		&written,
		NULL
	) == 0) {
		std::cout << "Sent!\n";
	}
	else { std::cout << "Error sending!";		return -1; }

	return 0;
}
