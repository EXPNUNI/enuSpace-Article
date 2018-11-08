#pragma once
#pragma pack(1)
#include <string>

#pragma pack(push, 1) 

struct EnuObject
{
	wchar_t id[32];
	wchar_t type[32];
	EnuObject *from;
	EnuObject *to;
};
struct EnuParam
{
	int type;
	void* param;
};
struct TRANSFER : EnuObject
{	
	EnuParam param_from;
	EnuParam param_to;
};


#pragma pack(pop) 
