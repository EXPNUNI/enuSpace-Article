// CoreTask.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CoreTask.h"

#include "..\model.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 
//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CCoreTaskApp

BEGIN_MESSAGE_MAP(CCoreTaskApp, CWinApp)
END_MESSAGE_MAP()


// CCoreTaskApp construction

CCoreTaskApp::CCoreTaskApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCoreTaskApp object

CCoreTaskApp theApp;


// CCoreTaskApp initialization

CString g_strDllPath;
HANDLE g_hConsole = NULL;
CPtrArray *enuObject;
double g_DT;

BOOL CCoreTaskApp::InitInstance()
{
	CWinApp::InitInstance();

	HINSTANCE hInstance = AfxGetInstanceHandle();
	wchar_t szPath[MAX_PATH];
	GetModuleFileName(hInstance, szPath, MAX_PATH);

	wchar_t drive[MAX_PATH];               // 드라이브 명
	wchar_t dir[MAX_PATH];                 // 디렉토리 경로
	wchar_t fname[MAX_PATH];			   // 파일명
	wchar_t ext[MAX_PATH];                 // 확장자 명

	_wsplitpath_s(szPath, drive, dir, fname, ext);
	g_strDllPath.Format(L"%s%s", drive, dir);

	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);

		g_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitle(L"Fortran");
	}

	return TRUE;
}

int CCoreTaskApp::ExitInstance()
{
	::FreeConsole();
	return CWinApp::ExitInstance();
}
///////////////////////////////////////////////////////////////////////////////////////////
void PrintMessage(CString strMessage, CString strID = L"");
CString MBToWC(char * str);

///////////////////////////////////////////////////////////////////////////////////////////
extern "C"
{
	void _Message(char* pMessage);

	void TASK_MAIN_COM1(component1* pStruct);
	void TASK_MAIN_COM2(component2* pStruct);
	void TASK_INIT();
	void TASK_LOAD();
	void TASK_UNLOAD();
};
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// enuSpace interface function pointer.
void(*g_fcbSetValue)(wchar_t*, double) = NULL;
VariableStruct(*g_fcbGetValue)(wchar_t*) = NULL;
void(*g_fcbSetArrayValue)(wchar_t*, void*, int, int) = NULL;
void(*g_fcbSetReShapeArrayValue)(wchar_t*, void*, int, int) = NULL;
void(*g_fcbSetPinInterfaceVariable)(wchar_t*, void*, int, int) = NULL;
VariableStruct(*g_fcbGetArrayValue)(wchar_t*) = NULL;
void(*g_fcbPrintMessage)(wchar_t*, wchar_t*) = NULL;
//////////////////////////////////////////////////////////////////////////////////////////////
// enuSpace interface functions.
extern "C" __declspec(dllexport) void SetCallBack_SetValue(void fcbSetValue(wchar_t*, double));
extern "C" __declspec(dllexport) void SetCallBack_GetValue(VariableStruct fcbGetValue(wchar_t*));
extern "C" __declspec(dllexport) void SetCallBack_SetArrayValue(void fcbSetArrayValue(wchar_t*, void*, int, int));
extern "C" __declspec(dllexport) void SetCallBack_GetArrayValue(VariableStruct fcbGetArrayValue(wchar_t*));
extern "C" __declspec(dllexport) void SetCallBack_SetReShapeArrayValue(void fcbSetReShapeArrayValue(wchar_t*, void*, int, int));
extern "C" __declspec(dllexport) void SetCallBack_SetPinInterfaceVariable(void fcbSetPinInterfaceVariable(wchar_t*, void*, int, int));
extern "C" __declspec(dllexport) void SetCallBack_PrintMessage(void fcbPrintMessage(wchar_t*, wchar_t*));

extern "C" __declspec(dllexport) int GetTaskType();
extern "C" __declspec(dllexport) bool IsEnableTransfer(wchar_t* pFromType, wchar_t* pToType);
extern "C" __declspec(dllexport) bool IsTaskStopWhenModify();

extern "C" __declspec(dllexport) bool OnInit();
extern "C" __declspec(dllexport) bool OnLoad();
extern "C" __declspec(dllexport) bool OnUnload();
extern "C" __declspec(dllexport) bool OnTask(__int64 time);
extern "C" __declspec(dllexport) void OnModeChange(int iMode);
extern "C" __declspec(dllexport) void ExecuteFunction(wchar_t* pStrFunction);

extern "C" __declspec(dllexport) void OnEditComponent(wchar_t* pStrSymbolName, wchar_t* pStrID);
extern "C" __declspec(dllexport) void OnShowComponent(wchar_t* pStrSymbolName, wchar_t* pStrID);
extern "C" __declspec(dllexport) bool OnShowHelp(wchar_t* pStrSymbolName);

