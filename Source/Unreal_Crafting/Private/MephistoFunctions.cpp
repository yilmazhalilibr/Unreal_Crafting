// Fill out your copyright notice in the Description page of Project Settings.


#include "MephistoFunctions.h"

MephistoFunctions::MephistoFunctions() : constDeger(555)
{

}
MephistoFunctions::MephistoFunctions(int firstValue, float& testActorValue)
{
	CalculateAllCounts(firstValue, firstValue + 2, firstValue + 3, testActorValue);

}


MephistoFunctions::~MephistoFunctions()
{
}

void MephistoFunctions::CalculateAllCounts(int x, float y, double z, float& result)
{
	y = x * z;
	y *= y;
	result = y;
	//LastProcessedValue = constDeger;

}



