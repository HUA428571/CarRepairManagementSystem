#pragma once
#include "head.h"

void print_OrderCheckMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_OrderCheckMenu_Visiter_Payed_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu_Visiter_Payed.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_OrderCheckMenu_Visiter_UnPay_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu_Visiter_UnPay.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}

void print_RepairMENU_MainMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_RepairMENU_RepairMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Repair.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_QualityMENU_MainMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\QualityMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_QualityMENU_QualityMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\QualityMENU_Quality.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_ReceptionMENU_MainMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\ReceptionMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_ReceptionMENU_AddMENU_background()
{
	//���ñ���ɫ
	setbkcolor(WHITE);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\ReceptionMENU_AddMENU.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_AdminMENU_MainMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\AdminMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_AdminMENU_PeopleMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\AdminMENU_People.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_StorageMENU_MainMENU_background()
{
	//���ñ���ɫ
	setbkcolor(COLOR_BG);
	//���ñ���
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\StorageMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}



void print_order_id(int x, int y, int OrderID)
{
	//��ӡ������
	char buffer_OrderID[45] = "";
	sprintf(buffer_OrderID, "%d", OrderID);
	int OrderID_length = strlen(buffer_OrderID);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(x - OrderID_length * 15, y, buffer_OrderID);
	return;
}

void print_repair_brief()
{
	IMAGE TodayInfo_Repair;
	loadimage(&TodayInfo_Repair, _T(".\\IMAGES\\TodayInfo_Repair.png"), 440, 580);
	putimage(790, 70, &TodayInfo_Repair);

	int my_order, my_order_finish;

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ʾ��ǰ�û���Ϣ
	char buffer_print_role[45] = "";
	//��ѯ����
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	MatchRole(atoi(row[1]), buffer_print_role);

	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_print_role);
	int username_length = strlen(row[0]);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170 - username_length * 15, 100, row[0]);
	mysql_free_result(res);

	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//�ҵĶ���
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	my_order = atoi(row[0]);

	//����û�ж�������
	if (my_order == 0)
	{
		outtextxy(985, 185, "������");
		outtextxy(985, 215, "������");
		outtextxy(985, 245, "������");
		outtextxy(985, 275, "������");
		outtextxy(855, 415, "������");
		return;
	}
	outtextxy(985, 185, row[0]);

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
	my_order_finish = atoi(row[0]);

	mysql_free_result(res);

	//������
	setlinestyle(PS_NULL);
	setfillcolor(COLOR_GREY_3);
	fillrectangle(855, 415, 855 + 310, 415 + 20);
	setfillcolor(COLOR_RED);
	float finfish = (float)my_order_finish / my_order;
	fillrectangle(855, 415, 855 + 310 * finfish, 415 + 20);
	char finish_buffer[8];
	sprintf(finish_buffer, "%3d%%", 100 * my_order_finish / my_order);
	outtextxy(1125, 385, finish_buffer);

	return;
}
void print_quality_brief()
{
	IMAGE TodayInfo_Quality;
	loadimage(&TodayInfo_Quality, _T(".\\IMAGES\\TodayInfo_Quality.png"), 440, 580);
	putimage(790, 70, &TodayInfo_Quality);

	int my_order, my_order_quality, my_order_finish;
	char print_buffer[64] = "";

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ʾ��ǰ�û���Ϣ
	char buffer_print_role[45] = "";
	//��ѯ����
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	MatchRole(atoi(row[1]), buffer_print_role);

	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_print_role);
	int username_length = strlen(row[0]);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170 - username_length * 15, 100, row[0]);
	mysql_free_result(res);

	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//�ҵĶ���
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	my_order = atoi(row[0]);
	//����û�ж�������
	if (my_order == 0)
	{
		outtextxy(985, 185, "������");
		outtextxy(985, 215, "������");
		outtextxy(985, 245, "������");
		outtextxy(985, 275, "������");
		outtextxy(855, 415, "������");
		return;
	}
	outtextxy(985, 185, row[0]);

	//�ܶ���
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);

	//���ʼ�
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE QualityStaffID=%d AND Status=3;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 245, row[0]);
	my_order_quality = atoi(row[0]);

	//���ʼ�
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE QualityStaffID=%d \
		AND(Status=4 OR Status=5);"
		, UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 275, row[0]);
	my_order_finish = atoi(row[0]);
	my_order_quality += my_order_finish;

	mysql_free_result(res);

	//������
	setlinestyle(PS_NULL);
	setfillcolor(COLOR_GREY_3);
	fillrectangle(855, 415, 855 + 310, 415 + 20);
	if (my_order_quality == 0)
	{
		outtextxy(985, 385, "0");
		return;
	}
	else
	{
		sprintf(print_buffer, "%d", my_order_quality);
		outtextxy(985, 385, print_buffer);
	}
	setfillcolor(COLOR_RED);
	float finfish = (float)my_order_finish / my_order_quality;
	fillrectangle(855, 415, 855 + 310 * finfish, 415 + 20);
	char finish_buffer[8];
	sprintf(finish_buffer, "%3d%%", 100 * my_order_finish / my_order_quality);
	outtextxy(1125, 385, finish_buffer);

	return;
}
void print_reception_brief()
{
	IMAGE TodayInfo_Reception;
	loadimage(&TodayInfo_Reception, _T(".\\IMAGES\\TodayInfo_Reception.png"), 440, 580);
	putimage(790, 70, &TodayInfo_Reception);

	float order_total,order_repair,order_quality,order_unpay,order_payed;
	char print_buffer[64] = "";

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ʾ��ǰ�û���Ϣ
	char buffer_print_role[45] = "";
	//��ѯ����
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	MatchRole(atoi(row[1]), buffer_print_role);

	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_print_role);
	int username_length = strlen(row[0]);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170 - username_length * 15, 100, row[0]);
	mysql_free_result(res);

	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//�ܶ���
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	order_total = atoi(row[0]);
	//û�ж�������
	settextcolor(COLOR_GREY_2);
	if (order_total == 0)
	{
		outtextxy(985, 185, "������");
		outtextxy(855, 240, "������");
		outtextxy(855, 295, "������");
		outtextxy(855, 350, "������");
		outtextxy(855, 405, "������");
		return;
	}
	outtextxy(985, 185, row[0]);

	//�ȴ�ά��
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE (Status=1 OR Status=21 OR Status=22);");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);
	order_repair = atoi(row[0]);

	//�ȴ��ʼ�
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=3;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 270, row[0]);
	order_quality = atoi(row[0]);

	//�ȴ�֧��
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=4;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 325, row[0]);
	order_unpay = atoi(row[0]);

	//�������
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=5;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 380, row[0]);
	order_payed = atoi(row[0]);

	mysql_free_result(res);

	//������
	setlinestyle(PS_NULL);
	setfillcolor(COLOR_GREY_3);
	fillrectangle(855, 240, 855 + 310, 240 + 20);
	fillrectangle(855, 295, 855 + 310, 295 + 20);
	fillrectangle(855, 350, 855 + 310, 350 + 20);
	fillrectangle(855, 405, 855 + 310, 405 + 20);

	setfillcolor(COLOR_BLUE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_repair / order_total);
	outtextxy(1125, 215, print_buffer);
	fillrectangle(855, 240, 855 + 310 * (order_repair / order_total), 240 + 20);

	setfillcolor(COLOR_ORANGE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_quality / order_total);
	outtextxy(1125, 270, print_buffer);
	fillrectangle(855, 295, 855 + 310 * (order_quality / order_total), 295 + 20);

	setfillcolor(COLOR_DEEP_BLUE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_unpay / order_total);
	outtextxy(1125, 325, print_buffer);
	fillrectangle(855, 350, 855 + 310 * (order_unpay / order_total), 350 + 20);

	setfillcolor(COLOR_GREEN);
	sprintf(print_buffer, "%3.0f%%", 100 * order_payed / order_total);
	outtextxy(1125, 380, print_buffer);
	fillrectangle(855, 405, 855 + 310 * (order_payed / order_total), 405 + 20);
	return;
}
void print_storage_brief()
{
	IMAGE TodayInfo_Reception;
	loadimage(&TodayInfo_Reception, _T(".\\IMAGES\\TodayInfo_Storage.png"), 440, 580);
	putimage(790, 70, &TodayInfo_Reception);

	float order_total, order_repair, order_quality, order_unpay, order_payed,part_total,part_require;
	char print_buffer[64] = "";

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ʾ��ǰ�û���Ϣ
	char buffer_print_role[45] = "";
	//��ѯ����
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	MatchRole(atoi(row[1]), buffer_print_role);

	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_print_role);
	int username_length = strlen(row[0]);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170 - username_length * 15, 100, row[0]);
	mysql_free_result(res);

	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//�ܶ���
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	order_total = atoi(row[0]);
	//û�ж�������
	settextcolor(COLOR_GREY_2);
	if (order_total == 0)
	{
		outtextxy(985, 185, "������");
		outtextxy(855, 240, "������");
		outtextxy(855, 295, "������");
		outtextxy(855, 350, "������");
		outtextxy(855, 405, "������");
		return;
	}
	outtextxy(985, 185, row[0]);

	//�ȴ�ά��
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE (Status=1 OR Status=21 OR Status=22);");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);
	order_repair = atoi(row[0]);

	//�ȴ��ʼ�
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=3;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 270, row[0]);
	order_quality = atoi(row[0]);

	//�ȴ�֧��
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=4;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 325, row[0]);
	order_unpay = atoi(row[0]);

	//�������
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=5;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 380, row[0]);
	order_payed = atoi(row[0]);

	//�����
	sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_total = atoi(row[0]);
	//û�ж�������
	settextcolor(COLOR_GREY_2);
	if (part_total == 0)
	{
		outtextxy(985, 515, "������");
		outtextxy(855, 570, "������");
		return;
	}
	outtextxy(985, 515, row[0]);

	//��治��
	sprintf(query_str,
		"SELECT count(*) FROM repair_part_storage WHERE Req>0;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 545, row[0]);
	part_require = atoi(row[0]);

	mysql_free_result(res);

	//������
	setlinestyle(PS_NULL);
	setfillcolor(COLOR_GREY_3);
	fillrectangle(855, 240, 855 + 310, 240 + 20);
	fillrectangle(855, 295, 855 + 310, 295 + 20);
	fillrectangle(855, 350, 855 + 310, 350 + 20);
	fillrectangle(855, 405, 855 + 310, 405 + 20);
	fillrectangle(855, 570, 855 + 310, 570 + 20);

	setfillcolor(COLOR_BLUE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_repair / order_total);
	outtextxy(1125, 215, print_buffer);
	fillrectangle(855, 240, 855 + 310 * (order_repair / order_total), 240 + 20);

	setfillcolor(COLOR_ORANGE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_quality / order_total);
	outtextxy(1125, 270, print_buffer);
	fillrectangle(855, 295, 855 + 310 * (order_quality / order_total), 295 + 20);

	setfillcolor(COLOR_DEEP_BLUE);
	sprintf(print_buffer, "%3.0f%%", 100 * order_unpay / order_total);
	outtextxy(1125, 325, print_buffer);
	fillrectangle(855, 350, 855 + 310 * (order_unpay / order_total), 350 + 20);

	setfillcolor(COLOR_GREEN);
	sprintf(print_buffer, "%3.0f%%", 100 * order_payed / order_total);
	outtextxy(1125, 380, print_buffer);
	fillrectangle(855, 405, 855 + 310 * (order_payed / order_total), 405 + 20);

	setfillcolor(COLOR_RED);
	sprintf(print_buffer, "%3.0f%%", 100 * part_require / part_total);
	outtextxy(1125, 545, print_buffer);
	fillrectangle(855, 570, 855 + 310 * (part_require / part_total), 570 + 20);

	return;
}