extern "C" __declspec(dllexport) void OnSetObjectArray(CPtrArray* Object);
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void SetCallBack_SetValue(void fcbSetValue(wchar_t*, double))
{
	g_fcbSetValue = fcbSetValue;
}

extern "C" __declspec(dllexport) void SetCallBack_GetValue(VariableStruct fcbGetValue(wchar_t*))
{
	g_fcbGetValue = fcbGetValue;
}

extern "C" __declspec(dllexport) void SetCallBack_SetArrayValue(void fcbSetArrayValue(wchar_t*, void*, int, int))
{
	g_fcbSetArrayValue = fcbSetArrayValue;
}

extern "C" __declspec(dllexport) void SetCallBack_GetArrayValue(VariableStruct fcbGetArrayValue(wchar_t*))
{
	g_fcbGetArrayValue = fcbGetArrayValue;
}

extern "C" __declspec(dllexport) void SetCallBack_SetReShapeArrayValue(void fcbSetReShapeArrayValue(wchar_t*, void*, int, int))
{
	g_fcbSetReShapeArrayValue = fcbSetReShapeArrayValue;
}

extern "C" __declspec(dllexport) void SetCallBack_SetPinInterfaceVariable(void fcbSetPinInterfaceVariable(wchar_t*, void*, int, int))
{
	g_fcbSetPinInterfaceVariable = fcbSetPinInterfaceVariable;
}

extern "C" __declspec(dllexport) void SetCallBack_PrintMessage(void fcbPrintMessage(wchar_t*, wchar_t*))
{
	g_fcbPrintMessage = fcbPrintMessage;
}

extern "C" __declspec(dllexport) void OnSetObjectArray(CPtrArray* Object)
{
	if (Object)	enuObject = Object;
}

extern "C" __declspec(dllexport) bool OnLoad()
{
	TASK_LOAD();
	return true;
}

extern "C" __declspec(dllexport) bool OnInit()
{
	try
	{
		if (g_fcbGetValue)
		{
			VariableStruct data;
			data = g_fcbGetValue(L"dt.model");
			if (data.type == DEF_DOUBLE)
				g_DT = *(double*)data.pValue;
		}
		// InitModel();
		TASK_INIT();
		return true;
	}
	catch (...)
	{

	}
	return false;
}

extern "C" __declspec(dllexport) bool OnTask(__int64 time)
{
	try
	{
		if (g_fcbGetValue)
		{
			VariableStruct data;
			data = g_fcbGetValue(L"dt.model");
			if (data.type == DEF_DOUBLE)
				g_DT = *(double*)data.pValue;
		}

		// TaskModel();			// C++ 함수 호출.

		for (int index = 0; index < enuObject->GetSize(); ++index)
		{
			EnuObject *pobj = (EnuObject *)(enuObject->GetAt(index));

			if (wcscmp(pobj->type, L"component1") == 0)
				TASK_MAIN_COM1((component1*)pobj);	// fortran 함수 호출.
			else if (wcscmp(pobj->type, L"component2") == 0)
				TASK_MAIN_COM2((component2*)pobj);	// fortran 함수 호출.
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

extern "C" __declspec(dllexport) bool OnUnload()
{
	TASK_UNLOAD();
	return true;
}

extern "C" __declspec(dllexport) void OnEditComponent(wchar_t* pStrSymbolName, wchar_t* pStrID)
{

}

extern "C" __declspec(dllexport) void OnShowComponent(wchar_t* pStrSymbolName, wchar_t* pStrID)
{

}

extern "C" __declspec(dllexport) void OnModeChange(int iMode)
{

}

extern "C" __declspec(dllexport) void ExecuteFunction(wchar_t* pStrFunction)
{

}

extern "C" __declspec(dllexport) bool OnShowHelp(wchar_t* pStrSymbolName)
{
	return true;
}

extern "C" __declspec(dllexport) int GetTaskType()
{
	return TASK_TYPE_OBJECTARRAY;
}

extern "C" __declspec(dllexport) bool IsEnableTransfer(wchar_t* pFromType, wchar_t* pToType)
{
	return true;
}

extern "C" __declspec(dllexport) bool IsTaskStopWhenModify()
{
	return true;
}
////////////////////////////////////////////////////////////////////////////
void PrintMessage(CString strMessage, CString strID)
{
	if (g_fcbPrintMessage)
	{
		strMessage = L"model->" + strMessage;
		g_fcbPrintMessage(strMessage.GetBuffer(0), strID.GetBuffer(0));
	}
}

CString MBToWC(char * str)
{
	wchar_t* strResult = new wchar_t[strlen(str) + 1];
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, strResult, (int)strlen(str) + 1);
	CString strReturn;
	strReturn = strResult;
	delete[] strResult;
	return strReturn;
}

void _Message(char* pMessage)
{
	PrintMessage(MBToWC(pMessage));
}