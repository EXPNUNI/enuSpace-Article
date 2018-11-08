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

#define TASK_TYPE_UNKNOWN						0			// Task�� Ÿ�� ���� (�˼����� Ÿ��)
#define TASK_TYPE_PROCESS						1			// Task�� Ÿ�� ����	(����ó���� Ÿ��)
#define TASK_TYPE_FLOW_COMPONENT_TOTAL			2			// Task�� Ÿ�� ����	(FLOW ������Ʈ ��ü ���� Ÿ��)
#define TASK_TYPE_FLOW_COMPONENT_PAGE			3			// Task�� Ÿ�� ����	(FLOW������Ʈ ������ ���� Ÿ��)
#define TASK_TYPE_FUNCTION_COMPONENT			4			// Task�� Ÿ�� ���� (�Լ��� ������Ʈ Ÿ��)
#define TASK_TYPE_OBJECTARRAY					5			// Task�� Ÿ�� ���� (������Ʈ�� ������ �迭 ������ �̿��Ͽ� ������ ����)

#define DEF_NAME_LEN							64
#define DEF_MAXTEXT_LEN							2048
#define DEF_LABELTEXT_LEN						1024


///////////////////////////////////////////////////////////////////////
// ������ ����ü ����.
struct arrayInfo
{
	int size;									// ���� �迭�� ����		ex) 100 
	wchar_t dimension[DEF_LABELTEXT_LEN];		// ���ڿ� �迭 ����		ex) [10][10]

	public:arrayInfo()
	{
		size = 0;
		wcscpy_s(dimension, L"");
	}
};

struct VariableStruct
{
	wchar_t name[DEF_NAME_LEN];				// ���� �̸�.
	int     type;							// ������ Ÿ�� (���Ϻ��� �Ǵ� ����ü)
	void*   pValue;							// ������ �ּ�
	wchar_t strValue[DEF_MAXTEXT_LEN];		// ���� ������ ���� ���ڿ� ��
	arrayInfo array;						// �迭 ����
	void* pStructItem;						// ����ü ��������
	void* pVariableItem;					// ���� ����ü ����.
	int iSize;								// ������ �޸� ������

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