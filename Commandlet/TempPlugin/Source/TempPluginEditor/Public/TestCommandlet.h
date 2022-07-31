// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "TestCommandlet.generated.h"

/**
 * 
 */
UCLASS()
class UTestCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params) override;

protected:
	void ReadInputFile(const FString &InputPath);
	void WriteOutputFIle(const FString& OutputPath, const FString& OutpotC);

};
