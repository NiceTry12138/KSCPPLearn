// Fill out your copyright notice in the Description page of Project Settings.

#include "ToolFunctionLibrary.h"
#include "Animation/AnimSequence.h"
#include "UObject/SoftObjectPath.h"

DEFINE_LOG_CATEGORY_STATIC(TestPluginLog, Log, All)

// AnimSequence'/Game/Blueprint/MM_Idle.MM_Idle'
FString UToolFunctionLibrary::TestFunc(const FString &FilePathRef, FString TargetBoneName)
{
	FStringAssetReference AnimPath = FilePathRef;
	UAnimSequence *Anim = Cast<UAnimSequence>(AnimPath.TryLoad());
	if (!IsValid(Anim))
	{
		UE_LOG(TestPluginLog, Display, TEXT("Anim Is Null"));
		return TEXT("");
	}
	UE_LOG(TestPluginLog, Display, TEXT("Anim Name : %s"), *Anim->GetName());
	auto SelInfoArr = Anim->GetResampledTrackData();
	// һ����˵��һ�����Ǹ��ڵ�
	FRawAnimSequenceTrack AnimSequenceTrack;
	bool bIsFind = false;
	for (int i = 0; i < SelInfoArr.Num(); ++i)
	{
		if (SelInfoArr[i].Name.IsEqual(FName(*TargetBoneName)))
		{
			bIsFind = true;
			AnimSequenceTrack = SelInfoArr[i].InternalTrackData;
		}
	}
	float TimeDelay = 1.0f / Anim->GetFrameRate();
	FString Output = TEXT("[\n{\n");
	Output.Append(TEXT("\"path\" : \""));
	Output.Append(Anim->GetFullName());
	Output.Append(TEXT("\",\n"));
	Output.Append(TEXT("\"animName\" : \""));
	Output.Append(Anim->GetName());
	Output.Append(TEXT("\",\n"));
	Output.Append(TEXT("\"data\" : [\n"));
	for (int i = 0; i < AnimSequenceTrack.PosKeys.Num(); ++i)
	{
		FVector3f PosKeys = AnimSequenceTrack.PosKeys[i];
		FQuat4f RotKeys = AnimSequenceTrack.RotKeys[i];
		FVector3f ScaleKeys = AnimSequenceTrack.ScaleKeys[i];
		Output.Append(TEXT("{\n"));
		Output.Append(FString::Printf(TEXT("\"time\": %f,\n"), TimeDelay * (i + 1)));
		Output.Append(FString::Printf(TEXT("\"x\": %f,\n"), PosKeys.X));
		Output.Append(FString::Printf(TEXT("\"y\": %f,\n"), PosKeys.Y));
		Output.Append(FString::Printf(TEXT("\"z\": %f,\n"), PosKeys.Z));
		Output.Append(FString::Printf(TEXT("\"yaw\": %f\n"), RotKeys.Rotator().Yaw));
		Output.Append(TEXT("},\n"));
	}
	Output.Append("]\n}\n]");
	return Output;
	// SaveToFile(TEXT("E:/1_Projects_/UnrealProject/EmptyUnrealProject"), TEXT("Depth.json"), Output, true);
}

/**
 * @brief 比较赞同王海宇的写法 不过本质上都是拿到了UAnimSequence对象
 * UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UAnimSequence::StaticClass(), false, GIsEditor);
 * ObjectLibrary->LoadAssetDataFromPath(Path);
 */

bool UToolFunctionLibrary::SaveToFile(FString Dir, FString Name, FString Text, bool Overwrite)
{
	IPlatformFile &F = FPlatformFileManager::Get().GetPlatformFile();
	if (!F.DirectoryExists(*Dir))
	{
		F.CreateDirectoryTree(*Dir);
		if (!F.DirectoryExists(*Dir))
		{
			return false;
		}
	}
	Dir += "\\";
	Dir += Name;
	if (!Overwrite)
	{
		if (F.FileExists(*Dir))
		{
			return false;
		}
	}
	return FFileHelper::SaveStringToFile(Text, *Dir);
}