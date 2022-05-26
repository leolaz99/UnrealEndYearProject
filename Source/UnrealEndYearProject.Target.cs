// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealEndYearProjectTarget : TargetRules
{
	public UnrealEndYearProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.Add("UnrealEndYearProject"); 
		ExtraModuleNames.Add("LLAIModule");
	}
}
