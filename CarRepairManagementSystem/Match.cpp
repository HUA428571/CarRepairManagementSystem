#pragma once
#include "head.h"

//ƥ��״̬��״̬���룬����ַ�����
void MatchStatus(int status, char* STATUS)
{
	switch (status)
	{
	case 1:
		strcpy(STATUS, "��������"); 
		settextcolor(COLOR_PURPLE);
		return;
	case 21:
		strcpy(STATUS, "�ȴ����");
		settextcolor(COLOR_BLUE);
		return;
	case 22:
		strcpy(STATUS, "�ʼ��˻�");
		settextcolor(COLOR_RED);
		return;
	case 3:
		strcpy(STATUS, "�ȴ��ʼ�");
		settextcolor(COLOR_ORANGE);
		return;
	case 4:
		strcpy(STATUS, "��֧��");
		settextcolor(COLOR_DEEP_BLUE);
		return;
	case 5:
		strcpy(STATUS, "�������");
		settextcolor(COLOR_GREEN);
		return;
	default:
		strcpy(STATUS, "��״̬��Ϣ");
		settextcolor(COLOR_GREY_2);
		return;
	}
}

//ƥ����Ա����Ա���룬����ַ�����
void MatchRole(int role, char* ROLE)
{
	switch (role)
	{
	case 0:
		strcpy(ROLE, "    ����Ա");
		return;
	case 1:
		strcpy(ROLE, "  �Ӵ�רԱ");
		return;
	case 2:
		strcpy(ROLE, "  ά��רԱ");
		return;
	case 3:
		strcpy(ROLE, "  �ʼ�רԱ");
		return;
	case 4:
		strcpy(ROLE, "  ���רԱ");
		return;
	default:
		strcpy(ROLE, "����Ա��Ϣ");
		return;
	}
}
