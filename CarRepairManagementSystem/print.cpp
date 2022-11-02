#pragma once
#include "head.h"

void print_OrderCheckMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_OrderCheckMenu_Visiter_Payed_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu_Visiter_Payed.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_OrderCheckMenu_Visiter_UnPay_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\OrderCheckMenu_Visiter_UnPay.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}

void print_RepairMENU_MainMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_RepairMENU_RepairMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Repair.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_QualityMENU_MainMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\QualityMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_QualityMENU_QualityMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\QualityMENU_Quality.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_ReceptionMENU_MainMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\ReceptionMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_ReceptionMENU_AddMENU_background()
{
	//设置背景色
	setbkcolor(WHITE);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\ReceptionMENU_AddMENU.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_AdminMENU_MainMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\AdminMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_AdminMENU_PeopleMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\AdminMENU_People.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}
void print_StorageMENU_MainMENU_background()
{
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\StorageMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}



void print_order_id(int x, int y, int OrderID)
{
	//打印订单号
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

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//显示当前用户信息
	char buffer_print_role[45] = "";
	//查询数据
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
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

	//我的订单
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	my_order = atoi(row[0]);

	//此人没有订单数据
	if (my_order == 0)
	{
		outtextxy(985, 185, "无数据");
		outtextxy(985, 215, "无数据");
		outtextxy(985, 245, "无数据");
		outtextxy(985, 275, "无数据");
		outtextxy(855, 415, "无数据");
		return;
	}
	outtextxy(985, 185, row[0]);

	//总订单
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);

	//待维修
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND(Status=1 OR Status=21 OR Status=22);", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 245, row[0]);

	//已维修
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND(Status=3 OR Status=4 OR Status=5);", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 275, row[0]);
	my_order_finish = atoi(row[0]);

	mysql_free_result(res);

	//进度条
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

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//显示当前用户信息
	char buffer_print_role[45] = "";
	//查询数据
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
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

	//我的订单
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	my_order = atoi(row[0]);
	//此人没有订单数据
	if (my_order == 0)
	{
		outtextxy(985, 185, "无数据");
		outtextxy(985, 215, "无数据");
		outtextxy(985, 245, "无数据");
		outtextxy(985, 275, "无数据");
		outtextxy(855, 415, "无数据");
		return;
	}
	outtextxy(985, 185, row[0]);

	//总订单
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);

	//待质检
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE QualityStaffID=%d AND Status=3;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 245, row[0]);
	my_order_quality = atoi(row[0]);

	//已质检
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE QualityStaffID=%d \
		AND(Status=4 OR Status=5);"
		, UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 275, row[0]);
	my_order_finish = atoi(row[0]);
	my_order_quality += my_order_finish;

	mysql_free_result(res);

	//进度条
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

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//显示当前用户信息
	char buffer_print_role[45] = "";
	//查询数据
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
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

	//总订单
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	order_total = atoi(row[0]);
	//没有订单数据
	settextcolor(COLOR_GREY_2);
	if (order_total == 0)
	{
		outtextxy(985, 185, "无数据");
		outtextxy(855, 240, "无数据");
		outtextxy(855, 295, "无数据");
		outtextxy(855, 350, "无数据");
		outtextxy(855, 405, "无数据");
		return;
	}
	outtextxy(985, 185, row[0]);

	//等待维修
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE (Status=1 OR Status=21 OR Status=22);");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);
	order_repair = atoi(row[0]);

	//等待质检
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=3;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 270, row[0]);
	order_quality = atoi(row[0]);

	//等待支付
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=4;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 325, row[0]);
	order_unpay = atoi(row[0]);

	//订单完成
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=5;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 380, row[0]);
	order_payed = atoi(row[0]);

	mysql_free_result(res);

	//进度条
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

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//显示当前用户信息
	char buffer_print_role[45] = "";
	//查询数据
	sprintf(query_str, "SELECT Name,Role FROM user WHERE UserID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
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

	//总订单
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	order_total = atoi(row[0]);
	//没有订单数据
	settextcolor(COLOR_GREY_2);
	if (order_total == 0)
	{
		outtextxy(985, 185, "无数据");
		outtextxy(855, 240, "无数据");
		outtextxy(855, 295, "无数据");
		outtextxy(855, 350, "无数据");
		outtextxy(855, 405, "无数据");
		return;
	}
	outtextxy(985, 185, row[0]);

	//等待维修
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE (Status=1 OR Status=21 OR Status=22);");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 215, row[0]);
	order_repair = atoi(row[0]);

	//等待质检
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=3;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 270, row[0]);
	order_quality = atoi(row[0]);

	//等待支付
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=4;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 325, row[0]);
	order_unpay = atoi(row[0]);

	//订单完成
	sprintf(query_str,
		"SELECT count(*) FROM order_list \
		WHERE Status=5;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 380, row[0]);
	order_payed = atoi(row[0]);

	//总配件
	sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_total = atoi(row[0]);
	//没有订单数据
	settextcolor(COLOR_GREY_2);
	if (part_total == 0)
	{
		outtextxy(985, 515, "无数据");
		outtextxy(855, 570, "无数据");
		return;
	}
	outtextxy(985, 515, row[0]);

	//库存不足
	sprintf(query_str,
		"SELECT count(*) FROM repair_part_storage WHERE Req>0;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 545, row[0]);
	part_require = atoi(row[0]);

	mysql_free_result(res);

	//进度条
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

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";

	//查询订单信息
	sprintf(query_str, "SELECT Status,OrderDate,Plate,VIN FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "无相关信息");
		outtextxy(x + 150, y + 65, "无相关信息");
		outtextxy(x + 150, y + 95, "无相关信息");
		outtextxy(x + 150, y + 125, "无相关信息");
	}
	else
	{
		char PrintBuffer[255];
		MatchStatus(atoi(row[0]), PrintBuffer);
		outtextxy(x + 150, y + 35, PrintBuffer);//订单状态
		settextcolor(COLOR_GREY_2);
		outtextxy(x + 150, y + 65, row[1]);//日期
		outtextxy(x + 150, y + 95, row[2]);//车牌号
		outtextxy(x + 150, y + 125, row[3]);//车架号
	}
	return;
}
void print_description_info(int x, int y, int OrderID)
{
	IMAGE Description_Info_BG;
	loadimage(&Description_Info_BG, _T(".\\IMAGES\\Description_Info_BG.png"), 370, 105);
	putimage(x, y, &Description_Info_BG);
	RECT print_rect;

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";

	//查询订单信息
	sprintf(query_str, "SELECT Description FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x, y + 35, "无相关信息");
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

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";

	//查询订单信息
	sprintf(query_str, "SELECT QualityDetail FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x, y + 35, "无相关信息");
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

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";

	//查询订单信息
	sprintf(query_str, "SELECT Owner,Phone FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "无相关信息");
		outtextxy(x + 150, y + 65, "无相关信息");
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

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";
	char owner_name[32] = "";
	char owner_phone[32] = "";

	//查询订单信息
	sprintf(query_str, "SELECT Owner,Phone FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);
	if (row == NULL)
	{
		outtextxy(x + 150, y + 35, "无相关信息");
		outtextxy(x + 150, y + 65, "无相关信息");
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
	//本函数限定订单的状态为 status
	//下标都从0开始（方便sql查询）
	int print_row = 13 * (page - 1);

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 780, 565);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		int status = atoi(row[1]);
		if (status == 1 || status == 21 || status == 22)
		{
			settextcolor(COLOR_BLUE);
			outtextxy(x + 500, y + i * 30, "维修");//维修
		}
		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "查看");//查看

		mysql_free_result(res);

		print_row++;
	}
	return;
}
void print_order_page_quality(int page, int count, int status)
{
	//本函数限定订单的状态为 status
	//下标都从0开始（方便sql查询）
	int print_row = 13 * (page - 1);

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 780, 565);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		int status = atoi(row[1]);
		if (status == 3)
		{
			settextcolor(COLOR_ORANGE);
			outtextxy(x + 500, y + i * 30, "质检");//质检
		}
		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "查看");//查看

		mysql_free_result(res);

		print_row++;
	}
	return;
}
void print_order_page(int page, int count, int status)
{
	//本函数限定订单的状态为 status
	//下标都从0开始（方便sql查询）
	int print_row = 13 * (page - 1);

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 780, 565);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 13) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_order_rol(x, y + i * 30, row);

		settextcolor(COLOR_GREEN);
		outtextxy(x + 555, y + i * 30, "查看");//查看

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
		outtextxy(x, y, "无有效数据");
		return;
	}
	outtextxy(x, y, row[0]);//编号

	char PrintBuffer[255];
	MatchStatus(atoi(row[1]), PrintBuffer);
	outtextxy(x + 110, y, PrintBuffer);//订单状态

	settextcolor(COLOR_GREY_2);
	outtextxy(x + 230, y, row[2]);//日期
	outtextxy(x + 370, y, row[3]);//车牌号

	return;
}


