#ifndef _MESSAGEDEF_H_
#define _MESSAGEDEF_H_

//------------------------------------------------------------------------------
// �޽��� ����
// �޽����� ID���� Connect�ÿ� ������ nStartMsgID�� ���Ͽ� ���
#define 	WMU_STARTMSGID				WM_USER + 1000

#define 	WMU_RECEIVE_SYSTEM_MESSAGE	WMU_STARTMSGID + CMD_SYSTEM_MESSAGE		// System Message
#define 	WMU_RECEIVE_DATA			WMU_STARTMSGID + CMD_RECEIVE_DATA		// Request�� ��û�� �����͸� �޾��� �� �߻�
#define 	WMU_RECEIVE_REAL_DATA		WMU_STARTMSGID + CMD_RECEIVE_REAL_DATA	// RegistAuto�� ����� �ǽð��� �޾��� �� �߻�
#define 	WMU_LOGIN					WMU_STARTMSGID + CMD_LOGIN				// �����κ��� �α��� ��� �޾����� �߻�
#define 	WMU_LOGOUT					WMU_STARTMSGID + CMD_LOGOUT				// �����κ��� �α׾ƿ� ��� �޾����� �߻�
#define		WMU_RECEIVE_ERROR			WMU_STARTMSGID + CMD_RECEIVE_ERROR		// �����κ��� ������ �޾��� �� �߻�

#endif // _MESSAGEDEF_H_