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

#include <string>

////////////////////////////////////////////////////////////////////////////////////////////
// Description : enuSpace - plugin (cedmcs)
//               This plugin library is made in Expansion & Universal Cooperation.  

// homepage    : https://expnuni.gitbooks.io/enuspace/content/
// Technical Support e-mail : master@enu-tech.co.kr
// Copyright (C) ENU Corporation, 이엔유주식회사, ENU Co., Ltd
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////



void InterfaceDataMapClear();
void SetArrayValue(std::string strVariable, void* pSrc, int iType, int iSize);
void SetReShapeArrayValue(std::string strVariable, void* pSrc, int iType, int iSize);		// enuSpace의 메모리 사이즈가 다른경우, enuSpace의 메모리를 재할당후 값 복사하는 함수
double GetArrayValue(std::string strVariable);
void SetValue(std::string strVariable, double fValue);
double GetValue(std::string strVariable);
void PrintMessage(CString strMessage, CString strID=L"");
int GetArrayIndexFromDimension(CString strOrgDim, CString strDimension);