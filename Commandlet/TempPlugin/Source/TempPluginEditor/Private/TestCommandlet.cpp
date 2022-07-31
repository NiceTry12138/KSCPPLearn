// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCommandlet.h"
#include "Misc/FileHelper.h"
#include "AssetToolsModule.h"
#include "ToolFunctionLibrary.h"
//#include "AIBlueprintFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(TestLog, Log, All)

int32 UTestCommandlet::Main(const FString& Params) {
	//FModuleManager::LoadModuleChecked<CoreUObject>(FName("CoreUObject"));

	FString InputFilePath;
	FString OutputFilePath;

	FParse::Value(*Params, TEXT("InputFilePath="), InputFilePath);
	FParse::Value(*Params, TEXT("OutputFilePath="), OutputFilePath);

	UE_LOG(TestLog, Display, TEXT("InputFilePath:%s"), *InputFilePath);
	UE_LOG(TestLog, Display, TEXT("OutputFilePath:%s"), *OutputFilePath);

	//auto JSFile = TestFunc(InputFilePath);
	//SaveToFile(OutputFilePath, TEXT("Anim.json"), JSFile, true);

	auto JSFile = UToolFunctionLibrary::TestFunc(InputFilePath);
	UToolFunctionLibrary::SaveToFile(OutputFilePath, TEXT("Anim.json"), JSFile, true);

	return 0;
}

void UTestCommandlet::ReadInputFile(const FString& InputPath)
{
	static const FName NAME_AssetTools = "AssetTools";
	auto AssetTools = &FModuleManager::GetModuleChecked<FAssetToolsModule>(NAME_AssetTools).Get();
}

void UTestCommandlet::WriteOutputFIle(const FString& OutputPath, const FString& OutpotContent)
{

}