int print_part_page_repair(int page, int count, int OrderID)
{
	//下标都从0开始（方便sql查询）
	int print_row = 10 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total += print_part_rol(x, y + i * 30, row);

		settextcolor(COLOR_RED);
		settextstyle(20, 0, FONT);
		outtextxy(x + 505, y + i * 30, "删除");//删除

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}
int print_part_page_quality(int page, int count, int OrderID)
{
	//下标都从0开始（方便sql查询）
	int print_row = 10 * (page - 1);
	int price_total = 0;

	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
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
	//下标都从0开始（方便sql查询）
	int print_row = 10 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 550, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
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
	//下标都从0开始（方便sql查询）
	int print_row = 7 * (page - 1);
	int price_total = 0;

	char query_str[512] = "";
	//显示定位
	int x = 160, y = 235;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(160, 235, 160 + 500, 235 + 200);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 7) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
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
		outtextxy(x, y, "无有效数据");
		return 0;
	}
	outtextxy(x, y, row[0]);//编号
	outtextxy(x + 90, y, row[1]);//名称
	outtextxy(x + 350, y, row[2]);//单价
	outtextxy(x + 440, y, row[3]);//件数
	return atoi(row[2]);
}


void print_people_page(int page, int count)
{
	//下标都从0开始（方便sql查询）
	int print_row = 10 * (page - 1);

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 650, 185 + 290);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//查询数据
		sprintf(query_str,
			"SELECT UserID,  UserName,Name, Role FROM user \
			ORDER BY Role LIMIT %d,1;"
			, print_row);

		mysql_query(&mysql, query_str);
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		print_people_rol(x, y + i * 30, row);

		settextcolor(COLOR_ORANGE);
		settextstyle(20, 0, FONT);
		outtextxy(x + 455, y + i * 30, "修改密码");//修改密码

		settextcolor(COLOR_RED);
		settextstyle(20, 0, FONT);
		outtextxy(x + 555, y + i * 30, "删除");//删除

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
		outtextxy(x, y, "无有效数据");
		return ;
	}
	outtextxy(x, y, row[0]);//编号
	outtextxy(x + 75, y, row[1]);//用户名
	outtextxy(x + 235, y, row[2]);//姓名
	MatchRole_with_color(atoi(row[3]), role_buffer);
	outtextxy(x + 335, y, role_buffer);//身份
	return ;
}

