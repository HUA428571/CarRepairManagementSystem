#pragma once
#include"head.h"
#include "print.h"

void print_repair_home_background()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}

void print_repair_repair_background()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Repair.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}


void print_repair_brief()
{
	IMAGE TodayInfo_Repair;
	loadimage(&TodayInfo_Repair, _T(".\\IMAGES\\TodayInfo_Repair.png"), 440, 580);
	putimage(790, 70, &TodayInfo_Repair);

	int my_order, my_order_finish;

	char buffer_role[11] = "";
	MatchRole(Role, buffer_role);
	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_role);
	int username_length = strlen(UserName);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170- username_length*15, 100, UserName);


	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";	
	
	//�ҵĶ���
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 185, row[0]);
	my_order = atoi(row[0]);

	//�ܶ���
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);

	//��ά��
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND(Status=1 OR Status=21 OR Status=22);", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 245, row[0]);

	//��ά��
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND(Status=3 OR Status=4 OR Status=5);", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 275, row[0]);
	outtextxy(985, 385, row[0]);
	my_order_finish = atoi(row[0]);

	mysql_free_result(res);	
	
	//������
	setlinestyle(PS_NULL);
	setfillcolor(COLOR_GREY_3);
	fillrectangle(855, 415, 855 + 310, 415 + 20);
	setfillcolor(COLOR_RED);
	float finfish = (float)my_order_finish / my_order;
	fillrectangle(855, 415, 855 + 310* finfish, 415 + 20);
	char finish_buffer[8];
	sprintf(finish_buffer, "%3d%%", 100*my_order_finish / my_order);
	outtextxy(1125, 385, finish_buffer);

	return;
}

void print_order_page_repair(int page, int count)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 13 * (page - 1);

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180,185,780,565);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 13) && (i <= count); i++)
	{
		//��ѯ����
		sprintf(query_str, "SELECT OrderID,Status,OrderDate,Plate FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID,print_row);
		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		int status = atoi(row[1]);
		if (status == 1 || status == 21 || status == 22)
		{
			settextcolor(COLOR_BLUE);
			outtextxy(x + 500, y + i * 30, "ά��");//ά��
		}
		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "�鿴");//�鿴

		mysql_free_result(res);

		print_row++;
	}
	return;
}

void print_order_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	outtextxy(x, y, row[0]);//���

	char PrintBuffer[255];
	MatchStatus(atoi(row[1]), PrintBuffer);
	int status = atoi(row[1]);
	outtextxy(x + 110, y, PrintBuffer);//����״̬

	settextcolor(COLOR_GREY_2);
	outtextxy(x + 230, y, row[2]);//����
	outtextxy(x + 370, y, row[3]);//���ƺ�

	return;
}

void print_part_page_repair(int page, int count)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 13 * (page - 1);

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 780, 565);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 13) && (i <= count); i++)
	{
		//��ѯ����
		sprintf(query_str, "SELECT OrderID,Status,OrderDate,Plate FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, print_row);
		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		int status = atoi(row[1]);
		if (status == 1 || status == 21 || status == 22)
		{
			settextcolor(COLOR_BLUE);
			outtextxy(x + 500, y + i * 30, "ά��");//ά��
		}
		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "�鿴");//�鿴

		mysql_free_result(res);

		print_row++;
	}
	return;
}

void print_part_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	outtextxy(x, y, row[0]);//���

	char PrintBuffer[255];
	MatchStatus(atoi(row[1]), PrintBuffer);
	int status = atoi(row[1]);
	outtextxy(x + 110, y, PrintBuffer);//����״̬

	settextcolor(COLOR_GREY_2);
	outtextxy(x + 230, y, row[2]);//����
	outtextxy(x + 370, y, row[3]);//���ƺ�

	return;
}


