// ���Ե� warning
#pragma warning(disable:4838) // ����ת��
#pragma warning(disable:4005) // ���ض���
#pragma warning(disable:4044) //


// ����һ�� _E_MSVC_NAME
#if _MSC_VER == 1200
#define _E_MSVC_NAME "Microsoft Visual C++ 6.0(1998)"
#elif _MSC_VER == 1310
#define _E_MSVC_NAME "Microsoft Visual C++ 7.1(2003)"
#elif _MSC_VER == 1400 
#define _E_MSVC_NAME "Microsoft Visual C++ 8.0(2005)"
#elif _MSC_VER == 1500 
#define _E_MSVC_NAME "Microsoft Visual C++ 9.0(2008)"
#elif _MSC_VER == 1600  
#define _E_MSVC_NAME "Microsoft Visual C++ 10.0(2010)"
#elif _MSC_VER == 1700   
#define _E_MSVC_NAME "Microsoft Visual C++ 11.0(2012)"
#elif _MSC_VER == 1800   
#define _E_MSVC_NAME "Microsoft Visual C++ 12.0(2013)"
#elif _MSC_VER == 1900   
#define _E_MSVC_NAME "Microsoft Visual C++ 14.0(2015)"
#elif _MSC_VER == 1911   
#define _E_MSVC_NAME "Microsoft Visual C++ 14.1(2017)"
#else
#define _E_MSVC_NAME "δ֪�汾 MSVC"
#endif

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "tchar.h"
#include "wtypes.h"

#include "lib2.h"
#include "lang.h"

//����Ϣ 

#ifndef __E_STATIC_LIB
#define LIB_GUID_STR			"{1A357FCF-855F-41c2-893E-8163685BF81F}" /*guidgen.exe����,����ǩ��*/
#define LIB_MajorVersion		1  /*�����汾��*/
#define LIB_MinorVersion		0   /*��ΰ汾��*/
#define LIB_BuildNumber			20180819 /*�����汾��*/
#define LIB_SysMajorVer			3 /*ϵͳ���汾��*/
#define LIB_SysMinorVer			0 /*ϵͳ�ΰ汾��*/
#define LIB_KrnlLibMajorVer		3 /*���Ŀ����汾��*/
#define LIB_KrnlLibMinorVer		0 /*���Ŀ�ΰ汾��*/
#define LIB_NAME_STR			"WinSocketForLyp" /*֧�ֿ���*/
#define LIB_DESCRIPTION_STR		"��װ�˿ͻ���IOCPģ�͵�UDP/TCP���"/*�������� ԭ����NULL*/
#define LIB_Author				"Lyp"/*��������*/

#define LIB_ZipCode		NULL
#define LIB_Address		"���Ե�ַ"
#define LIB_Phone		"13145205200"
#define LIB_Fax			NULL 
#define LIB_Email		"942664114@qq.com"
#define LIB_HomePage	NULL
#define LIB_Other		NULL

#define LIB_TYPE_COUNT 2 /*�����������*/
#define LIB_TYPE_STR "0000UDPClient\0""0000TCPClient\0""\0" /*�������*/
#endif


