#pragma once

#include "GlobalHeader.h"
#include <string>

class component
{
public:
	component()
	{
		m_up = false;
		m_down = false;
		m_output = 0;
		memset(m_output_d, 0, sizeof(double) * 10);
	}

	~component();

	bool SetInitValue(std::string strVar, VariableStruct* pData)
	{
		if (strVar == "m_output" && pData->type == DEF_INT)				m_output = *(int*)pData->pValue;
		else if (strVar == "m_up" && pData->type == DEF_BOOL)			m_up = *(bool*)pData->pValue;
		else if (strVar == "m_down" && pData->type == DEF_BOOL)			m_down = *(bool*)pData->pValue;
		else if (strVar == "m_output_d" && pData->type == DEF_DOUBLE)	memcpy(m_output_d, (double*)pData->pValue, sizeof(double) * 10);
		else	return false;
		return true;
	}

	bool SetInterface(const wchar_t* id, void fcbSetPinInterfaceVariable(wchar_t*, void*, int, int))
	{
		CString strVariable;
		strVariable.Format(L"%s.%s", id, L"m_output");		fcbSetPinInterfaceVariable(strVariable.GetBuffer(0), &m_output, DEF_INT, 0);

		strVariable.Format(L"%s.%s", id, L"m_up");			fcbSetPinInterfaceVariable(strVariable.GetBuffer(0), &m_up, DEF_BOOL, 0);
		strVariable.Format(L"%s.%s", id, L"m_down");		fcbSetPinInterfaceVariable(strVariable.GetBuffer(0), &m_down, DEF_BOOL, 0);

		strVariable.Format(L"%s.%s", id, L"m_output_d");	fcbSetPinInterfaceVariable(strVariable.GetBuffer(0), &m_output_d, DEF_DOUBLE, 10);
		
		return true;
	}

	bool m_up;
	bool m_down;

	int m_output;

	double m_output_d[10];

	///////////////////////////////////////////////////////////////////////////
	void Simulation(void);
	///////////////////////////////////////////////////////////////////////////
};

