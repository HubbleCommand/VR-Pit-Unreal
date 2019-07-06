// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "PitWorkHorse_AC.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class VRPITVA_API UPitWorkHorse_AC : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPitWorkHorse_AC();

	//Pit
	class UPitData;
	UPitData GetPitData(TArray<FString>);

	//Port
	int SetUpPort();
	int PortOutput(float duration, int32 output);

	//Hide/unhide numbers
	void ToggleActor(AActor* toHide, bool toggle);

	//Other
	UFUNCTION(BlueprintCallable)
	void ExecuteTrials();

	UFUNCTION(BlueprintCallable)
	void BuildPit(float depth, FString platform, bool falling_status);

	UFUNCTION(BlueprintCallable)
	void DestroyPit();

	UFUNCTION(BlueprintCallable)
	void Fade();

	UFUNCTION(BlueprintCallable)
	void CD1();
	UFUNCTION(BlueprintCallable)
	void CD2();
	UFUNCTION(BlueprintCallable)
	void CD3();
	UFUNCTION(BlueprintCallable)
	void CDAll();

	//Don't worry about intellisense warning, ResetPlayer() IS implemented, but in Blueprints
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Output")
	void ResetPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Pit;

	/*	UPROPERTY(EditAnywhere)
	ULightComponent* Light;	*/
	UPROPERTY(EditAnywhere)
	AActor* FloorDroppable;

	UPROPERTY(EditAnywhere)
	AActor* Platform_plank;

	UPROPERTY(EditAnywhere)
	AActor* Platform_track;

	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Floor Barrier"))
	AActor* FloorBarrier;
	
	UPROPERTY(EditAnywhere)
	AActor* Number3;

	UPROPERTY(EditAnywhere)
	AActor* Number2;

	UPROPERTY(EditAnywhere)
	AActor* Number1;
};
