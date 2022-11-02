#pragma once
#include "head.h"

//ƥ�䶩��״̬��״̬���룬����ַ�����
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

//ƥ����Ա���ͣ���Ա���룬����ַ�����
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
void MatchRole_with_color(int role, char* ROLE)
{
	switch (role)
	{
	case 0:
		strcpy(ROLE, "����Ա");
		settextcolor(COLOR_GREEN);
		return;
	case 1:
		strcpy(ROLE, "�Ӵ�רԱ");
		settextcolor(COLOR_PURPLE);
		return;
	case 2:
		strcpy(ROLE, "ά��רԱ");
		settextcolor(COLOR_BLUE);
		return;
	case 3:
		strcpy(ROLE, "�ʼ�רԱ");
		settextcolor(COLOR_ORANGE);
		return;
	case 4:
		strcpy(ROLE, "���רԱ");
		settextcolor(COLOR_RED);
		return;
	default:
		strcpy(ROLE, "����Ϣ");
		return;
	}
}


//�������MySQL��ʽ������
void MatchDate(char* buffer_Date)
{
	time_t NOW;
	tm* Local;
	NOW = time(NULL);
	Local = localtime(&NOW);
	sprintf(buffer_Date, "%04d-%02d-%02d", Local->tm_year + 1900, Local->tm_mon + 1, Local->tm_mday);
	return;
}
