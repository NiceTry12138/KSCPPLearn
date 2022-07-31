// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ToolFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TEMPPLUGINEDITOR_API UToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Util")
	static FString TestFunc(const FString& FilePathRef, FString TargetBoneName = TEXT("root"));

	UFUNCTION(BlueprintCallable, Category = "Util")
	static bool SaveToFile(FString Dir, FString Name, FString Text, bool Overwrite);
};
