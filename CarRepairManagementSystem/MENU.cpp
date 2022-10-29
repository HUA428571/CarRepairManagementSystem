#pragma once
#include"head.h"

int startMENU()
{
	cleardevice();
	settextcolor(BLACK);
	setbkcolor(COLOR_WHITE);
	setbkmode(TRANSPARENT);

	IMAGE BG;
	IMAGE UserNameBox;
	IMAGE PassWordBox;
	IMAGE UserNameWrong;
	IMAGE PassWordWrong;
	loadimage(&BG, _T(".\\IMAGES\\StartMenu.png"), 1280, 720);
	loadimage(&UserNameBox, _T(".\\IMAGES\\UserNameBox.png"), 340, 60);
	loadimage(&PassWordBox, _T(".\\IMAGES\\PasswordBox.png"), 340, 60);
	loadimage(&UserNameWrong, _T(".\\IMAGES\\UserNameWrong.png"), 340, 60);
	loadimage(&PassWordWrong, _T(".\\IMAGES\\PasswordWrong.png"), 340, 60);
	putimage(0, 0, &BG);

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	char buffer_UserName[64];
	char buffer_input_OrderID[32];

	char UserNameCheck = 0;
	char PassWord[50];
	int Role = 0;
	int Status;
	int OrderID;

	int MENUchoice;
	MENUchoice = StartMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 1:
			putimage(0, 0, &BG);
			putimage(470, 290, &UserNameBox);
			InputBox_show(buffer_UserName, 40, 530, 310, 270, 30, "");
			setlinecolor(BLACK);
			line(530, 340, 800, 340);
			UserNameCheck = 1;
			MENUchoice = StartMENU_MENUChoose();
			break;
		case 2:
			putimage(470, 370, &PassWordBox);
			InputBox_no_show(PassWord, 40, 530, 390, 270, 30, "");
			setlinecolor(BLACK);
			line(530, 420, 800, 420);
			if (UserNameCheck == 0)
			{
				MENUchoice = StartMENU_MENUChoose();
			}
			else
			{
				Role = CheckID(buffer_UserName, PassWord);
				if (Role >= 0)
					return Role + 100;
				else
				{
					putimage(470, 290, &UserNameWrong);
					putimage(470, 370, &PassWordWrong);
					UserNameCheck = 0;
					MENUchoice = StartMENU_MENUChoose();
				}
			}
			break;
		case 61:
			return 0;
		case 62:
			clearrectangle(236, 644, 124 + 132, 644 + 22);
			InputBox_show(buffer_input_OrderID, 10, 236, 644, 132, 22, "请输入订单号");
			OrderID = atoi(buffer_input_OrderID);
			//查询订单状态
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//获取结果集
			res = mysql_store_result(&mysql);
			//没有找到相应的订单
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				return 1;
			}
			row = mysql_fetch_row(res);
			Status = atoi(row[0]);
			if (Status == 4)
			{
				OrderCheckMenu_Visiter_UnPay(Status, OrderID);
			}
			else
			{
				OrderCheckMenu_Visiter_Payed(Status, OrderID);
			}
			return 1;
		}
	}
}

