#pragma once//Ԥ����ָ��  ��һ���Ͳ����ظ�����ͷ�ļ�
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
	int Index;//�������е�����
	int Index_Prop;//�������ж�Ӧ���ߵ�����
	LONGLONG Offset_Propadd;//��������ж�Ӧ���ߵĵ����ļ�ƫ����

	LONG Netlist = sizeof(LONG);
};



typedef	struct prop
{
	int Index;//��������
	ULONG sizeImage;//�������ܴ�С
	std::wstring Name;//��������
	BITMAPFILEHEADER* pbitmapadr;//�ļ�ͷ
	BITMAPINFO* Picture;//�ļ��� BITMAPINFO  ������ɫ��������ܴ��ڣ�
	BYTE* pBit;//����
	std::wstring	Illustrate;//����

} PROP, * lPPROP;