void print_order_info(int x, int y, int OrderID)
{
	IMAGE Order_Info_BG;
	loadimage(&Order_Info_BG, _T(".\\IMAGES\\Order_Info_BG.png"), 370, 145);
	putimage(x, y, &Order_Info_BG);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";

	//��ѯ������Ϣ
	sprintf(query_str, "SELECT Status,OrderDate,Plate,VIN FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "�������Ϣ");
		outtextxy(x + 150, y + 65, "�������Ϣ");
		outtextxy(x + 150, y + 95, "�������Ϣ");
		outtextxy(x + 150, y + 125, "�������Ϣ");
	}
	else
	{
		char PrintBuffer[255];
		MatchStatus(atoi(row[0]), PrintBuffer);
		outtextxy(x + 150, y + 35, PrintBuffer);//����״̬
		settextcolor(COLOR_GREY_2);
		outtextxy(x + 150, y + 65, row[1]);//����
		outtextxy(x + 150, y + 95, row[2]);//���ƺ�
		outtextxy(x + 150, y + 125, row[3]);//���ܺ�
	}
	return;
}
void print_description_info(int x, int y, int OrderID)
{
	IMAGE Description_Info_BG;
	loadimage(&Description_Info_BG, _T(".\\IMAGES\\Description_Info_BG.png"), 370, 105);
	putimage(x, y, &Description_Info_BG);
	RECT print_rect;

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";

	//��ѯ������Ϣ
	sprintf(query_str, "SELECT Description FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x, y + 35, "�������Ϣ");
	}
	else
	{
		print_rect = { x, y+35, x + 370, y +35+ 105 };
		drawtext(row[0], &print_rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
	}
	return;
}
void print_quality_detail_info(int x, int y, int OrderID)
{
	IMAGE QualityDetail_Info_BG;
	loadimage(&QualityDetail_Info_BG, _T(".\\IMAGES\\QualityDetail_Info_BG.png"), 370, 105);
	putimage(x, y, &QualityDetail_Info_BG);
	RECT print_rect;

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";

	//��ѯ������Ϣ
	sprintf(query_str, "SELECT QualityDetail FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x, y + 35, "�������Ϣ");
	}
	else
	{
		print_rect = { x, y + 35, x + 370, y + 35 + 105 };
		drawtext(row[0], &print_rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
	}
	return;
}
void print_CarOwner_info(int x, int y, int OrderID)
{
	IMAGE CarOwner_Info_BG;
	loadimage(&CarOwner_Info_BG, _T(".\\IMAGES\\CarOwner_Info_BG.png"), 370, 85);
	putimage(x, y, &CarOwner_Info_BG);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";

	//��ѯ������Ϣ
	sprintf(query_str, "SELECT Owner,Phone FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "�������Ϣ");
		outtextxy(x + 150, y + 65, "�������Ϣ");
	}
	else
	{
		outtextxy(x + 150, y + 35, row[0]);
		outtextxy(x + 150, y + 65, row[1]);
	}
	return;
}
void print_CarOwner_info_safe(int x, int y, int OrderID)
{
	IMAGE CarOwner_Info_BG;
	loadimage(&CarOwner_Info_BG, _T(".\\IMAGES\\CarOwner_Info_BG.png"), 370, 85);
	putimage(x, y, &CarOwner_Info_BG);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";
	char owner_name[32] = "";
	char owner_phone[32] = "";

	//��ѯ������Ϣ
	sprintf(query_str, "SELECT Owner,Phone FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "�������Ϣ");
		outtextxy(x + 150, y + 65, "�������Ϣ");
	}
	else
	{
		strcpy(owner_name, row[0]);
		strcpy(owner_phone, row[1]);
		owner_phone[3] = '*';
		owner_phone[4] = '*';
		owner_phone[5] = '*';
		owner_phone[6] = '*';
		outtextxy(x + 150, y + 35, owner_name);
		outtextxy(x + 150, y + 65, owner_phone);
	}
	return;
}


void print_order_page_repair(int page, int count, int status)
{
	//�������޶�������״̬Ϊ status
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
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//��ѯ����
		if (status == 0)
		{
			sprintf(query_str, 
				"SELECT OrderID,Status,OrderDate,Plate \
				FROM order_list WHERE RepairStaffID=%d \
				ORDER BY OrderID LIMIT %d,1;"
				, UserID, print_row);
		}
		else
		{
			sprintf(query_str, 
				"SELECT OrderID,Status,OrderDate,Plate \
				FROM order_list WHERE RepairStaffID=%d \
				AND (Status=21 OR Status=22 OR Status=1) \
				ORDER BY OrderID LIMIT %d,1;"
				, UserID, print_row);
		}
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
void print_order_page_quality(int page, int count, int status)
{
	//�������޶�������״̬Ϊ status
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
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//��ѯ����
		if (status == 0)
		{
			sprintf(query_str, "SELECT OrderID,Status,OrderDate,Plate FROM order_list \
WHERE QualityStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, print_row);
		}
		else
		{
			sprintf(query_str, "SELECT OrderID,Status,OrderDate,Plate FROM order_list \
WHERE QualityStaffID=%d AND Status=3 ORDER BY OrderID LIMIT %d,1;", UserID, print_row);
		}
		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		int status = atoi(row[1]);
		if (status == 3)
		{
			settextcolor(COLOR_ORANGE);
			outtextxy(x + 500, y + i * 30, "�ʼ�");//�ʼ�
		}
		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "�鿴");//�鿴

		mysql_free_result(res);

		print_row++;
	}
	return;
}
void print_order_page(int page, int count, int status)
{
	//�������޶�������״̬Ϊ status
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
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//��ѯ����
		switch (status)
		{
		case 0:
			sprintf(query_str, 
				"SELECT OrderID,Status,OrderDate,Plate FROM order_list \
				ORDER BY OrderID LIMIT %d,1;", print_row);
			break;
		case 1:
			sprintf(query_str,
				"SELECT OrderID,Status,OrderDate,Plate FROM order_list \
				WHERE (Status=1 OR Status=22 OR Status=21) \
				ORDER BY OrderID LIMIT %d,1;", print_row);
			break;
		case 2:
			sprintf(query_str,
				"SELECT OrderID,Status,OrderDate,Plate FROM order_list \
				WHERE Status=3 \
				ORDER BY OrderID LIMIT %d,1;", print_row);
			break;
		case 3:
			sprintf(query_str,
				"SELECT OrderID,Status,OrderDate,Plate FROM order_list \
				WHERE Status=4 \
				ORDER BY OrderID LIMIT %d,1;", print_row);
			break;
		}
		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

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
	if (row == NULL)
	{
		outtextxy(x, y, "����Ч����");
		return;
	}
	outtextxy(x, y, row[0]);//���

	char PrintBuffer[255];
	MatchStatus(atoi(row[1]), PrintBuffer);
	outtextxy(x + 110, y, PrintBuffer);//����״̬

	settextcolor(COLOR_GREY_2);
	outtextxy(x + 230, y, row[2]);//����
	outtextxy(x + 370, y, row[3]);//���ƺ�

	return;
}


int print_part_page_repair(int page, int count, int OrderID)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 10 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//��ѯ����
		sprintf(query_str,
			"SELECT \
			repair_record.id_RepairRecord, \
			repair_part_storage.PartName, \
			repair_part_storage.Price, \
			repair_record.Num \
			FROM repair_record,repair_part_storage \
			WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
			AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
			, OrderID, print_row);

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total += print_part_rol(x, y + i * 30, row);

		settextcolor(COLOR_RED);
		settextstyle(20, 0, FONT);
		outtextxy(x + 505, y + i * 30, "ɾ��");//ɾ��

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}
int print_part_page_quality(int page, int count, int OrderID)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 10 * (page - 1);
	int price_total = 0;

	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//��ѯ����
		sprintf(query_str,
			"SELECT \
			repair_record.id_RepairRecord, \
			repair_part_storage.PartName, \
			repair_part_storage.Price, \
			repair_record.Num \
			FROM repair_record,repair_part_storage \
			WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
			AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
			, OrderID, print_row);

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total += print_part_rol(x, y + i * 30, row);

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}
int print_part_page_OrderCheckMENU(int page, int count, int OrderID)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 10 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//��ѯ����
		sprintf(query_str,
			"SELECT \
			repair_record.id_RepairRecord, \
			repair_part_storage.PartName, \
			repair_part_storage.Price, \
			repair_record.Num \
			FROM repair_record,repair_part_storage \
			WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
			AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
			, OrderID, print_row);

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total += print_part_rol(x, y + i * 30, row);

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}
int print_part_page_OrderCheckMENU_Visiter(int page, int count, int OrderID)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 7 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//��ʾ��λ
	int x = 160, y = 235;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(160, 235, 160 + 500, 235 + 200);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 7) && (print_row < count); i++)
	{
		//��ѯ����
		sprintf(query_str,
			"SELECT \
			repair_record.id_RepairRecord, \
			repair_part_storage.PartName, \
			repair_part_storage.Price, \
			repair_record.Num \
			FROM repair_record,repair_part_storage \
			WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
			AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
			, OrderID, print_row);

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total += print_part_rol(x, y + i * 30, row);

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}

