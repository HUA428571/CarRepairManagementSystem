#pragma once
#include"head.h"
#define DEBUG

MYSQL mysql;
int UserID;

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

#ifdef DEBUG
	//��DEBUGģʽ��ֱ�ӽ�����Ӧ�Ľ���
	int MENUchoice = 100;
	UserID = 1;
#endif // DEBUG

#ifndef DEBUG
	int MENUchoice = startMENU();
#endif // !DEBUG

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			//�������
			mysql_close(&mysql);

			return 0;
		case 1:
			MENUchoice = startMENU();
			break;
		case 100:
			MENUchoice = AdminMENU_MainMENU();
			break;
		case 101:
			MENUchoice = ReceptionMENU_MainMENU();
			break;
		case 102:
			MENUchoice = RepairMENU_MainMENU();
			break;
		case 103:
			MENUchoice = QualityMENU_MainMENU();
		case 104:

			MENUchoice = 1;
			break;
		case 105:

			MENUchoice = 1;
			break;
		}
	}
}