int OrderCheckMENU(int OrderID)
{
	//打印背景
	print_OrderCheckMENU_background();
	RECT print_rect;
	int x, y, w, h;

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
	int time_price_total = 0;
	//计算配件费
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询配件使用数量
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

	//打印维修员、质检员、工时、工费、配件费信息
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);

	x = 188;
	y = 580;
	w = 100;
	h = 25;
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 303;
	print_rect = { x, y, x + w, y + h };
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 434;
	w = 50;
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 519;
	w = 75;
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 612;
	w = 100;
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//打印订单号
	print_order_id(1170, 100, OrderID);
	//打印订单信息
	print_order_info(800, 150, OrderID);
	//打印状况描述模块
	print_description_info(800, 330, OrderID);
	//打印质检反馈模块
	print_quality_detail_info(800, 479, OrderID);

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
		max_page = (int)((part_count - 1) / 10) + 1;
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
				print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
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
				print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
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
int OrderCheckMenu_Visiter_Payed(int Status, int OrderID)
{
	//打印背景
	print_OrderCheckMenu_Visiter_Payed_background();
	RECT print_rect;
	int x, y, w, h;

	//显示配件使用信息
	//获取配件使用数
	int part_count;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//工时
	char repair_time[16] = "";
	int time_price_total = 0;
	//计算配件费
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询配件使用数量
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

	//打印维修员、质检员、工时、工费、配件费，费用总计，已支付
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);

	x = 190;
	y = 530;
	w = 100;
	h = 25;
	//维修员姓名
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 324;
	//质检员姓名
	print_rect = { x, y, x + w, y + h };
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 474;
	w = 50;
	//工时
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 578;
	w = 75;
	//工费
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 690;
	w = 100;
	//配件费
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 833;
	//费用总计
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 976;
	//已支付
	print_rect = { x, y, x + w, y + h };
	if (Status == 5)
	{
		drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext("0", &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//打印订单号
	print_order_id(1120, 163, OrderID);
	//打印订单信息
	print_order_info(750, 200, OrderID);
	//打印车主信息模块
	print_CarOwner_info(750, 380, OrderID);


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
		print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
		max_page = (int)((part_count - 1) / 7) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(190, 455, 210, 475);
	clearrectangle(220, 455, 240, 475);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(190, 455, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(220, 455, page_buffer);

	//等待鼠标
	int MENUchoice = OrderCheckMENU_Visiter_Payed_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 3:
			return MENUchoice;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_Payed_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_Payed_MENUChoose();
			break;
		}
	}
}
int OrderCheckMenu_Visiter_UnPay(int Status, int OrderID)
{
	//打印背景
	print_OrderCheckMenu_Visiter_UnPay_background();
	RECT print_rect;
	int x, y, w, h;
	//本页图片
	IMAGE Pay_Finished_tip;
	loadimage(&Pay_Finished_tip, _T(".\\IMAGES\\Pay_Finished_tip.png"), 300, 150);

	//显示配件使用信息
	//获取配件使用数
	int part_count;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//工时
	char repair_time[16] = "";
	int time_price_total = 0;
	//计算配件费
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询配件使用数量
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

	//打印维修员、质检员、工时、工费、配件费，费用总计，已支付
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);

	x = 170;
	y = 530;
	w = 100;
	h = 25;
	//维修员姓名
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 289;
	//质检员姓名
	print_rect = { x, y, x + w, y + h };
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 424;
	w = 50;
	//工时
	print_rect = { x, y, x + w, y + h };
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 513;
	w = 75;
	//工费
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 610;
	w = 100;
	//配件费
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 738;
	//费用总计
	print_rect = { x, y, x + w, y + h };
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 866;
	//已支付
	print_rect = { x, y, x + w, y + h };
	drawtext("0", &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//打印订单号
	print_order_id(1120, 163, OrderID);
	//打印订单信息
	print_order_info(750, 200, OrderID);
	//打印车主信息模块
	print_CarOwner_info(750, 380, OrderID);

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
		print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
		max_page = (int)((part_count - 1) / 7) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(190, 455, 210, 475);
	clearrectangle(220, 455, 240, 475);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(190, 455, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(220, 455, page_buffer);

	//等待鼠标
	int MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 3:
			return MENUchoice;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
			break;
		case 43:
			//订单支付

			sprintf(query_str, "UPDATE order_list SET Status = 5 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			putimage(490, 285, &Pay_Finished_tip);
			Sleep(1500);
			//返回
			return 3;
		}
	}
}

