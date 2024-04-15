// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InheritanceTest.h"
/**
 *
 */
class UNREAL_CRAFTING_API MephistoFunctions
{
public:
	MephistoFunctions();
	MephistoFunctions(int firstValue, float& testActorValue);

	~MephistoFunctions();

	//InheritanceTest* ChildTest = new InheritanceChild(52,"0");
	

	int const constDeger = 25;

	float LastProcessedValue;

	void CalculateAllCounts(int x, float y, double z, float& globalValue);



};
