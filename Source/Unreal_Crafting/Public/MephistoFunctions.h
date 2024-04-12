// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class UNREAL_CRAFTING_API MephistoFunctions
{
public:
	MephistoFunctions();
	~MephistoFunctions();

	float LastProcessedValue;

	void CalculateAllCounts(int x, float y, double z, float& globalValue);

};