int RepairMENU_MainMENU()
{
	//维修员主页,显示订单信息
	//获取订单数
	int count_all;//订单总数
	int count_finish;
	int current_page = 0;
	int max_page = 0;
	//sort_flag=0,显示所有订单
	//sort_flag=1,只显示当前身份订单
	int sort_flag = 0;

	//打印背景
	print_RepairMENU_MainMENU_background();
	//加载图片
	IMAGE Repair_Order_Page_BAR_0;
	loadimage(&Repair_Order_Page_BAR_0, _T(".\\IMAGES\\Repair_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Repair_Order_Page_BAR_1;
	loadimage(&Repair_Order_Page_BAR_1, _T(".\\IMAGES\\Repair_Order_Page_BAR_1.png"), 450, 80);

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询数据
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);
	mysql_free_result(res);

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
		print_order_page_repair(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
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
	int row_clicked;
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			return MENUchoice;
		case 1:
		case 2:
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_repair(current_page, count_all, sort_flag);
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
				print_order_page_repair(current_page, count_all, sort_flag);
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
		case 43:
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 560, &Repair_Order_Page_BAR_0);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 780, 565);

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
					print_order_page_repair(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
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
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 44:
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 560, &Repair_Order_Page_BAR_1);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1);", UserID);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 780, 565);

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
					print_order_page_repair(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
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
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//重新显示本页信息
			//打印背景
			print_RepairMENU_MainMENU_background();
			//打印消息栏
			print_repair_brief();

			if (sort_flag == 0)
			{
				sort_flag = 1;
				MENUchoice = 43;
				break;
			}
			else
			{
				sort_flag = 0;
				MENUchoice = 44;
				break;
			}
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
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				//查询被点击的订单号
				if (sort_flag == 0)
				{
					sprintf(query_str, "SELECT Status,OrderID FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}
				else
				{
					sprintf(query_str, "SELECT Status,OrderID FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1) ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				//如果这个订单不处于维修状态
				int order_status = atoi(row[0]);
				if (order_status == 3 || order_status == 4 || order_status == 5)
				{
					MENUchoice = RepairMENU_MainMENU_MENUChoose();
					break;
				}
				int OrderID = atoi(row[1]);
				mysql_free_result(res);

				MENUchoice = RepairMENU_RepairMENU(OrderID);
				//上一级删除
				//重新加载显示订单维修页
				while (MENUchoice == 99)
				{
					MENUchoice = RepairMENU_RepairMENU(OrderID);
				}
				//上一级返回
				if (MENUchoice == 3)
				{
					MENUchoice = 90;
					break;
				}
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
			//查看
		case 201:
		case 202:
		case 203:
		case 204:
		case 205:
		case 206:
		case 207:
		case 208:
		case 209:
		case 210:
		case 211:
		case 212:
		case 213:					//跳转到维修页面
			//首先判断该页的订单数量
			//当前点击行数（从0开始，整张表）
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				if (sort_flag == 0)
				{
					sprintf(query_str, "SELECT OrderID FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}
				else
				{
					sprintf(query_str, "SELECT OrderID FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1) ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//重新打印本页
					//打印背景
					print_RepairMENU_MainMENU_background();
					//打印消息栏
					print_repair_brief();
					print_order_page_repair(current_page, count_all, sort_flag);
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
				else
				{
					break;
				}
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
	print_RepairMENU_RepairMENU_background();

	//维修页,显示配件使用信息
	//获取配件使用数
	int count_all;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	int id_RepairRecord;			//维修记录编号
	char part_name[60] = "";
	int repair_record_RepairPartID;	//维修零件编号
	int repair_record_num;	//维修零件使用数量
	int part_price;					//维修零件价格
	int storage_part_num;		//维修零件库存
	int storage_part_req;
	int add_RepairPartID;			//维修零件编号
	int add_part_require;

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询配件使用数量
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
		strcpy(repair_time_buffer, "0");
	}
	else
	{
		strcpy(repair_time_buffer, row[0]);
		repair_time = atoi(row[0]);
	}
	mysql_free_result(res);

	//打印维修员和质检员信息
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time_buffer);
	//打印订单号
	print_order_id(1170, 100, OrderID);
	//打印订单信息
	print_order_info(800, 150, OrderID);
	//打印状况描述模块
	print_description_info(800, 330, OrderID);
	//打印质检反馈模块
	print_quality_detail_info(800, 470, OrderID);

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
		max_page = (int)((count_all - 1) / 10) + 1;
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
	int row_clicked;				//当前行数（对应SQL中）

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
			//删除
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
			row_clicked = MENUchoice % 100 + 10 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				//查询被点击的维修记录号
				sprintf(query_str,
					"SELECT \
					repair_record.id_RepairRecord,repair_record.RepairPartID,repair_record.Num, \
					repair_part_storage.Num, repair_part_storage.Req\
					FROM repair_record,repair_part_storage \
					WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
					AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
					, OrderID, row_clicked);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				id_RepairRecord = atoi(row[0]);
				repair_record_RepairPartID = atoi(row[1]);
				repair_record_num = atoi(row[2]);
				storage_part_num = atoi(row[3]);
				storage_part_req = atoi(row[4]);

				mysql_free_result(res);

				//删除该条维修记录
				sprintf(query_str,
					"DELETE FROM repair_record WHERE id_RepairRecord=%d;"
					, id_RepairRecord);
				mysql_query(&mysql, query_str);

				//更新零件库存信息
				sprintf(query_str,
					"UPDATE repair_part_storage SET Num = %d,Req=%d WHERE RepairPartID =%d"
					, storage_part_num + repair_record_num, storage_part_req - repair_record_num, repair_record_RepairPartID);
				mysql_query(&mysql, query_str);

				return 99;
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 51:
			//添加配件
			if (InputBox(input_buffer, 140, "请输入要添加的配件名称"))
			{
				sprintf(query_str, "SELECT RepairPartID,PartName,Num,Req FROM repair_part_storage WHERE PartName='%s';", input_buffer);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				//没有查找到可用的配件
				if (row == NULL)
				{
					IMAGE No_Part_fault;
					loadimage(&No_Part_fault, _T(".\\IMAGES\\No_Part_fault.png"), 300, 150);
					putimage(490, 285, &No_Part_fault);
					Sleep(1500);
					return 99;
				}
				//保存相关数据
				add_RepairPartID = atoi(row[0]);
				strcpy(part_name, row[1]);
				storage_part_num = atoi(row[2]);
				storage_part_req = atoi(row[3]);

				while (InputBox(input_buffer, 4, "请输入添加配件的数量") == NULL);
				add_part_require = atoi(input_buffer);

				if (add_part_require > storage_part_num)
				{
					//库存不足
					//加载背景
					IMAGE Add_Part_Request_BAR;
					loadimage(&Add_Part_Request_BAR, _T(".\\IMAGES\\Add_Part_Request_BAR.png"), 610, 115);
					putimage(150, 525, &Add_Part_Request_BAR);

					IMAGE Part_Not_Sufficient_tip;
					loadimage(&Part_Not_Sufficient_tip, _T(".\\IMAGES\\Part_Not_Sufficient_tip.png"), 300, 150);
					putimage(490, 285, &Part_Not_Sufficient_tip);
				}
				else
				{
					//库存充足
					//加载背景
					IMAGE Add_Part_Add_BAR;
					loadimage(&Add_Part_Add_BAR, _T(".\\IMAGES\\Add_Part_Add_BAR.png"), 610, 115);
					putimage(150, 525, &Add_Part_Add_BAR);
				}

				//输出查询到的配件信息
				settextcolor(BLACK);
				settextstyle(25, 0, FONT);
				outtextxy(190, 580, row[0]);//编号
				outtextxy(260, 580, row[1]);//名称
				outtextxy(510, 580, input_buffer);//数量
				MENUchoice = RepairMENU_RepairMENU_AddPart_MENUChoose();
				if (MENUchoice == 52)
					return 99;
				if (MENUchoice == 53)
				{
					if (add_part_require > storage_part_num)
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Req = %d WHERE RepairPartID =%d", storage_part_req + add_part_require, add_RepairPartID);
						mysql_query(&mysql, query_str);
					}
					else
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Num = %d WHERE RepairPartID =%d", storage_part_num - add_part_require, add_RepairPartID);
						mysql_query(&mysql, query_str);
						sprintf(query_str, "INSERT INTO repair_record (OrderID, RepairPartID, Num) VALUES (%d,%d,%d)", OrderID, add_RepairPartID, add_part_require);
						mysql_query(&mysql, query_str);
					}
					return 99;
				}
				break;
			}
			else
			{
				MENUchoice = RepairMENU_RepairMENU_MENUChoose();
				break;
			}
		case 52:
			//添加工时
			while (InputBox(input_buffer, 6, "更改工时：\n正数增加工时，负数减少工时") == NULL);
			repair_time += atoi(input_buffer);
			sprintf(query_str, "UPDATE order_list SET RepairTime = %d WHERE OrderID =%d;", repair_time, OrderID);
			mysql_query(&mysql, query_str);
			return 99;
		case 53:
			//完成
			sprintf(query_str, "UPDATE order_list SET Status = 3 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			IMAGE Repair_Finished_tip;
			loadimage(&Repair_Finished_tip, _T(".\\IMAGES\\Repair_Finished_tip.png"), 300, 150);
			putimage(490, 285, &Repair_Finished_tip);
			Sleep(1500);
			//if (InputBox(input_buffer, 140, "140字符以内", "添加维修描述", 0, 0, true))
			//{
			//	sprintf(query_str, "UPDATE order_list SET RepairDetail = %s WHERE OrderID =%d;",input_buffer, OrderID);
			//	mysql_query(&mysql, query_str);
			//}
			//返回
			return 3;
		}
	}
}

int QualityMENU_MainMENU()
{
	//质检员主页,显示订单信息
	//获取订单数
	int count_all;//订单总数
	int count_finish;
	int current_page = 0;
	int max_page = 0;
	//sort_flag=0,显示所有订单
	//sort_flag=1,只显示当前身份订单
	int sort_flag = 0;

	//打印背景
	print_QualityMENU_MainMENU_background();
	//打印摘要栏
	print_quality_brief();
	//加载图片
	IMAGE Quality_Order_Page_BAR_0;
	loadimage(&Quality_Order_Page_BAR_0, _T(".\\IMAGES\\Quality_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Quality_Order_Page_BAR_1;
	loadimage(&Quality_Order_Page_BAR_1, _T(".\\IMAGES\\Quality_Order_Page_BAR_1.png"), 450, 80);

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询数据
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);


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
		print_order_page_quality(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//等待鼠标
	int MENUchoice = QualityMENU_MainMENU_MENUChoose();
	int row_clicked;
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			return MENUchoice;
		case 1:
		case 2:
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
		case 41:					//上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_quality(current_page, count_all, sort_flag);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page_quality(current_page, count_all, sort_flag);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
		case 43:
			if (sort_flag == 0)
			{
				MENUchoice = QualityMENU_MainMENU_MENUChoose();
				break;
			}
			else
			{
				sort_flag = 0;
				putimage(150, 560, &Quality_Order_Page_BAR_0);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 780, 565);

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
					print_order_page_quality(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);

				MENUchoice = QualityMENU_MainMENU_MENUChoose();
				break;
			}
		case 44:
			if (sort_flag == 1)
			{
				MENUchoice = QualityMENU_MainMENU_MENUChoose();
				break;
			}
			else
			{
				sort_flag = 1;
				putimage(150, 560, &Quality_Order_Page_BAR_1);

				//查询数据
				sprintf(query_str,
					"SELECT count(*) FROM order_list WHERE QualityStaffID=%d \
					AND Status=3;", UserID);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 780, 565);

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
					print_order_page_quality(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);

				MENUchoice = QualityMENU_MainMENU_MENUChoose();
				break;
			}
		case 90:
			//重新显示本页信息
			//打印背景
			print_QualityMENU_MainMENU_background();
			//打印消息栏
			print_quality_brief();

			if (sort_flag == 0)
			{
				sort_flag = 1;
				MENUchoice = 43;
				break;
			}
			else
			{
				sort_flag = 0;
				MENUchoice = 44;
				break;
			}
			//质检
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
		case 113:
			//跳转到质检页面
			//首先判断该页的订单数量
			//当前点击行数（从0开始，整张表）
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				//查询被点击的订单号
				if (sort_flag == 0)
				{
					sprintf(query_str,
						"SELECT Status,OrderID FROM order_list \
						WHERE QualityStaffID=%d ORDER BY OrderID LIMIT %d,1;"
						, UserID, row_clicked);
				}
				else
				{
					sprintf(query_str,
						"SELECT Status,OrderID FROM order_list \
						WHERE QualityStaffID=%d AND Status=3 \
						ORDER BY OrderID LIMIT %d,1;"
						, UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int order_status = atoi(row[0]);
				int OrderID = atoi(row[1]);
				//如果这个订单不处于质检状态
				if (order_status != 3)
				{
					MENUchoice = QualityMENU_MainMENU_MENUChoose();
					break;
				}
				mysql_free_result(res);

				MENUchoice = QualityMENU_QualityMENU(OrderID);
				//上一级返回
				if (MENUchoice == 3)
				{
					MENUchoice = 90;
					break;
				}
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
			//查看
		case 201:
		case 202:
		case 203:
		case 204:
		case 205:
		case 206:
		case 207:
		case 208:
		case 209:
		case 210:
		case 211:
		case 212:
		case 213:
			//跳转到查看页面
			//首先判断该页的订单数量
			//当前点击行数（从0开始，整张表）
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				if (sort_flag == 0)
				{
					sprintf(query_str,
						"SELECT OrderID FROM order_list \
						WHERE QualityStaffID=%d ORDER BY OrderID LIMIT %d,1;"
						, UserID, row_clicked);
				}
				else
				{
					sprintf(query_str,
						"SELECT OrderID FROM order_list \
						WHERE QualityStaffID=%d AND (Status=21 OR Status=22 OR Status=1) \
						ORDER BY OrderID LIMIT %d,1;"
						, UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//重新显示本页信息
					//打印背景
					print_QualityMENU_MainMENU_background();
					//打印消息栏
					print_quality_brief();
					print_order_page_quality(current_page, count_all, sort_flag);
					//先清空页码区域
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 590, 230, 610);
					clearrectangle(240, 590, 260, 610);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//显示当前页码
					sprintf(page_buffer, _T("%2d"), current_page);
					outtextxy(210, 590, page_buffer);
					sprintf(page_buffer, _T("%d"), max_page);
					outtextxy(240, 590, page_buffer);
				}
				else
				{
					break;
				}
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
		}
	}
	return 0;
}
int QualityMENU_QualityMENU(int OrderID)
{
	//打印背景
	print_QualityMENU_QualityMENU_background();

	//维修页,显示配件使用信息
	//获取配件使用数
	int count_all;//配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	//本页图片
	IMAGE Quality_Return_tip;
	loadimage(&Quality_Return_tip, _T(".\\IMAGES\\Quality_Return_tip.png"), 300, 150);
	IMAGE Quality_Finished_tip;
	loadimage(&Quality_Finished_tip, _T(".\\IMAGES\\Quality_Finished_tip.png"), 300, 150);


	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询配件使用数量
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
		strcpy(repair_staff_name, "无信息");
	else
		strcpy(repair_staff_name, row[0]);

	//查询质检员姓名
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
		strcpy(quality_staff_name, "无信息");
	else
		strcpy(quality_staff_name, row[0]);

	//查询工时
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_time_buffer, "0");
	}
	else
	{
		strcpy(repair_time_buffer, row[0]);
		repair_time = atoi(row[0]);
	}

	mysql_free_result(res);

	//打印维修员和质检员信息
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time_buffer);
	//打印订单号
	print_order_id(1170, 100, OrderID);
	//打印订单信息
	print_order_info(800, 150, OrderID);
	//打印状况描述模块
	print_description_info(800, 330, OrderID);
	//打印质检反馈模块
	print_quality_detail_info(800, 470, OrderID);

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
		print_part_page_quality(current_page, count_all, OrderID);
		max_page = (int)((count_all - 1) / 10) + 1;
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
	int MENUchoice = QualityMENU_QualityMENU_MENUChoose();
	int row_clicked;				//当前行数（对应SQL中）

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
				print_part_page_quality(current_page, count_all, OrderID);
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
			MENUchoice = QualityMENU_QualityMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_quality(current_page, count_all, OrderID);
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
			MENUchoice = QualityMENU_QualityMENU_MENUChoose();
			break;
		case 61:
			//退回维修
			sprintf(query_str, "UPDATE order_list SET Status = 22 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			if (InputBox(input_buffer, 52, "50字符以内", "添加质检描述", "质检退回维修", 350, 120, true))
			{
				sprintf(query_str, "UPDATE order_list SET QualityDetail = '%s' WHERE OrderID =%d;", input_buffer, OrderID);
				mysql_query(&mysql, query_str);
			}

			putimage(490, 285, &Quality_Return_tip);
			Sleep(1500);
			//返回
			return 3;
		case 62:
			//通过质检
			sprintf(query_str, "UPDATE order_list SET Status = 4 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			if (InputBox(input_buffer, 52, "50字符以内", "添加质检描述", "质检通过", 350, 120, true))
			{
				sprintf(query_str, "UPDATE order_list SET QualityDetail = '%s' WHERE OrderID =%d;", input_buffer, OrderID);
				mysql_query(&mysql, query_str);
			}

			putimage(490, 285, &Quality_Finished_tip);
			Sleep(1500);
			//返回
			return 3;
		}
	}
}