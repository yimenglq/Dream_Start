#pragma once//预编译指令  有一个就不会重复包含头文件
#include<Windows.h>
#include<windowsx.h>
#include<map>
#include<vector>
#include <string>
#include<time.h>
#include<process.h>
#include"Game_Init_cpp_macro.h"

using namespace std;


typedef struct prop_FILE_top
{
	LONGLONG porp_num;
	LONGLONG num_porp_sizebyte;
};
typedef struct prop_FILE_prop_listadd
{
	int Index;//向量表中的引索
	int Index_Prop;//向量表中对应道具的引索
	LONGLONG Offset_Propadd;//向量表存有对应道具的道具文件偏移量

	LONG Netlist = sizeof(LONG);
};



typedef	struct prop
{
	int Index;//道具引索
	ULONG sizeImage;//像素体总大小
	std::wstring Name;//道具名称
	BITMAPFILEHEADER* pbitmapadr;//文件头
	BITMAPINFO* Picture;//文件体 BITMAPINFO  加上颜色表（这个可能存在）
	BYTE* pBit;//像素
	std::wstring	Illustrate;//描述

} PROP, * lPPROP;