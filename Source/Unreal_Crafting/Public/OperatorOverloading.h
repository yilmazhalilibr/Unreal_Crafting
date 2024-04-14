// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class UNREAL_CRAFTING_API OperatorOverloading
{
public:
	OperatorOverloading(int r = 0, int s = 0);
	~OperatorOverloading();

private:
	int Reel;
	int Virtual;

public:
	int GetReel()
	{
		return Reel;
	}
	int GetVirtual()
	{
		return Virtual;
	}
	void SetReel(int reel)
	{
		Reel = reel;
	}
	void SetVirtual(int _virtual)
	{
		Virtual = _virtual;
	}
	void Print();

	OperatorOverloading operator+(OperatorOverloading& OO);
};
