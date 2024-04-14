// Fill out your copyright notice in the Description page of Project Settings.


#include "OperatorOverloading.h"
#include <iostream>

using namespace std;

OperatorOverloading::OperatorOverloading(int r, int s)
{
	Reel = r;
	Virtual = s;

}

OperatorOverloading::~OperatorOverloading()
{
}


void OperatorOverloading::Print()
{
	if (Virtual > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reel : %d + Virtual : %di"), Reel, Virtual);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reel : %d + Virtual : %di"), -Reel, -Virtual);

	}
}

OperatorOverloading OperatorOverloading::operator+(OperatorOverloading& OO)
{
	OperatorOverloading total;
	total.SetReel(Reel + OO.Reel);
	total.SetVirtual(Virtual + OO.Virtual);

	return total;
}