void print_storage_page(int page, int count, int flag)
{
	//下标都从0开始（方便sql查询）
	int print_row = 10 * (page - 1);

	char query_str[512] = "";
	//显示定位
	int x = 180, y = 185;
	//首先清空显示区域
	setbkcolor(COLOR_BG);
	clearrectangle(180, 185, 180 + 650, 185 + 290);
	settextcolor(COLOR_GREY_2);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	for (int i = 0; (i < 10) && (print_row < count); i++)
	{
		//查询数据
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
		//获取结果集
		res = mysql_store_result(&mysql);
		if (res == NULL)
		{
			outtextxy(x, y + i * 30, "无有效数据");
			return;
		}
		row = mysql_fetch_row(res);

		print_storage_rol(x, y + i * 30, row);

		settextcolor(COLOR_ORANGE);
		settextstyle(20, 0, FONT);
		outtextxy(x + 555, y + i * 30, "修改");//删除

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
		outtextxy(x, y, "无有效数据");
		return;
	}					
	print_rect = { x, y, x + 40, y + 20 };
	drawtext(row[0], &print_rect, DT_CENTER | DT_VCENTER);//编号
	x += 80;
	print_rect = { x, y, x + 180, y + 20 };
	drawtext(row[1], &print_rect, DT_LEFT | DT_VCENTER);//配件名称
	x += 220;
	print_rect = { x, y, x + 50, y + 20 };
	drawtext(row[2], &print_rect, DT_CENTER | DT_VCENTER);//价格
	if (atoi(row[4]) > 0)
	{
		settextcolor(COLOR_RED);
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER);//库存
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[4], &print_rect, DT_CENTER | DT_VCENTER);//需求
	}
	else
	{
		settextcolor(COLOR_GREEN);
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER);//库存
		x += 85;
		print_rect = { x, y, x + 50, y + 20 };
		drawtext("无", &print_rect, DT_CENTER | DT_VCENTER);//需求
	}
	return;
}



