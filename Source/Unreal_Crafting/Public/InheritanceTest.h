// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <unordered_map>

using namespace std;
/**
 *
 */
class UNREAL_CRAFTING_API InheritanceTest
{
protected:
	string name;
	string surname;
	int age;
public:
	InheritanceTest(string name = "Default", string surname = "Defaults", int age = 0);
	~InheritanceTest();

	string GetProperties();

};
