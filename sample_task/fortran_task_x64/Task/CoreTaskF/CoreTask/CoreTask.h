// CoreTask.h : main header file for the CoreTask DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCoreTaskApp
// See CoreTask.cpp for the implementation of this class
//

class CCoreTaskApp : public CWinApp
{
public:
	CCoreTaskApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


////////////////////////////////////////////////////////////////////////////////////////////
// Description : enuSpace - plugin (sample)
//               This plugin library is made in Expansion & Universal Cooperation.  

// homepage    : https://expnuni.gitbooks.io/enuspace/content/
// Technical Support e-mail : master@enu-tech.co.kr
// Copyright (C) ENU Corporation, �̿����ֽ�ȸ��, ENU Co., Ltd
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

/////////////////////////////////////////////////////////////////////////////////
#define DEF_UNKNOWN								-1
#define DEF_INT									0
#define DEF_FLOAT								1
#define DEF_DOUBLE								2
#define DEF_BOOL								3
#define DEF_STRING								4
#define DEF_STRUCT								5
#define DEF_VARIABLE							6
#define DEF_OBJECT								7

#define TASK_TYPE_UNKNOWN						0			// Task�� Ÿ�� ���� (�˼����� Ÿ��)
#define TASK_TYPE_PROCESS						1			// Task�� Ÿ�� ����	(����ó���� Ÿ��)
#define TASK_TYPE_FLOW_COMPONENT_TOTAL			2			// Task�� Ÿ�� ����	(FLOW ������Ʈ ��ü ���� Ÿ��)
#define TASK_TYPE_FLOW_COMPONENT_PAGE			3			// Task�� Ÿ�� ����	(FLOW������Ʈ ������ ���� Ÿ��)
#define TASK_TYPE_FUNCTION_COMPONENT			4			// Task�� Ÿ�� ���� (�Լ��� ������Ʈ Ÿ��)


#define DEF_NAME_LEN							64
#define DEF_MAXTEXT_LEN							2048
#define DEF_LABELTEXT_LEN						1024


struct arrayInfo
{
	int size;
	int position;								// enuSpace ���� (added v3.15)
	wchar_t dimension[DEF_LABELTEXT_LEN];

public:arrayInfo()
{
	size = 0;
	position = 0;
	wcscpy_s(dimension, L"");
}
};

struct VariableStruct
{
	wchar_t name[DEF_NAME_LEN];
	int     type;
	void*   pValue;
	wchar_t strValue[DEF_MAXTEXT_LEN];
	arrayInfo array;

public:VariableStruct()
{
	wcscpy_s(name, L"");			
	type = DEF_UNKNOWN;
	pValue = NULL;
	wcscpy_s(strValue, L"N/A");
}
};

void InterfaceDataMapClear();
void SetArrayValue(std::string strVariable, void* pSrc, int iType, int iSize);
void SetReShapeArrayValue(std::string strVariable, void* pSrc, int iType, int iSize);		// enuSpace�� �޸� ����� �ٸ����, enuSpace�� �޸𸮸� ���Ҵ��� �� �����ϴ� �Լ�
double GetArrayValue(std::string strVariable);
void SetValue(std::string strVariable, double fValue);
double GetValue(std::string strVariable);
void PrintMessage(CString strMessage, CString strID=L"");
int GetArrayIndexFromDimension(CString strOrgDim, CString strDimension);