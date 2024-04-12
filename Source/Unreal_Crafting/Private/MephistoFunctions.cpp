// Fill out your copyright notice in the Description page of Project Settings.


#include "MephistoFunctions.h"

MephistoFunctions::MephistoFunctions()
{
}

MephistoFunctions::~MephistoFunctions()
{
}

void MephistoFunctions::CalculateAllCounts(int x, float y, double z, float& result)
{
	y = x * z;
	y *= y;
	result = y;
	LastProcessedValue = result;
}



