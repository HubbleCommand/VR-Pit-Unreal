// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"

#include "ANotherExposeTest.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class VRPITVA_API UANotherExposeTest : public UObject
{
	
	GENERATED_BODY()
public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stuff")
	//TArray<bool> Falling;

	UANotherExposeTest();
	/*
	TArray<FString> Platforms;
	TArray<float> Lengths;
	TArray<float> Widths;
	TArray<float> Spaces;
	TArray<float> DurationPre;
	TArray<float> DurationExposure;
	TArray<float> DurationPost;
	TArray<float> Depth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stuff")
	FString trialPath;
	
	UFUNCTION(BlueprintCallable, Category = "Stuff")
	UANotherExposeTest& GetData(TArray<FString>);
	

	UFUNCTION(BlueprintCallable, Category = "Stuff")
		bool VerifyElements(UANotherExposeTest data);

	UFUNCTION(BlueprintCallable, Category = "Stuff")
		TArray<FString> GetText(FString text);

	UFUNCTION(BlueprintCallable, Category = "Stuff")
		UANotherExposeTest& GetData(TArray<FString>);

	UANotherExposeTest(const FObjectInitializer& ObjectInitializer);

	*/
};
