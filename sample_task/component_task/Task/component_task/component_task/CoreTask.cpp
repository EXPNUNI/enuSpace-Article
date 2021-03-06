// CoreTask.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CoreTask.h"

#include "component.h"

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
FILE* m_FileData = NULL;

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

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////
void(*g_fcbSetValue)(wchar_t*, double) = NULL;
VariableStruct (*g_fcbGetValue)(wchar_t*) = NULL;
void(*g_fcbSetArrayValue)(wchar_t*, void*, int, int) = NULL;
void(*g_fcbSetReShapeArrayValue)(wchar_t*, void*, int, int) = NULL;
void(*g_fcbSetPinInterfaceVariable)(wchar_t*, void*, int, int) = NULL;
VariableStruct (*g_fcbGetArrayValue)(wchar_t*) = NULL;
void(*g_fcbPrintMessage)(wchar_t*, wchar_t*) = NULL;

CMap<CString, LPCWSTR, VariableStruct*, VariableStruct*> g_DBMapList;

CString StringToCString(std::string str)
{
	CString result;
	result = CString::CStringT(CA2CT(str.c_str()));
	return result;
}

std::string CStringToString(CString reqStr)
{
	std::string result;
	result = std::string(CT2CA(reqStr.operator LPCWSTR()));
	return result;
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

int GetArrayIndexFromDimension(CString strOrgDim, CString strDimension)
{
	CString Token;
	CString Seperator = _T("[]");
	int Position = 0;
	CString strBuffer = strOrgDim;

	bool berror = false;
	int idimcount = 0;
	int idim[20];

	Token = strBuffer.Tokenize(Seperator, Position);
	while (Token != L"")
	{
		Token.Trim();
		int iValue = _wtoi(Token);
		if (iValue > 0)
		{
			idim[idimcount] = iValue;
			idimcount++;
		}
		else
		{
			berror = true;
			break;
		}
		Token = strBuffer.Tokenize(Seperator, Position);
	}

	if (berror)
		return 0;

	/////////////////////////////////////////////////////////
	int iIndex = 0;
	strBuffer = strDimension;
	Position = 0;

	int isdimcount = 0;
	int isdim[20];

	Token = strBuffer.Tokenize(Seperator, Position);
	while (Token != L"")
	{
		Token.Trim();
		int iValue = _wtoi(Token);
		if (iValue >= 0)
		{
			isdim[isdimcount] = iValue;
			isdimcount++;
		}
		else
		{
			berror = true;
			break;
		}
		Token = strBuffer.Tokenize(Seperator, Position);
	}

	if (berror || isdimcount != idimcount)
		return 0;

	for (int i = 0; i < idimcount; i++)
	{
		int imux = 1;
		for (int j = i + 1; j < idimcount; j++)
		{
			imux = imux * idim[j];
		}
		iIndex = iIndex + isdim[i] * imux;
	}

	return iIndex;
}

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

// 인터페이스 맵 데이터 구조체 클리어 수행.
void InterfaceDataMapClear()
{
	POSITION mappos = g_DBMapList.GetStartPosition();
	while (mappos)
	{
		VariableStruct *pObject = NULL;
		CString srtVar = L"";
		g_DBMapList.GetNextAssoc(mappos, srtVar, pObject);
		if (srtVar != L"")
		{
			if (pObject)
			{
				delete pObject;
			}
		}
	}
	g_DBMapList.RemoveAll();
}

// enuSpace의 메모리 사이즈가 다른경우, enuSpace의 메모리를 재할당후 값 복사하는 함수
// strVariable=ID_OBJECT.input[12][12] (배열의 SHAPE 정보 포함) pSrc=원본 데이터의 포인터, iType=원본 데이터의 타입, iSize=원본 데이터의 사이즈
// 입력된 배열의 정보와 enuSpace의 배열 정보를 비교
void SetReShapeArrayValue(std::string strVariable, void* pSrc, int iType, int iSize)
{
	VariableStruct* pData = NULL;
	std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());

	CString strVal = (wchar_t*)widestr.c_str();

	CString strDim;
	int iPos = strVal.Find(L"[");
	if (iPos > 1)
	{
		strDim = strVal.Right(strVal.GetLength() - iPos);
		strVal = strVal.Left(iPos);
	}

	g_DBMapList.Lookup(strVal, pData);
	if (pData)
	{
		// 요청한 변수의 데이터 타입 및 배열의 길이가 동일하다면, 값을 업데이트 수행.
		if (pData->array.size == iSize && pData->type == iType)
		{
			// ArraySize는 동일하나 dimension값이 변경된경우 매모리맵의 데이터 업데이트 수행.
			if (wcscmp(pData->array.dimension, strDim.GetBuffer(0)) != 0)
			{
				// enuSpace Reshape 변경을 보냄, enuSpace는 메모리 사이즈 점검후 dimension 정보만 업데이트 수행.
				if (g_fcbSetReShapeArrayValue)
				{
					g_fcbSetReShapeArrayValue((wchar_t*)widestr.c_str(), pSrc, iType, iSize);
					wcscpy_s(pData->array.dimension, strDim);
				}
				return;
			}

			int itemSize = 0;
			void* pTarget = NULL;
			switch (iType)
			{
				case DEF_BOOL:
				{
					itemSize = iSize * sizeof(bool);
					pTarget = ((bool*)pData->pValue);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_INT:
				{
					itemSize = iSize * sizeof(int);
					pTarget = ((int*)pData->pValue);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_FLOAT:
				{
					itemSize = iSize * sizeof(float);
					pTarget = ((float*)pData->pValue);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_DOUBLE:
				{
					itemSize = iSize * sizeof(double);
					pTarget = ((double*)pData->pValue);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_STRING:
				{
					for (int i = 0; i < iSize; i++)
					{
						std::string strValue = *((std::string*)pSrc + i);
						pTarget = ((std::string*)pData->pValue);
						((CString*)pTarget+i)->SetString(StringToCString(strValue));
					}
					break;
				}
			}
			return;
		}
		// 메모리의 데이터 타입 및 배열의 사이즈가 다르다면, 맵 리스트에서 제거 수행 후 메모리 RESHAPE 후 값 업데이트 함수 호출
		else
		{
			delete pData;
			pData = NULL;
			g_DBMapList.RemoveKey(strVal);

			if (g_fcbSetReShapeArrayValue)
			{
				g_fcbSetReShapeArrayValue((wchar_t*)widestr.c_str(), pSrc, iType, iSize);
			}
			// 하위로직을 타고 리스트 별도 추가 수행.
		}
	}

	// 맵 리스트에서 검색을 수행하지 못하였다면, 값을 업데이트 요청함. 값 업데이트 요청함수는 데이터의 타입 및 ARRAY 정보가 다른 경우
	// 메모리의 ReShape 수행후 값을 업데이트 수행
	// 적용된 메모리의 정보를 맵리스트에 추가하여, 다음 로직 수행시 빠른 처리할 수 있도록 추가함.
	if (pData == NULL)
	{
		if (g_fcbGetArrayValue)
		{
			std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());
			VariableStruct Data = g_fcbGetArrayValue(strVal.GetBuffer(0));
			if (Data.pValue)
			{
				// 동일한 데이터의 사이즈 및 타입의 경우 값 업데이트 수행.
				if (Data.type == iType && Data.array.size == iSize)
				{
					int itemSize = 0;
					void* pTarget = NULL;
					switch (iType)
					{
						case DEF_BOOL:
						{
							itemSize = iSize * sizeof(bool);
							pTarget = ((bool*)Data.pValue);
							memcpy(pTarget, pSrc, itemSize);
							break;
						}
						case DEF_INT:
						{
							itemSize = iSize * sizeof(int);
							pTarget = ((int*)Data.pValue);
							memcpy(pTarget, pSrc, itemSize);
							break;
						}
						case DEF_FLOAT:
						{
							itemSize = iSize * sizeof(float);
							pTarget = ((float*)Data.pValue);
							memcpy(pTarget, pSrc, itemSize);
							break;
						}
						case DEF_DOUBLE:
						{
							itemSize = iSize * sizeof(double);
							pTarget = ((double*)Data.pValue);
							memcpy(pTarget, pSrc, itemSize);
							break;
						}
						case DEF_STRING:
						{
							for (int i = 0; i < iSize; i++)
							{
								std::string strValue = *((std::string*)pSrc + i);
								pTarget = ((std::string*)Data.pValue);
								((CString*)pTarget + i)->SetString(StringToCString(strValue));
							}
							break;
						}
					}
					// 리스트 추가 
					VariableStruct* pNewData = new VariableStruct;
					*pNewData = Data;
					g_DBMapList.SetAt(strVal, pNewData);
				}
				// 입력된 사이즈, 타입이 enuSpace의 사이즈, 타입이 다르다면 RESHAPE 및 값 업데이트 수행
				else
				{
					if (g_fcbSetReShapeArrayValue)
					{
						if (iType == DEF_STRING)
						{
							CString *pString = new CString[iSize];
							for (int i = 0; i < iSize; i++)
							{
								std::string strValue = *((std::string*)pSrc + i);
								((CString*)pString + i)->SetString(StringToCString(strValue));
							}
							g_fcbSetReShapeArrayValue((wchar_t*)widestr.c_str(), pString, iType, iSize);
							delete[] pString;
						}
						else
							g_fcbSetReShapeArrayValue((wchar_t*)widestr.c_str(), pSrc, iType, iSize);
					}
				}
			}
			else
			{
				CString strMessage;
				strMessage.Format(L"error : SetArrayValue (Unknown Variable id(%s))", StringToCString(strVariable));
				PrintMessage(strMessage);
				return;			// enuSpace에 없는 변수를 요청함.
			}
		}
	}
}

// 배열값 적용 함수 
// strVarialbe=ID_OBJECT.input[0], pSrc=데이터를 적용할 배열의 주소, iType=데이터의 타입, iSize=데이터의 사이즈
// ID_OBJECT.input[10]의 변수가 10개의 Array로 구성시
// ID_OBJECT.input[5], iSize의 값을 3을 입력하였을 경우, 5번째 부터 7번째까지 복사를 수행함.
// 만약 사이즈의 값이 원본 사이즈의 값을 넘어섰을 경우 값을 복사하지 않음.
void SetArrayValue(std::string strVariable, void* pSrc, int iType, int iSize)
{
	VariableStruct* pData = NULL;
	std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());

	CString strVal = (wchar_t*)widestr.c_str();
	CString strDim;

	// 맵의 정보는 배열의 이름은 포함되어 있지 않음. 구조체 정보에 포함됨.
	int iPos = strVal.Find(L"[");
	if (iPos > 1)
	{
		strDim = strVal.Right(strVal.GetLength() - iPos);
		strVal = strVal.Left(iPos);
	}
	g_DBMapList.Lookup(strVal, pData);

	// 맵을 통하여 데이터의 구조체 정보가 없다면, enuSpace에 해당 변수의 포인터 주소를 요청함.
	if (g_fcbSetArrayValue && pData == NULL)
	{
		VariableStruct Data = g_fcbGetArrayValue(strVal.GetBuffer(0));
		if (Data.pValue)
		{
			VariableStruct* pNewData = new VariableStruct;
			*pNewData = Data;
			g_DBMapList.SetAt((wchar_t*)widestr.c_str(), pNewData);

			pData = pNewData;
		}
	}

	// 취득한 메모리의 영역을 검사하고 적절한 범위라면, 복사 수행.
	if (pData && pData->pValue)
	{
		int itemSize = 0;
		void* pTarget = NULL;
		int iIndex = GetArrayIndexFromDimension(pData->array.dimension, strDim);
		if (iIndex + iSize <= pData->array.size)
		{
			switch (iType)
			{
				case DEF_BOOL:
				{
					itemSize = iSize * sizeof(bool);
					pTarget = ((bool*)pData->pValue + iIndex);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_INT:
				{
					itemSize = iSize * sizeof(int);
					pTarget = ((int*)pData->pValue + iIndex);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_FLOAT:
				{
					itemSize = iSize * sizeof(float);
					pTarget = ((float*)pData->pValue + iIndex);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_DOUBLE:
				{
					itemSize = iSize * sizeof(double);
					pTarget = ((double*)pData->pValue + iIndex);
					memcpy(pTarget, pSrc, itemSize);
					break;
				}
				case DEF_STRING:
				{
					pTarget = pData->pValue;
					for (int i = 0; i < iSize; i++)
					{
						std::string strValue = *((std::string*)pData->pValue + i);
						((CString*)pTarget + i)->SetString(StringToCString(strValue));
					}
					break;
				}
			}
		}
	}
}

// 배열변수의 값을 요청하는 함수 예) OD_OBJECT.input[10] input[10]번쨰의 값을 반환함.
double GetArrayValue(std::string strVariable)
{
	VariableStruct* pData = NULL;
	std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());

	CString strVal = (wchar_t*)widestr.c_str();
	CString strDim;

	// 맵의 정보는 배열의 이름은 포함되어 있지 않음. 구조체 정보에 포함됨.
	int iPos = strVal.Find(L"[");
	if (iPos > 1)
	{
		strDim = strVal.Right(strVal.GetLength() - iPos);
		strVal = strVal.Left(iPos);
	}
	g_DBMapList.Lookup(strVal, pData);

	if (g_fcbGetArrayValue && pData == NULL)
	{
		std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());
		VariableStruct Data = g_fcbGetArrayValue(strVal.GetBuffer(0));
		if (Data.pValue)
		{
			VariableStruct* pNewData = new VariableStruct;
			*pNewData = Data;
			g_DBMapList.SetAt(strVal, pNewData);

			pData = pNewData;
		}
	}

	double fReturn = 0;
	if (pData && pData->pValue)
	{
		// 원본 배열변수의 배열 정보와 입력된 요청된 배열의 정보를 이용하여 Array의 위치를 획득함.
		int iIndex = GetArrayIndexFromDimension(pData->array.dimension, strDim);
		if (iIndex <= pData->array.size)
		{
			switch (pData->type)
			{
				case DEF_INT:
					fReturn = *(int*)pData->pValue;
					break;
				case DEF_FLOAT:
					fReturn = *(float*)pData->pValue;
					break;
				case DEF_DOUBLE:
					fReturn = *(double*)pData->pValue;
					break;
				case DEF_BOOL:
					if (*(bool*)pData->pValue == TRUE)
						fReturn = 1;
					else
						fReturn = 0;
					break;
				case DEF_STRING:
					fReturn = 0;				// NOT SUPPORT
					break;
				default:
					break;
			}
		}
	}
	return fReturn;
}

void SetValue(std::string strVariable, double fValue)
{
	double fReturn = 0;
	VariableStruct* pData = NULL;
	std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());
	g_DBMapList.Lookup((wchar_t*)widestr.c_str(), pData);

	if (g_fcbSetValue && pData == NULL)
	{
		VariableStruct Data = g_fcbGetValue((wchar_t*)widestr.c_str());
		if (Data.pValue)
		{
			VariableStruct* pNewData = new VariableStruct;
			*pNewData = Data;
			g_DBMapList.SetAt((wchar_t*)widestr.c_str(), pNewData);

			pData = pNewData;
		}
	}

	if (pData && pData->pValue)
	{
		switch (pData->type)
		{
		case DEF_INT:
			*(int*)pData->pValue = (int)fValue;
			break;
		case DEF_FLOAT:
			*(float*)pData->pValue = (float)fValue;
			break;
		case DEF_DOUBLE:
			*(double*)pData->pValue = fValue;
			break;
		case DEF_BOOL:
			if (fValue == 1)
				*(bool*)pData->pValue = true;
			else
				*(bool*)pData->pValue = false;
			break;
		case DEF_STRING:

			break;
		default:
			break;
		}
	}
}

double GetValue(std::string strVariable)
{
	double fReturn = 0;
	VariableStruct* pData = NULL;
	std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());
	g_DBMapList.Lookup((wchar_t*)widestr.c_str(), pData);

	if (g_fcbGetValue && pData == NULL)
	{
		VariableStruct Data = g_fcbGetValue((wchar_t*)widestr.c_str());
		if (Data.pValue)
		{
			VariableStruct* pNewData = new VariableStruct;
			*pNewData = Data;
			g_DBMapList.SetAt((wchar_t*)widestr.c_str(), pNewData);

			pData = pNewData;
		}
	}

	if (pData && pData->pValue)
	{
		switch (pData->type)
		{
		case DEF_INT:
			fReturn = *(int*)pData->pValue;
			break;
		case DEF_FLOAT:
			fReturn = *(float*)pData->pValue;
			break;
		case DEF_DOUBLE:
			fReturn = *(double*)pData->pValue;
			break;
		case DEF_BOOL:
			if (*(bool*)pData->pValue == TRUE)
				fReturn = 1;
			else
				fReturn = 0;
			break;
		case DEF_STRING:
			fReturn = 0;				// NOT SUPPORT
			break;
		default:
			break;
		}
	}
	return fReturn;
}

void PrintMessage(CString strMessage, CString strID)
{
	if (g_fcbPrintMessage)
	{
		strMessage = L"component->" + strMessage;
		g_fcbPrintMessage(strMessage.GetBuffer(0), strID.GetBuffer(0));
	}
}

#include "./../jsoncpp-src-0.5.0/include/json/json.h"
#ifdef _DEBUG
#pragma comment(lib,"../jsoncpp-src-0.5.0/lib/x64/debug/lib_json.lib")
#else
#pragma comment(lib,"../jsoncpp-src-0.5.0/lib/x64/release/lib_json.lib")
#endif

struct ObjectInfo
{
	std::string id;					// 그래픽 로직 블럭의 ID
	Json::Value param;				// 그래픽 로직 블럭의 JSON 파라미터 정보
	void *pObject;

	public:ObjectInfo()
	{
		pObject = nullptr;
	}
};

std::map<std::string, ObjectInfo* > m_ObjectMapList;
void ObjectMapClear()
{
	std::map<std::string, ObjectInfo*>::iterator vit;
	for (vit = m_ObjectMapList.begin(); vit != m_ObjectMapList.end(); ++vit)
	{
		ObjectInfo* pTar = vit->second;
		delete pTar;
		pTar = nullptr;
	}
	m_ObjectMapList.clear();
}

void component_input(component *pcomponent, std::string id, Json::Value pInputItem)
{
	int iSize = (int)pInputItem.size();
	for (int subindex = 0; subindex < iSize; ++subindex)
	{
		Json::Value ItemValue = pInputItem[subindex];

		std::string strPinName = ItemValue.get("pin-name", "").asString();								
		std::string strPinType = ItemValue.get("pin-type", "").asString();								
		std::string strPinInitial = ItemValue.get("pin-initial", "").asString();						
		std::string strPinDataType = ItemValue.get("pin-datatype", "").asString();				
		std::string strPinShape = ItemValue.get("pin-shape", "").asString();		

		std::string strVariable = id + "." + strPinName;

		VariableStruct* pData = NULL;
		std::wstring widestr = std::wstring(strVariable.begin(), strVariable.end());
		g_DBMapList.Lookup((wchar_t*)widestr.c_str(), pData);

		if (g_fcbGetValue && pData == NULL)
		{
			VariableStruct Data = g_fcbGetValue((wchar_t*)widestr.c_str());
			if (Data.pValue)
			{
				if (!pcomponent->SetInitValue(strPinName, &Data))
				{
					CString strMsg;
					strMsg.Format(L"warning : %s - Interface variable missed.", widestr.c_str());
					PrintMessage(strMsg);
				}
			}
		}
	}
}

bool Init_component(std::string config_doc, std::string page_name)
{
	Json::Value root;
	Json::Reader reader;

	bool parsingSuccessful = reader.parse(config_doc, root);
	if (!parsingSuccessful)
	{
		return false;
	}

	Json::Value InputItem;
	const Json::Value plugins = root["object"];
	for (int index = 0; index < (int)plugins.size(); ++index)
	{
		Json::Value Item = plugins[index];

		std::string strSymbolName = Item.get("symbol-name", "").asString();
		std::string strId = Item.get("id", "").asString();

		if (strSymbolName == "#component")
		{
			ObjectInfo* pObj = nullptr;
			const std::map<std::string, ObjectInfo*>::const_iterator aLookup = m_ObjectMapList.find(strId);
			const bool bExists = aLookup != m_ObjectMapList.end();
			if (bExists == false)
			{
				component *pComponent = new component();
				std::wstring widestr = std::wstring(strId.begin(), strId.end());

				Json::Value InputItem = Item["input"];
				component_input(pComponent, strId, InputItem);

				pComponent->SetInterface(widestr.c_str(), g_fcbSetPinInterfaceVariable);

				ObjectInfo* pCreateObj = new ObjectInfo;
				pCreateObj->pObject = pComponent;
				pCreateObj->id = strId;

				m_ObjectMapList.insert(std::pair<std::string, ObjectInfo*>(strId, pCreateObj));
			}
		}
	}

	return true;
}

extern "C" __declspec(dllexport) bool OnLoad()
{
	return true;
}

extern "C" __declspec(dllexport) bool OnInit()
{
	try
	{
		ObjectMapClear();
		InterfaceDataMapClear();

		CString dirName = g_strDllPath;
		CString strExt = L"/*.json";

		CFileFind finder;

		BOOL bWorking = finder.FindFile(dirName + strExt);

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (finder.IsDots())
			{
				continue;
			}

			CString logic_file = finder.GetFilePath();

			std::string filename = CStringToString(logic_file);

			CString str;
			CFile pFile;

			if (pFile.Open(logic_file, CFile::modeRead | CFile::typeBinary))
			{
				pFile.Seek(2, CFile::begin);
				size_t fLength = (size_t)pFile.GetLength() - 2;
				TCHAR *th = (TCHAR*)malloc(fLength + sizeof(TCHAR));
				memset(th, 0, fLength + sizeof(TCHAR));
				pFile.Read(th, fLength);

				str = th;
				free(th);
				pFile.Close();

				std::string covertStr;
				covertStr = CStringToString(str);

				WCHAR drive[_MAX_DRIVE];
				WCHAR dir[_MAX_DIR];
				WCHAR fname[_MAX_FNAME];
				WCHAR ext[_MAX_EXT];
				_wsplitpath_s(logic_file, drive, dir, fname, ext);

				///////////////////////////////////////////////////////////////////
				// binary data file
				CString datafilename;
				datafilename.Format(L"%s%s%s.dat", drive, dir, fname);
				if (_wfopen_s(&m_FileData, datafilename.GetBuffer(0), L"rb") != NULL)
				{
					m_FileData = NULL;
				}

				std::string pagename;
				pagename = CStringToString(fname);

				Init_component(covertStr, pagename);

				///////////////////////////////////////////////////////////////////
				// binary data file close
				if (m_FileData)
				{
					fclose(m_FileData);
					m_FileData = NULL;
				}
			}
		}
		finder.Close();
		return true;
	}
	catch (...)
	{

	}
	return false;
}

extern "C" __declspec(dllexport) bool OnTask(__int64 time)
{
	std::map<std::string, ObjectInfo*>::iterator vit;
	for (vit = m_ObjectMapList.begin(); vit != m_ObjectMapList.end(); ++vit)
	{
		ObjectInfo* pTar = vit->second;
		((component*)pTar->pObject)->Simulation();
	}

	return true;
}

extern "C" __declspec(dllexport) bool OnUnload()
{
	ObjectMapClear();
	InterfaceDataMapClear();
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
	return TASK_TYPE_FLOW_COMPONENT_PAGE;
}

extern "C" __declspec(dllexport) bool IsEnableTransfer(wchar_t* pFromType, wchar_t* pToType)
{
	return true;
}

extern "C" __declspec(dllexport) bool IsTaskStopWhenModify()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////

