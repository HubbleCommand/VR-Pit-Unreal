// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VRPit_GI_CPP.generated.h"

/**
 * 
 */
UCLASS()
class VRPITVA_API UVRPit_GI_CPP : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VRPitGI)
	int32 InterLevelPersistentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VRPitGI)
	FString TrialDataFilePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VRPitGI)
	FString Port;
	
};
