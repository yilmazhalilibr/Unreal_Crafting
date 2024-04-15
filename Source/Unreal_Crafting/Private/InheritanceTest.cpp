// Fill out your copyright notice in the Description page of Project Settings.


#include "InheritanceTest.h"


InheritanceTest::InheritanceTest(string name, string surname, int age)
{
}

InheritanceTest::~InheritanceTest()
{
}

string InheritanceTest::GetProperties()
{
	return name;
}

class InheritanceChild : public InheritanceTest
{
private:
	int ChildTier;
	string ChildID;

	InheritanceChild(int ChildTier = 0, string ChildID = "0") : InheritanceTest(name, surname, age)
	{};

	string GetChildID()
	{
		return ChildID;
	};

};