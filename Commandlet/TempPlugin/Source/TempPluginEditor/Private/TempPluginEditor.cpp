// Copyright Epic Games, Inc. All Rights Reserved.

#include "TempPluginEditor.h"
#include "Modules//ModuleManager.h"
#include "PropertyEditorModule.h"

#include "CustomSelectorCustomization.h"
#define LOCTEXT_NAMESPACE "FTempPluginEditorModule"

void FTempPluginEditorModule::StartupModule()
{

}

void FTempPluginEditorModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTempPluginEditorModule, TempPluginEditor)