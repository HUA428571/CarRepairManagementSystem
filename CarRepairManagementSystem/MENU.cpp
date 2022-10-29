#pragma once
#include"head.h"

int RepairMENU()
{
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
	//sort_flag=0,显示所有订单
	//sort_flag=1,只显示当前身份订单
	int sort_flag = 0;

	//打印背景
	print_RepairMENU_MainMENU_background();

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
				print_order_page_repair(current_page, count_all,sort_flag);
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
			if (sort_flag == 0)
			{
				MENUchoice = RepairMENU_MainMENU_MENUChoose();
				break;
			}
			else
			{
				sort_flag = 0;

				IMAGE Repair_Order_Page_BAR_0;
				loadimage(&Repair_Order_Page_BAR_0, _T(".\\IMAGES\\Repair_Order_Page_BAR_0.png"), 450, 80);
				putimage(150, 560, &Repair_Order_Page_BAR_0);

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
				break;
			}
		case 44:
			if (sort_flag == 1)
			{
				MENUchoice = RepairMENU_MainMENU_MENUChoose();
				break;
			}
			else
			{
				sort_flag = 1;

				IMAGE Repair_Order_Page_BAR_1;
				loadimage(&Repair_Order_Page_BAR_1, _T(".\\IMAGES\\Repair_Order_Page_BAR_1.png"), 450, 80);
				putimage(150, 560, &Repair_Order_Page_BAR_1);

				//MYsql的查询操作
				static MYSQL_RES* res; //查询结果集
				static MYSQL_ROW row;  //记录结构体
				//查询数据
				char query_str[512] = "";
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
				break;
			}
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
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				char query_str[512] = "";
				MYSQL_RES* res; //查询结果集
				MYSQL_ROW row;  //记录结构体
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
				//重现显示改订单维修页
				while (MENUchoice == 99)
				{
					MENUchoice = RepairMENU_RepairMENU(OrderID);
				}
				//上一级返回
				if (MENUchoice == 3)
				{
					//重新显示本页信息
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
				char query_str[512] = "";
				MYSQL_RES* res; //查询结果集
				MYSQL_ROW row;  //记录结构体
				//查询被点击的订单号
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

				if (MENUchoice != 3)
				{
					break;
				}
				//重新显示本页信息
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
	int RepairPartID;			//维修零件编号
	int id_RepairRecord;//维修记录编号
	int repair_record_RepairPartID;//维修零件编号
	int repair_record_part_number;//维修零件使用数量
	char part_name[60] = "";
	int part_price;//维修零件价格
	int storage_part_number;//维修零件库存
	int storage_part_require;
	int part_require;

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
				char query_str[512] = "";
				MYSQL_RES* res; //查询结果集
				MYSQL_ROW row;  //记录结构体
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
				repair_record_part_number = atoi(row[2]);
				storage_part_number = atoi(row[3]);
				storage_part_require = atoi(row[4]);

				mysql_free_result(res);

				//删除该条维修记录
				sprintf(query_str,
					"DELETE FROM repair_record WHERE id_RepairRecord=%d;"
					, id_RepairRecord);
				mysql_query(&mysql, query_str);

				//更新零件库存信息
				sprintf(query_str,
					"UPDATE repair_part_storage SET Num = %d,Req=%d WHERE RepairPartID =%d"
					, storage_part_number + repair_record_part_number, storage_part_require - repair_record_part_number, repair_record_RepairPartID);
				mysql_query(&mysql, query_str);


				return 99;
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 51:
			//添加配件
			if (InputBox(input_buffer, 140, "请输入要添加的配件名称"))
			{
				//MYsql的查询操作
				static MYSQL_RES* res; //查询结果集
				static MYSQL_ROW row;  //记录结构体

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
				RepairPartID = atoi(row[0]);
				strcpy(part_name, row[1]);
				storage_part_number = atoi(row[2]);
				storage_part_require = atoi(row[3]);

				while (InputBox(input_buffer, 4, "请输入添加配件的数量") == NULL);
				part_require = atoi(input_buffer);

				if (part_require > storage_part_number)
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
					if (part_require > storage_part_number)
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Req = %d WHERE RepairPartID =%d", storage_part_require + part_require, RepairPartID);
						mysql_query(&mysql, query_str);
					}
					else
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Num = %d WHERE RepairPartID =%d", storage_part_number - part_require, RepairPartID);
						mysql_query(&mysql, query_str);
						sprintf(query_str, "INSERT INTO repair_record (OrderID, RepairPartID, Num) VALUES (%d,%d,%d)", OrderID, RepairPartID, part_require);
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