#pragma once
#include"head.h"

MYSQL mysql;
int UserID;
//char UserName[46]="";
//int Role;

//MYsql�Ĳ�ѯ����
//MYSQL_RES* res; //��ѯ�����
//MYSQL_ROW row;  //��¼�ṹ��


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

	//initgraph(1280, 720, EW_NOCLOSE);	// ������ͼ���ڣ���СΪ 1280x720 ����
	initgraph(1280, 720);	// ������ͼ���ڣ���СΪ 1280x720 ����
	setbkmode(TRANSPARENT);

	//�����������
	LOGFONT format;
	gettextstyle(&format);						// ��ȡ��ǰ��������
	format.lfQuality = PROOF_QUALITY;			// �������Ч��Ϊ�������  
	format.lfPitchAndFamily = FIXED_PITCH;
	settextstyle(&format);						// ����������ʽ







	UserID = 23;
	//Role = 2;
	//strcpy(UserName, "B19030314");

	//RepairMENU();
	RepairMENU_MainMENU();
	
	mysql_close(&mysql);
	return 0;
}