int print_part_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	if (row == NULL)
	{
		outtextxy(x, y, "����Ч����");
		return 0;
	}
	outtextxy(x, y, row[0]);//���
	outtextxy(x + 90, y, row[1]);//����
	outtextxy(x + 350, y, row[2]);//����
	outtextxy(x + 440, y, row[3]);//����
	return atoi(row[2]);
}


void print_people_page(int page, int count)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 10 * (page - 1);

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 650, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//��ѯ����
		sprintf(query_str,
			"SELECT UserID,  UserName,Name, Role FROM user \
			ORDER BY Role LIMIT %d,1;"
			, print_row);

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_people_rol(x, y + i * 30, row);

		settextcolor(COLOR_ORANGE);
		settextstyle(20, 0, FONT);
		outtextxy(x + 455, y + i * 30, "�޸�����");//�޸�����

		settextcolor(COLOR_RED);
		settextstyle(20, 0, FONT);
		outtextxy(x + 555, y + i * 30, "ɾ��");//ɾ��

		mysql_free_result(res);
		print_row++;
	}
}
void print_people_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	char role_buffer[32] = "";
	if (row == NULL)
	{
		outtextxy(x, y, "����Ч����");
		return ;
	}
	outtextxy(x, y, row[0]);//���
	outtextxy(x + 75, y, row[1]);//�û���
	outtextxy(x + 235, y, row[2]);//����
	MatchRole_with_color(atoi(row[3]), role_buffer);
	outtextxy(x + 335, y, role_buffer);//���
	return ;
}

