#pragma once
#include "head.h"
#include "print.h"

void print_repair_home_background()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);
	return;
}

void print_repair_repair_background()
{
	cleardevice();
	setbkmode(TRANSPARENT);
	//设置背景色
	setbkcolor(COLOR_BG);
	//设置背景
	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Repair.png"), 1280, 720);
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

	char buffer_role[11] = "";
	MatchRole(Role, buffer_role);
	settextcolor(COLOR_GREY_2);
	settextstyle(18, 0, FONT);
	outtextxy(1080, 82, buffer_role);
	int username_length = strlen(UserName);
	settextcolor(BLACK);
	settextstyle(30, 0, FONT);
	outtextxy(1170 - username_length * 15, 100, UserName);


	settextcolor(BLACK);
	settextstyle(20, 0, FONT);

	//MYsql的查询操作
	MYSQL_RES* res; //查询结果集
	MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";

	//我的订单
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	outtextxy(985, 185, row[0]);
	my_order = atoi(row[0]);

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
	outtextxy(985, 385, row[0]);
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
		outtextxy(x+150, y+35, "无相关信息");
		outtextxy(x+150, y+65, "无相关信息");
		outtextxy(x+150, y+95, "无相关信息");
		outtextxy(x+150, y+125, "无相关信息");
	}
	else
	{
		char PrintBuffer[255];
		MatchStatus(atoi(row[0]), PrintBuffer);
		outtextxy(x + 150, y + 35, PrintBuffer);//订单状态
		settextcolor(COLOR_GREY_2);
		outtextxy(x+150, y+65, row[1]);//日期
		outtextxy(x+150, y+95, row[2]);//车牌号
		outtextxy(x+150, y+125, row[3]);//车架号
	}
	return;
}

void print_description_info(int x, int y, int OrderID)
{
	IMAGE Description_Info_BG;
	loadimage(&Description_Info_BG, _T(".\\IMAGES\\Description_Info_BG.png"), 370, 80);
	putimage(x, y, &Description_Info_BG);

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
		outtextxy(x, y + 35, row[0]);
	}
	return;
}

void print_quality_detail_info(int x, int y, int OrderID)
{
	IMAGE QualityDetail_Info_BG;
	loadimage(&QualityDetail_Info_BG, _T(".\\IMAGES\\QualityDetail_Info_BG.png"), 370, 80);
	putimage(x, y, &QualityDetail_Info_BG);

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
		outtextxy(x, y + 35, row[0]);
	}
	return;
}


void print_order_page_repair(int page, int count)
{
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
		sprintf(query_str, "SELECT OrderID,Status,OrderDate,Plate FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, print_row);
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

void print_order_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
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
repair_record.Number \
FROM repair_record,repair_part_storage \
WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;", OrderID, print_row);

		mysql_query(&mysql, query_str);
		//获取结果集
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		price_total+= print_part_rol(x, y + i * 30, row);

		settextcolor(COLOR_RED);
		settextstyle(20, 0, FONT);
		outtextxy(x + 505, y + i * 30, "删除");//删除

		mysql_free_result(res);
		print_row++;
	}
	return price_total;
}

int print_part_rol(int x, int y, MYSQL_ROW row)
{
	settextcolor(COLOR_GREY_2);
	outtextxy(x, y, row[0]);//编号
	outtextxy(x + 90, y, row[1]);//名称
	outtextxy(x + 350, y, row[2]);//单价
	outtextxy(x + 440, y, row[3]);//件数
	return atoi(row[2]);
}


