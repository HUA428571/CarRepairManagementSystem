#pragma once
#include "head.h"
#include "Function.h"


int OrderCheckMENU(int OrderID)
{
	//打印背景
	print_OrderCheckMENU_background();

	//维修页,显示配件使用信息
	//获取配件使用数
	int part_count;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//工时
	char repair_time[16] = "";
	int part_price_total = calaulate_part_total_price(OrderID);
	int time_price_total = 0;

	char PrintBuffer[255];

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体

	//查询配件使用数量
	char query_str[512] = "";
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_count = atoi(row[0]);

	//查询维修员姓名
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_staff_name, "无信息");
	}
	else
	{
		strcpy(repair_staff_name, row[0]);
	}

	//查询质检员姓名
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(quality_staff_name, "无信息");
	}
	else
	{
		strcpy(quality_staff_name, row[0]);
	}
	mysql_free_result(res);

	//查询工时
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_time, "0");
	}
	else
	{
		strcpy(repair_time, row[0]);
	}
	mysql_free_result(res);
	time_price_total = atoi(repair_time) * tPRICE;

	//打印维修员和质检员信息
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time);
	sprintf(PrintBuffer, "%d", time_price_total);
	outtextxy(510, 580, PrintBuffer);
	sprintf(PrintBuffer, "%d", part_price_total);
	outtextxy(600, 580, PrintBuffer);

	//打印订单号
	print_order_id(1170,100 , OrderID);
	//打印订单信息
	print_order_info(800, 150, OrderID);
	//打印状况描述模块
	print_description_info(800, 330, OrderID);
	//打印质检反馈模块
	print_quality_detail_info(800, 445, OrderID);

	if (part_count == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "暂无相关数据！");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//先打印第一页
		current_page = 1;
		print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
		max_page = (int)((part_count-1) / 10) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//等待鼠标
	int MENUchoice = OrderCheckMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			return MENUchoice;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_repair(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = OrderCheckMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_repair(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = OrderCheckMENU_MENUChoose();
			break;
		}
	}
}

int calaulate_part_total_price(int OrderID)
{
	int total = 0;
	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	sprintf(query_str, 
		"SELECT repair_part_storage.Price,repair_record.Num \
		FROM repair_record, repair_part_storage\
		WHERE repair_record.RepairPartID = repair_part_storage.RepairPartID\
		AND OrderID =%d;", OrderID);
	mysql_query(&mysql, query_str);
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res))
	{
		total += atoi(row[0]) * atoi(row[1]);
	}
	mysql_free_result(res);
	return total;
}