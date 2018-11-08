#pragma once

#include "..\model\model\GlobalHeader.h"
#include <string>
#include <vector>
#include <afxcoll.h>
#include "EnuObj.h"

#ifndef _MODEL_HEADER__
#define _MODEL_HEADER__

extern CPtrArray *enuObject;
extern double g_DT;

#pragma pack(push, 1) 

struct component1 : EnuObject
{
	int iCount;
	double fValue;
	double fArray[5][10];
	component1()
	{
		iCount = 0;
		fValue = 0;
	}
	void Simulation(void);
};
struct component2 : EnuObject
{
	int input;
	int output;
	component2()
	{
		input = 0;
		output = 0;
	}
	void Simulation(void);
};
#pragma pack(pop) 

///////////////////////////////////////////////////////////////////////////
void InitModel();
void TaskModel();
///////////////////////////////////////////////////////////////////////////


#endif