#pragma once
#include"head.h"
//# define HEAD
//#include <time.h>
//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <stdlib.h>
//
//#include <graphics.h>
//#include <easyx.h>
//#include <conio.h>
//#include <mysql.h>
//using namespace std;
//MYSQL mysql;
//#define FONT "����"

int main()
{
	//��ʼ�����ݿ�
	mysql_init(&mysql);
	//�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	if (mysql_real_connect(&mysql, "127.0.0.1", "B19030314", "B19030314", "curriculum_design_202210", 3306, NULL, 0) == NULL) {
		printf("���� %s\n", mysql_error(&mysql));
		printf("���ݿ�����ʧ�ܣ�\n");
		exit(-1);
	}



	//��ʱ���Դ���
	initgraph(1280, 720, EW_NOCLOSE);	// ������ͼ���ڣ���СΪ 1280x720 ����
	cleardevice();
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT format;
	gettextstyle(&format);						// ��ȡ��ǰ��������
	format.lfHeight = 30;						// ��������߶�Ϊ30
	format.lfQuality = PROOF_QUALITY;			// �������Ч��Ϊ�������  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T("����"));	// ��������ΪFONT2_EN
	settextstyle(&format);						// ����������ʽ

	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);

	settextstyle(20, 0, FONT);
	//outtextxy(180, 185, mysql_error(&mysql));
	outtextxy(180, 215, "���ӳɹ�");
	//outtextxy(100, 130, "ע��ɹ� 1  23456789");

	while(1);


	return 0;
}