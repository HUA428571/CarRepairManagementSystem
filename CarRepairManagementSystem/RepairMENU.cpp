#pragma once
#include"head.h"

int RepairMENU()
{
	print_repair_home_background();
	//setbkcolor(COLOR_BG);
	//cleardevice();


	RepairMENU_MainMENU();


	while (1);

	return 0;
}

int RepairMENU_MainMENU()
{
	//维修员主页,显示订单信息
	//获取订单数
	int count_all;//订单总数
	int count_finish;
	int current_page = 0;
	int max_page = 0;

	//打印背景
	print_repair_home_background();

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	//打印摘要栏
	print_repair_brief();

	if (count_all == 0)
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
		print_order_page_repair(current_page, count_all);
		max_page = (int)(count_all / 13) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//等待鼠标
	int MENUchoice = RepairMENU_MainMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
			return MENUchoice;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_repair(current_page, count_all);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page_repair(current_page, count_all);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
			//维修
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
		case 106:
		case 107:
		case 108:
		case 109:
		case 110:
		case 111:
		case 112:
		case 113:					//跳转到维修页面
			//首先判断该页的订单数量
			//当前点击行数（从0开始，整张表）
			int row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				char query_str[512] = "";
				MYSQL_RES* res; //查询结果集
				MYSQL_ROW row;  //记录结构体
				//查询被点击的订单号
				sprintf(query_str, "SELECT OrderID FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = RepairMENU_RepairMENU(OrderID);

				if (MENUchoice != 3)
				{
					break;
				}
				//重新显示本页信息
				//打印背景
				print_repair_home_background();
				//打印消息栏
				print_repair_brief();
				print_order_page_repair(current_page, count_all);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		}
	}
	return 0;
}

int RepairMENU_RepairMENU(int OrderID)
{
	//打印背景
	print_repair_repair_background();

	//维修页,显示配件使用信息
	//获取配件使用数
	int count_all;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time[16] = "";

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
	count_all = atoi(row[0]);

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

	//打印维修员和质检员信息
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time);
	//打印订单号
	print_order_id(1170, 113, OrderID);
	//打印订单信息
	print_order_info(800, 150, OrderID);
	//打印状况描述模块
	print_description_info(800, 330, OrderID);
	//打印质检反馈模块
	print_quality_detail_info(800, 445, OrderID);

	if (count_all == 0)
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
		print_part_page_repair(current_page, count_all, OrderID);
		max_page = (int)(count_all / 10) + 1;
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
	int MENUchoice = RepairMENU_RepairMENU_MENUChoose();
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
				print_part_page_repair(current_page, count_all, OrderID);
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
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_repair(current_page, count_all, OrderID);
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
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		}
	}
}