void print_storage_page(int page, int count, int flag)
{
	//�±궼��0��ʼ������sql��ѯ��
	int print_row = 10 * (page - 1);

	char query_str[512] = "";
	//��ʾ��λ
	int x = 180, y = 185;
	//���������ʾ����
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 650, 185 + 290);
	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);

	//MYsql�Ĳ�ѯ����
	MYSQL_RES* res; //��ѯ�����
	MYSQL_ROW row;  //��¼�ṹ��
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//��ѯ����
		if (flag == 1)
		{
			sprintf(query_str,
				"SELECT RepairPartID, PartName, Price, Num, Req \
				FROM repair_part_storage \
				WHERE Req>0 \
				ORDER BY RepairPartID LIMIT %d,1;"
				, print_row);
		}
		else
		{
			sprintf(query_str,
				"SELECT RepairPartID, PartName, Price, Num, Req \
				FROM repair_part_storage \
				ORDER BY RepairPartID LIMIT %d,1;"
				, print_row);
		}

		mysql_query(&mysql, query_str);
		//��ȡ�����
		res = mysql_store_result(&mysql);
		if (res == NULL)
		{
			outtextxy(x, y + i * 30, "����Ч����");
			return;
		}
		row = mysql_fetch_row(res);

		print_storage_rol(x, y + i * 30, row);

		settextcolor(COLOR_ORANGE);
		settextstyle(20, 0, FONT);
		outtextxy(x + 555, y + i * 30, "�޸�");//ɾ��

		mysql_free_result(res);
		print_row++;
	}
}
void print_storage_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	char role_buffer[32] = "";
	RECT print_rect;
	if (row == NULL)
	{
		outtextxy(x, y, "����Ч����");
		return;
	}					
	print_rect = { x, y, x + 40, y + 20 };
	drawtext(row[0], &print_rect, DT_CENTER | DT_VCENTER);//���
	x += 80;
	print_rect = { x, y, x + 180, y + 20 };
	drawtext(row[1], &print_rect, DT_LEFT | DT_VCENTER);//�������
	x += 220;
	print_rect = { x, y, x + 50, y + 20 };
	drawtext(row[2], &print_rect, DT_CENTER | DT_VCENTER);//�۸�
	if (atoi(row[4]) > 0)
	{
		settextcolor(COLOR_RED);
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER);//���
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[4], &print_rect, DT_CENTER | DT_VCENTER);//����
	}
	else
	{
		settextcolor(COLOR_GREEN);
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER);//���
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext("��", &print_rect, DT_CENTER | DT_VCENTER);//����
	}
	return;
}



