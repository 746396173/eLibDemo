#include "stdafx.h"
#include "libDemo.h"
#include "UDPClient.h"
#include "TCPClient.h"

//////////////////////////////////////////////////////////////////////
//////-----��-----�ⳣ��������������Ͷ�����-----��-----//////////
//////////////////////////////////////////////////////////////////////
#ifndef __E_STATIC_LIB
//���� __E_STATIC_LIB �ڲ�����
BOOL mConstsIsNull = FALSE;
LIB_CONST_INFO Consts[] =
{

	/* { ��������, Ӣ������, ��������, �����ȼ�(LVL_), ��������(CT_), �ı�����, ��ֵ���� }   ֻ��������������*/

	{ _WT("UDP_��������"), _WT("UDP_SEND_DATA"), NULL, LVL_HIGH, CT_NUM, NULL, UDP_SEND_DATA },
	{ _WT("UDP_�յ�����"), _WT("UDP_RECV_DATA"), NULL, LVL_HIGH, CT_NUM, NULL, UDP_RECV_DATA },
	{ _WT("UDP_��������"), _WT("UDP_ERROR_SOCKET"), NULL, LVL_HIGH, CT_NUM, NULL, UDP_ERROR_SOCKET },

	{ _WT("TCP_��������"), _WT("TCP_SEND_DATA"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_SEND_DATA },
	{ _WT("TCP_���ݵ���"), _WT("TCP_RECV_DATA"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_RECV_DATA },
	{ _WT("TCP_�ͻ��Ͽ�"), _WT("TCP_CLIENT_DISCONNECT"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_CLIENT_DISCONNECT },
	{ _WT("TCP_����Ͽ�"), _WT("TCP_SERVER_DISCONNECT"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_SERVER_DISCONNECT },
	{ _WT("TCP_�쳣�Ͽ�"), _WT("TCP_EXCEPTION_DISCONNECT"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_EXCEPTION_DISCONNECT },
	{ _WT("TCP_��������"), _WT("TCP_ERROR"), NULL, LVL_HIGH, CT_NUM, NULL, TCP_ERROR },
};

#endif

//��ؽ���
/*
�����ȼ���: LVL_SIMPLE  1  ����        LVL_SECONDARY  2  �м�             LVL_HIGH  3  �߼�

���������� : CT_NUM             1    // sample: 3.1415926
CT_BOOL            2    // sample: 1
CT_TEXT            3    // sample: "abc"

�ı�������CT_TEXT�ã���ֵ������CT_NUM��CT_BOOL�á�
*/


/////////////////////////////////////////////////////////////////
//////--------------------�����Զ�����������----------------//////
////////////////////////////////////////////////////////////////

#ifndef __E_STATIC_LIB	//���м�ľ�̬����ʱ����
//���� __E_STATIC_LIB �ڲ�����   
#endif


#ifndef __E_STATIC_LIB
//���� __E_STATIC_LIB �ڲ�����
INT DatatypeCommandIndexs[] =
{
	NULL
};
BOOL mDataTypesIsNull = TRUE;
static LIB_DATA_TYPE_INFO DataTypes[] =
{
	NULL
	/* { ��������, Ӣ������, ��������, ��������, ��������, ����״̬, ͼ������, �¼�����, �¼�ָ��, ��������, ����ָ��, ����ָ��, Ԫ������, Ԫ��ָ�� } */
};

#endif

/////////////////////////////////////////////////////////////////////////////
///////------------------֧�ֿ������ʵ������---------------------////////
/////////////////////////////////////////////////////////////////////////////

/*
������ʵ�ֶ���Ҫ�����ں�������Ա㾲̬�Ͷ�̬�ⶼ��ʹ�ã���ExecuteCommand��Commands��ֻ�趨���ں�����湩��̬��ʹ�á�
pRetData �������ָ�롣����ӦCMD_INFO��m_dtRetTypeΪ_SDT_NULL���������޷���ֵ��ʱ��pRetData��Ч��
iArgCount ������������
pArgInf ��������ָ��
*/

EXTERN_C void sum(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_int = pArgInf[0].m_int + pArgInf[1].m_int;
	return;
};

EXTERN_C void InitEnv(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = InitWinsock();
	return;
};

EXTERN_C void EndEnv(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	destory();
	return;
};

EXTERN_C void Start(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	int port = pArgInf[0].m_int;
	int callback = pArgInf[1].m_int;
	int extra = pArgInf[2].m_int;
	OverlappedP* ptr = start(port, callback, extra);
	pRetData->m_int = (int)ptr;
	return;
};

EXTERN_C void SendTo(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	OverlappedP* ptr = (OverlappedP*)pArgInf[0].m_int;
	char *ip = pArgInf[1].m_pText;
	int port = pArgInf[2].m_int;
	char* buf = (char*)pArgInf[3].m_int;
	int len = pArgInf[4].m_int;
	pRetData->m_bool = sendpack(ptr, ip, port, buf, len);
	return;
};

EXTERN_C void Stop(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	OverlappedP* ptr = (OverlappedP*)pArgInf[0].m_int;
	pRetData->m_bool = stop(ptr);
	return;
};

EXTERN_C void InitTCPEnv(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	pRetData->m_bool = TCPInitWinsock();
	return;
};

EXTERN_C void EndTCPEnv(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	Destory();
	return;
};

//TCPOverlappedP* Connect(char* serverIp, u_short serverPort, int callback, int Extra);
EXTERN_C void ConnectServer(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	char *ip = pArgInf[0].m_pText;
	int port = pArgInf[1].m_int;
	int callback = pArgInf[2].m_int;
	int extra = pArgInf[3].m_int;
	
	TCPOverlappedP* ptr = Connect(ip, port, callback, extra);
	pRetData->m_int = (int)ptr;
	return;
};

EXTERN_C void Send(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	TCPOverlappedP* ptr = (TCPOverlappedP*)pArgInf[0].m_int;
	char* buf = (char*)pArgInf[1].m_int;
	int len = pArgInf[2].m_int;
	pRetData->m_int = Send(ptr, buf, len);
	return;
};

//int Close(TCPOverlappedP* recv);
EXTERN_C void Close(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	TCPOverlappedP* ptr = (TCPOverlappedP*)pArgInf[0].m_int;
	pRetData->m_int = Close(ptr);
	return;
};

EXTERN_C void GetClientPort(PMDATA_INF pRetData, INT iArgCount, PMDATA_INF pArgInf)
{
	TCPOverlappedP* ptr = (TCPOverlappedP*)pArgInf[0].m_int;
	pRetData->m_int = (int)GetClientPort(ptr);
	return;
};


//==========================================
//==========================================
//==========================================
#ifndef __E_STATIC_LIB
PFN_EXECUTE_CMD ExecuteCommand[] =
{
	// ������Ҫ���е��õ�  ����  ����������ö��Ÿ���
	InitEnv,
	EndEnv,
	Start,
	SendTo,
	Stop,
	InitTCPEnv,
	EndTCPEnv,
	ConnectServer,
	Send,
	Close,
	GetClientPort
};

static const char* const CommandNames[] =
{
	// ������Ҫ���е��õ�  ������  ��д������ö��Ÿ���
	"InitEnv",
	"EndEnv",
	"Start",
	"SendTo",
	"Stop", 
	"InitTCPEnv",
	"EndTCPEnv",
	"ConnectServer",
	"Send",
	"Close",
	"GetClientPort"
};

#endif

/////////////////////////////////////////////////////////////////////////////
///////----------------����֧�ֿ����������-----------------------////////
/////////////////////////////////////////////////////////////////////////////
#ifndef __E_STATIC_LIB

ARG_INFO sum_CommandArgs[] =
{
	{ _WT("arg1"), _WT(""), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("arg2"), _WT(""), 0, 0, SDT_INT, NULL, NULL },
};
//���������������� OverlappedP* start(int clientport, int callback, int Extra)
//(over->OperationType, (int)over->wsabuf.buf, Transferred, inet_ntoa(over->addr.sin_addr), ntohs(over->addr.sin_port), over->Extra)
/* { ��������, ��������, ͼ������, ͼ������, ��������(�μ�SDT_), Ĭ����ֵ, �������(�μ�AS_) } */
ARG_INFO Start_CommandArgs[] =
{
	{ _WT("�󶨶˿�"), _WT("�ͻ��˰󶨵ı��ض˿�,Ĭ��Ϊ0������ϵͳ�Զ�����һ�����ö˿�"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("�ص���ַ"), _WT("�¼��ص�����(�޷���ֵ)\r\n\t����1:�¼����� \r\n\t����2:���ݵ�ַ\r\n\t����3:���ݳ���\r\n\t����4:������IP\r\n\t����5:�����߶˿�\r\n\t����6:��������"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("��������"), _WT("���ͻ��˰󶨵�����,���ڻص������л�ȡ���й�������."), 0, 0, SDT_INT, NULL, NULL },
};
//�������ݲ���   bool sendpack(OverlappedP* recv, char* ip, short port, char* buffer, int buflen)
ARG_INFO Send_CommandArgs[] =
{
	{ _WT("�󶨾��"), _WT("�˾��������()��������"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("�Է���ַ"), _WT("�Է�IP"), 0, 0, SDT_TEXT, NULL, NULL },
	{ _WT("�Է��˿�"), _WT("�Է��˿�"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("����ָ��"), _WT("�ֽڼ��������ݵ�ַ"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("���ݳ���"), _WT("���ݳ���"), 0, 0, SDT_INT, NULL, NULL },
};

//ֹͣ����   bool stop(OverlappedP *Recv);
ARG_INFO Stop_CommandArgs[] =
{
	{ _WT("�󶨾��"), _WT("�˾��������()��������"), 0, 0, SDT_INT, NULL, NULL }
};

//Connect����
ARG_INFO Connect_CommandArgs[] =
{
	{ _WT("������IP"), _WT("��������IP,���ʮ����,����192.168.0.1,127.0.0.1"), 0, 0, SDT_TEXT, NULL, NULL },
	{ _WT("�������˿�"), _WT("�������Ķ˿�"), 0, 0, SDT_INT, NULL, NULL },
	////�¼�����  ���ݵ�ַ ���ݳ��� �����ַ ����˿� �������� �������
	{ _WT("�ص���ַ"), _WT("�¼��ص�����(�޷���ֵ),��������������\r\n\t����1: �¼����� ������\r\n\t����2: ���ݵ�ַ\r\n\t����3: ���ݳ���\r\n\t����4:������IP\r\n\t����5:�������˿�\r\n\t����6:��������\r\n\t����7:�������"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("��������"), _WT("���ͻ��˰󶨵�����,���ڻص������л�ȡ���й�������."), 0, 0, SDT_INT, NULL, NULL },
};

//int Send(TCPOverlappedP* recv, char* buf, int len);
ARG_INFO TCPSend_CommandArgs[] =
{
	{ _WT("�󶨾��"), _WT("�˾��������()��������"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("����ָ��"), _WT("�ֽڼ��������ݵ�ַ"), 0, 0, SDT_INT, NULL, NULL },
	{ _WT("���ݳ���"), _WT("���ݳ���"), 0, 0, SDT_INT, NULL, NULL },
};

//int Close(TCPOverlappedP* recv);
ARG_INFO Close_CommandArgs[] =
{
	{ _WT("�󶨾��"), _WT("�˾��������()��������"), 0, 0, SDT_INT, NULL, NULL }
};

//u_short GetClientPort(TCPOverlappedP* ptr);
ARG_INFO GetClientPort_CommandArgs[] =
{
	{ _WT("�󶨾��"), _WT("�˾��������()��������"), 0, 0, SDT_INT, NULL, NULL }
};
#endif

/////////////////////////////////////////////////////////////////////////////
///////---------------����Ҫ������֧�ֿ�����----------------------////////
/////////////////////////////////////////////////////////////////////////////
#ifndef __E_STATIC_LIB

static CMD_INFO Commands[] =
{
	/* { ��������, Ӣ������, ��������, �������(-1���������͵ķ���), ����״̬(CT_), ��������(SDT_), ��ֵ����, ����ȼ�(LVL_), ͼ������, ͼ������, ��������, ������Ϣ } */
	{
		/*��������*/						_WT("InitEnv"),
		/*Ӣ������*/						_WT("InitEnv"),
		/*��������*/						_WT("��ʼ��Socket����,ֻ����һ��,�����ڳ���һ����(������[_��������_�������]�ӳ����µ���)��Ҫ����,�������ʱ����,EndEnv()"),
		/*�������(-1���������͵ķ���)*/	1,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				_SDT_NULL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						0,
		/*������Ϣ*/						NULL
	},
	{
		/*��������*/						_WT("EndEnv"),
		/*Ӣ������*/						_WT("EndEnv"),
		/*��������*/						_WT("��InitEnv��Ӧ"),
		/*�������(-1���������͵ķ���)*/	1,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				_SDT_NULL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						0,
		/*������Ϣ*/						NULL
	},
	{
		/*��������*/						_WT("Start"),
		/*Ӣ������*/						_WT("Start"),
		/*��������*/						_WT("����Socket,���ؾ��,�˾�������ڷ�������,�˾������SOCEKT���,����һ���ص��ṹָ��."),
		/*�������(-1���������͵ķ���)*/	1,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_INT,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(Start_CommandArgs) / sizeof(Start_CommandArgs[0]),
		/*������Ϣ*/						Start_CommandArgs
	},
	{
		/*��������*/						_WT("SendTo"),
		/*Ӣ������*/						_WT("SendTo"),
		/*��������*/						_WT("��������"),
		/*�������(-1���������͵ķ���)*/	1,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_BOOL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(Send_CommandArgs) / sizeof(Send_CommandArgs[0]),
		/*������Ϣ*/						Send_CommandArgs
	},
	{
		/*��������*/						_WT("Stop"),
		/*Ӣ������*/						_WT("Stop"),
		/*��������*/						_WT("�ر����Socket"),
		/*�������(-1���������͵ķ���)*/	1,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_BOOL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(Stop_CommandArgs) / sizeof(Stop_CommandArgs[0]),
		/*������Ϣ*/						Stop_CommandArgs
	},
	{
		/*��������*/						_WT("InitTCPEnv"),
		/*Ӣ������*/						_WT("InitTCPEnv"),
		/*��������*/						_WT("��ʼ��TCP����"),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_BOOL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						0,
		/*������Ϣ*/						0
	},
	{
		/*��������*/						_WT("EndTCPEnv"),
		/*Ӣ������*/						_WT("EndTCPEnv"),
		/*��������*/						_WT("���TCP����"),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_BOOL,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						0,
		/*������Ϣ*/						0
	},
	{
		/*��������*/						_WT("Connect"),
		/*Ӣ������*/						_WT("ConnectServer"),
		/*��������*/						_WT("���ӷ�����,���ؾ��,�˾�������ڷ�������,�˾������SOCEKT���,����һ���ص��ṹָ��."),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_INT,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(Connect_CommandArgs) / sizeof(Connect_CommandArgs[0]),
		/*������Ϣ*/						Connect_CommandArgs
	},
	{
		/*��������*/						_WT("Send"),
		/*Ӣ������*/						_WT("Send"),
		/*��������*/						_WT("��������,����ֵ��0���ɹ��� -1��SOCKET��Ч�� -2 ����ʧ�� ����WSAGetLastError()��ȡ�������"),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_INT,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(TCPSend_CommandArgs) / sizeof(TCPSend_CommandArgs[0]),
		/*������Ϣ*/						TCPSend_CommandArgs
	},
	{
		/*��������*/						_WT("Close"),
		/*Ӣ������*/						_WT("Close"),
		/*��������*/						_WT("�ر����Socket����"),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_INT,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(Close_CommandArgs) / sizeof(Close_CommandArgs[0]),
		/*������Ϣ*/						Close_CommandArgs
	},
	{
		/*��������*/						_WT("GetClientPort"),
		/*Ӣ������*/						_WT("GetClientPort"),
		/*��������*/						_WT("��ȡ�ͻ��˶˿�"),
		/*�������(-1���������͵ķ���)*/	2,
		/*����״̬(CT_)*/				NULL,
		/*��������(SDT_)*/				SDT_INT,
		/*��ֵ����*/						0,
		/*����ȼ�(LVL_)*/				LVL_SIMPLE,
		/*ͼ������*/						0,
		/*ͼ������*/						0,
		/*��������*/						sizeof(GetClientPort_CommandArgs) / sizeof(GetClientPort_CommandArgs[0]),
		/*������Ϣ*/						GetClientPort_CommandArgs
	},

};
#endif


INT WINAPI ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
	INT nRet = NR_OK;
	switch (nMsg)
	{
	case NL_SYS_NOTIFY_FUNCTION:
		//g_fnNotifySys = (PFN_NOTIFY_SYS)dwParam1;
		break;
	case NL_FREE_LIB_DATA:
		break;
	default:
		nRet = NR_ERR;
		break;
	}

	////�����û�����
	//if (g_fn_OnSysNotify)
	//	nRet = g_fn_OnSysNotify(nMsg, dwParam1, dwParam2);

	return nRet;
}

//////////////////////////////////////////////////////////////////////
//////// -----------------֧�ֿ���Ϣ������------------------//////
//////////////////////////////////////////////////////////////////////

EXTERN_C INT WINAPI  _ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
#ifndef __E_STATIC_LIB
	if (nMsg == NL_GET_CMD_FUNC_NAMES) // ������������ʵ�ֺ����ĵĺ�����������(char*[]), ֧�־�̬����Ķ�̬����봦��
		return (INT)CommandNames;
	else if (nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME) // ���ش���ϵͳ֪ͨ�ĺ�������(PFN_NOTIFY_LIB��������), ֧�־�̬����Ķ�̬����봦��
		return (INT)"_ProcessNotifyLib";
	else if (nMsg == NL_GET_DEPENDENT_LIBS) return (INT)NULL;
	// ���ؾ�̬����������������̬���ļ����б�(��ʽΪ\0�ָ����ı�,��β����\0), ֧�־�̬����Ķ�̬����봦��
	// kernel32.lib user32.lib gdi32.lib �ȳ��õ�ϵͳ�ⲻ��Ҫ���ڴ��б���
	// ����NULL��NR_ERR��ʾ��ָ�������ļ�  
#endif
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
};


///////////////////////////////////////
////////   ����֧�ֿ������Ϣ   //////
///////////////////////////////////////

#ifndef __E_STATIC_LIB
static LIB_INFO LibInfo =
{
	/* { ���ʽ��, GUID����, ���汾��, �ΰ汾��, �����汾��, ϵͳ���汾��, ϵͳ�ΰ汾��, ���Ŀ����汾��, ���Ŀ�ΰ汾��,
	֧�ֿ���, ֧�ֿ�����, ֧�ֿ�����, ֧�ֿ�״̬,
	��������, ��������, ͨ�ŵ�ַ, �绰����, �������, ��������, ��ҳ��ַ, ������Ϣ,
	��������, ����ָ��, �������, �������, ��������, ����ָ��, �������,
	���ӹ���, ��������, ��Ϣָ��, ����ģ��, ģ������,
	��������, ����ָ��, �ⲿ�ļ�} */
	LIB_FORMAT_VER,/*���ʽ��*/
	_T(LIB_GUID_STR),/*����*/
	LIB_MajorVersion,/*���汾��*/
	LIB_MinorVersion,/*�ΰ汾��*/
	LIB_BuildNumber,/*�����汾��*/
	LIB_SysMajorVer,/*ϵͳ���汾��*/
	LIB_SysMinorVer,/*ϵͳ�ΰ汾��*/
	LIB_KrnlLibMajorVer,/*���Ŀ����汾��*/
	LIB_KrnlLibMinorVer,/*���Ŀ�ΰ汾��*/
	_T(LIB_NAME_STR),/*֧�ֿ���*/
	__GBK_LANG_VER,/**/
	_WT(LIB_DESCRIPTION_STR),/*֧�ֿ�����*/
	_LIB_OS(__OS_WIN),/**/
	_WT(LIB_Author),/*��������*/
	_WT(LIB_ZipCode),/*��������*/
	_WT(LIB_Address),/*ͨ�ŵ�ַ*/
	_WT(LIB_Phone),/*�绰����*/
	_WT(LIB_Fax),/*�������*/
	_WT(LIB_Email),/*��������*/
	_WT(LIB_HomePage),/*��ҳ��ַ*/
	_WT(LIB_Other),/*������Ϣ*/
	mDataTypesIsNull ? NULL : sizeof(DataTypes) / sizeof(DataTypes[0]),/*��������*/
	mDataTypesIsNull ? NULL : DataTypes,/*����ָ��*/
	LIB_TYPE_COUNT,/*�������*/
	_WT(LIB_TYPE_STR),/*�������*/
	sizeof(Commands) / sizeof(Commands[0]),/*��������*/
	Commands,/*����ָ��*/
	ExecuteCommand,/*�������*/
	NULL,/*���ӹ���*/
	NULL,/*��������*/
	_ProcessNotifyLib,/*��Ϣָ��*/
	NULL,/*����ģ��*/
	NULL,/*ģ������*/
	mConstsIsNull ? NULL : sizeof(Consts) / sizeof(Consts[0]),/*��������*/
	mConstsIsNull ? NULL : Consts,/*����ָ��*/
	NULL/*�ⲿ�ļ�*/
};


EXTERN_C _declspec(dllexport) PLIB_INFO GetNewInf()
{
	return (&LibInfo);
};

#endif