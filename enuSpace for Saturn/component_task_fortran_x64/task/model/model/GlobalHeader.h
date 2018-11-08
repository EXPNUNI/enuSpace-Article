#pragma once

#ifndef _GLOBAL_MODEL_HEADER__
#define _GLOBAL_MODEL_HEADER__

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

#define TASK_TYPE_UNKNOWN						0			// Task의 타입 정의 (알수없는 타입)
#define TASK_TYPE_PROCESS						1			// Task의 타입 정의	(연산처리용 타입)
#define TASK_TYPE_FLOW_COMPONENT_TOTAL			2			// Task의 타입 정의	(FLOW 컴포넌트 전체 단위 타입)
#define TASK_TYPE_FLOW_COMPONENT_PAGE			3			// Task의 타입 정의	(FLOW컴포넌트 페이지 단위 타입)
#define TASK_TYPE_FUNCTION_COMPONENT			4			// Task의 타입 정의 (함수형 컴포넌트 타입)
#define TASK_TYPE_OBJECTARRAY					5			// Task의 타입 정의 (오브젝트의 포인터 배열 정보를 이용하여 데이터 전달)

#define DEF_NAME_LEN							64
#define DEF_MAXTEXT_LEN							2048
#define DEF_LABELTEXT_LEN						1024


///////////////////////////////////////////////////////////////////////
// 데이터 구조체 정보.
struct arrayInfo
{
	int size;									// 변수 배열의 개수		ex) 100 
	wchar_t dimension[DEF_LABELTEXT_LEN];		// 문자열 배열 정보		ex) [10][10]

	public:arrayInfo()
	{
		size = 0;
		wcscpy_s(dimension, L"");
	}
};

struct VariableStruct
{
	wchar_t name[DEF_NAME_LEN];				// 변수 이름.
	int     type;							// 변수의 타입 (단일변수 또는 구조체)
	void*   pValue;							// 변수의 주소
	wchar_t strValue[DEF_MAXTEXT_LEN];		// 단일 변수에 대한 문자열 값
	arrayInfo array;						// 배열 정보
	void* pStructItem;						// 구조체 선언정보
	void* pVariableItem;					// 변수 구조체 정보.
	int iSize;								// 변수의 메모리 사이즈

	public:VariableStruct()
	{
		wcscpy_s(name, L"");
		type = DEF_UNKNOWN;
		pValue = NULL;
		wcscpy_s(strValue, L"N/A");
		pStructItem = NULL;
		pVariableItem = NULL;
		iSize = 0;
	}
};

#endif