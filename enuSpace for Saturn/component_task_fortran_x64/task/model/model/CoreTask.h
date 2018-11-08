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
	virtual int ExitInstance();
};


////////////////////////////////////////////////////////////////////////////////////////////
// Description : enuSpace - plugin (sample)
//               This plugin library is made in Expansion & Universal Cooperation.  

// homepage    : https://expnuni.gitbooks.io/enuspace/content/
// Technical Support e-mail : master@enu-tech.co.kr
// Copyright (C) ENU Corporation, 이엔유주식회사, ENU Co., Ltd
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////
