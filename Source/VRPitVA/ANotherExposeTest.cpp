// Fill out your copyright notice in the Description page of Project Settings.

#include "ANotherExposeTest.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

UANotherExposeTest::UANotherExposeTest()	//(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	/*
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
	*/
};
/*
bool VerifyElements(UANotherExposeTest data)
{
	float expected = data.Falling.Num() + data.Platforms.Num() + data.Lengths.Num() +
		data.Widths.Num() + data.Spaces.Num() + data.DurationPre.Num() +
		data.DurationExposure.Num() + data.DurationPost.Num() + data.Depth.Num();
	expected = expected / 9;
	if (floor(expected) == expected)	//floor can be used to check if float is whole number
	{
		UE_LOG(LogTemp, Warning, TEXT("All Pit Data elements are the same length!"));
		if (data.Falling.Num() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

UANotherExposeTest& UANotherExposeTest::GetData(TArray<FString> lines)
{
	UANotherExposeTest data;
	int a = 0;
	int trials = lines.Num() - 1;
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

TArray<FString> UANotherExposeTest::GetText(FString text)
{
	FString Result;
	FString godpleaseohy = "C:/Users/Sasha Poirier/Desktop/test.txt";
	FString path = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	godpleaseohy = path + "test.txt";
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), *path);
	const TCHAR * Filename = *godpleaseohy;
	uint32 VerifyFlags = 0;
	if (FFileHelper::LoadFileToString(Result, Filename))
	{
		UE_LOG(LogTemp, Warning, TEXT("Huzzah! Got file contents! \n Contents: %s"), *Result);
		TArray<FString> Lines;
		Result.ParseIntoArrayLines(Lines);
		UANotherExposeTest Pits;
		Pits = GetData(Lines);

		if (Pits.VerifyElements())
		{

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Oops! Couldn't properly store the pit data, or the file wasn't written properly!"));
		}
	}
	else { UE_LOG(LogTemp, Error, TEXT("Could not load trial data file!")); }
}
*/