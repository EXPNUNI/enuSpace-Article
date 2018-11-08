#include "stdafx.h"
#include "..\model.h"


void InitModel()
{

}

void TaskModel()
{
	for (int index = 0; index < enuObject->GetSize(); ++index)
	{
		EnuObject *pObj = (EnuObject *)(enuObject->GetAt(index));

		if (wcscmp(pObj->type, L"component1") == 0)
			((component1*)pObj)->Simulation();
		else if (wcscmp(pObj->type, L"component2") == 0)
			((component2*)pObj)->Simulation();
	}
}

void component1::Simulation(void)
{

}

void component2::Simulation(void)
{
	
}
