#pragma once
#include "head.h"

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

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
			InputBox_show(buffer_UserName, 12, 530, 310, 270, 30, "");
			setlinecolor(BLACK);
			line(530, 340, 800, 340);
			UserNameCheck = 1;
			MENUchoice = StartMENU_MENUChoose();
			break;
		case 2:
			putimage(470, 370, &PassWordBox);
			InputBox_no_show(PassWord, 12, 530, 390, 270, 30, "");
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
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				return 1;
			}
			row = mysql_fetch_row(res);
			//没有找到相应的订单
			if (row == NULL)
			{
				IMAGE No_Order_fault;
				loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				return 1;
			}
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

int ReceptionMENU_MainMENU()
{
	//接待员主页,显示订单信息
	//获取订单数
	int count_all; //订单总数
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,显示所有订单
	// sort_flag=1,等待维修订单
	// sort_flag=2,等待质检订单
	// sort_flag=3,等待支付订单
	int sort_flag = 0;

	char buffer_input_OrderID[32];
	int OrderID;

	//打印背景
	print_ReceptionMENU_MainMENU_background();
	//打印摘要栏
	print_reception_brief();
	//加载图片
	IMAGE Reception_Order_Page_BAR_0;
	loadimage(&Reception_Order_Page_BAR_0, _T(".\\IMAGES\\Reception_Order_Page_BAR_0.png"), 630, 80);
	IMAGE Reception_Order_Page_BAR_1;
	loadimage(&Reception_Order_Page_BAR_1, _T(".\\IMAGES\\Reception_Order_Page_BAR_1.png"), 630, 80);
	IMAGE Reception_Order_Page_BAR_2;
	loadimage(&Reception_Order_Page_BAR_2, _T(".\\IMAGES\\Reception_Order_Page_BAR_2.png"), 630, 80);
	IMAGE Reception_Order_Page_BAR_3;
	loadimage(&Reception_Order_Page_BAR_3, _T(".\\IMAGES\\Reception_Order_Page_BAR_3.png"), 630, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询数据（全部订单数）
	sprintf(query_str, "SELECT count(*) FROM order_list;");
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
		print_order_page(current_page, count_all, sort_flag);
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
	int MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
	int row_clicked;
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			return 1;
		case 1:
			return 101;
		case 2:
			//查询界面
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "请输入订单号");
			OrderID = atoi(buffer_input_OrderID);
			//查询订单状态
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//获取结果集
			res = mysql_store_result(&mysql);
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			row = mysql_fetch_row(res);
			//没有找到相应的订单
			if (row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			MENUchoice = OrderCheckMENU(OrderID);
			if (MENUchoice == 3)
				MENUchoice = 1;
			break;
		case 4:
			MENUchoice = ReceptionMENU_AddMENU();
			break;
		case 41: //上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 42: //下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//鼠标按在所有订单区域
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 560, &Reception_Order_Page_BAR_0);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM order_list;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//鼠标按在等待维修订单区域
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 560, &Reception_Order_Page_BAR_1);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE (Status=1 OR Status=22 OR Status=21) ;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 45:
			//鼠标按在等待质检订单区域
			if (sort_flag != 2)
			{
				sort_flag = 2;
				putimage(150, 560, &Reception_Order_Page_BAR_2);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=3 ;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 46:
			//鼠标按在等待支付订单区域
			if (sort_flag != 3)
			{
				sort_flag = 3;
				putimage(150, 560, &Reception_Order_Page_BAR_3);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=4;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//重新显示本页信息
			//打印背景
			print_ReceptionMENU_MainMENU_background();
			//打印消息栏
			print_reception_brief();

			switch (sort_flag)
			{
			case 0:
				sort_flag = -1;
				MENUchoice = 43;
				break;
			case 1:
				sort_flag = -1;
				MENUchoice = 44;
				break;
			case 2:
				sort_flag = -1;
				MENUchoice = 45;
				break;
			case 3:
				sort_flag = -1;
				MENUchoice = 46;
				break;
			}
			break;
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
				switch (sort_flag)
				{
				case 0:
					sprintf(query_str,
							"SELECT OrderID FROM order_list \
						ORDER BY OrderID LIMIT % d, 1;",
							row_clicked);
					break;
				case 1:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE (Status=1 OR Status=22 OR Status=21) \
						ORDER BY OrderID LIMIT % d, 1;",
							row_clicked);
					break;
				case 2:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE Status=3 ORDER BY OrderID LIMIT %d,1;",
							row_clicked);
					break;
				case 3:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE Status=4 ORDER BY OrderID LIMIT %d,1;",
							row_clicked);
					break;
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
					print_ReceptionMENU_MainMENU_background();
					switch (sort_flag)
					{
					case 0:
						putimage(150, 560, &Reception_Order_Page_BAR_0);
						break;
					case 1:
						putimage(150, 560, &Reception_Order_Page_BAR_1);
						break;
					case 3:
						putimage(150, 560, &Reception_Order_Page_BAR_2);
						break;
					case 4:
						putimage(150, 560, &Reception_Order_Page_BAR_1);
						break;
					}
					//打印消息栏
					print_reception_brief();
					print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		}
	}
	return 0;
}
int ReceptionMENU_AddMENU()
{
	//接待员添加订单信息

	//打印背景
	print_ReceptionMENU_AddMENU_background();
	//打印摘要栏
	print_reception_brief();

	IMAGE PNG_Right;
	loadimage(&PNG_Right, _T(".\\IMAGES\\Right.png"), 20, 20);
	IMAGE PNG_Wrong;
	loadimage(&PNG_Wrong, _T(".\\IMAGES\\Wrong.png"), 20, 20);
	IMAGE Add_Finished_tip;
	loadimage(&Add_Finished_tip, _T(".\\IMAGES\\Add_Finished_tip.png"), 300, 150);
	IMAGE MySQL_fault;
	loadimage(&MySQL_fault, _T(".\\IMAGES\\MySQL_fault.png"), 450, 250);
	RECT print_rect;

	char buffer_input[256] = "";
	char buffer_Date[128] = "";
	char buffer_Plate[128] = "";
	char buffer_VIM[128] = "";
	char buffer_Owner[128] = "";
	char buffer_Phone[128] = "";
	char buffer_Description[128] = "";
	char buffer_RepairStaffName[128] = "";
	char buffer_QualityStaffName[128] = "";
	int RepairStaffID = 0;
	int QualityStaffID = 0;
	int OrderID;

	bool check_Plate = false;
	bool check_VIM = false;
	bool check_Owner = false;
	bool check_Phone = false;
	bool check_Description = false;
	bool check_RepairStaffID = false;
	bool check_QualityStaffID = false;

	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	MatchDate(buffer_Date);
	outtextxy(333, 185, buffer_Date);

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//等待鼠标
	int MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
			return MENUchoice;
			// MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			// break;
		case 71: //添加车牌号
			InputBox(buffer_input, 9, "请输入车牌号");
			if (strlen(buffer_input) == 8)
			{
				check_Plate = true;
				strcpy(buffer_Plate, buffer_input);
				putimage(313, 215, &PNG_Right);
				clearrectangle(333, 215, 333 + 220, 215 + 20);
				outtextxy(333, 215, buffer_input);
			}
			else
			{
				putimage(313, 215, &PNG_Wrong);
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 72: //添加车架号
			InputBox(buffer_input, 18, "请输入车架号（车辆识别码）");
			if (strlen(buffer_input) == 17)
			{
				check_VIM = true;
				strcpy(buffer_VIM, buffer_input);
				putimage(313, 245, &PNG_Right);
				clearrectangle(333, 245, 333 + 220, 245 + 20);
				outtextxy(333, 245, buffer_input);
			}
			else
			{
				putimage(313, 245, &PNG_Wrong);
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 73: //添加车主信息
			InputBox(buffer_input, 9, "请输入车主姓名");
			if (strlen(buffer_input) > 0)
			{
				check_Owner = true;
				strcpy(buffer_Owner, buffer_input);
				putimage(313, 335, &PNG_Right);
				clearrectangle(333, 335, 333 + 220, 335 + 20);
				outtextxy(333, 335, buffer_input);
			}
			else
			{
				putimage(313, 335, &PNG_Wrong);
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 74: //添加车主手机号
			InputBox(buffer_input, 12, "请输入车主手机号");
			if (strlen(buffer_input) == 11)
			{
				check_Phone = true;
				strcpy(buffer_Phone, buffer_input);
				putimage(313, 365, &PNG_Right);
				clearrectangle(333, 365, 333 + 220, 365 + 20);
				outtextxy(333, 365, buffer_input);
			}
			else
			{
				putimage(313, 365, &PNG_Wrong);
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 75: //添加状况描述
			InputBox(buffer_input, 101, "请输入维修信息描述\n不能超过50字符");
			if (strlen(buffer_input) > 0)
			{
				check_Description = true;
				strcpy(buffer_Description, buffer_input);
				clearrectangle(183, 455, 183 + 370, 455 + 80);
				print_rect = {183, 455, 183 + 370, 455 + 80};
				drawtext(buffer_Description, &print_rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
				putimage(533, 420, &PNG_Right);
			}
			else
			{
				putimage(533, 420, &PNG_Wrong);
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 41: //添加维修员
			InputBox(buffer_input, 9, "请输入维修员姓名");
			if (strlen(buffer_input) > 0)
			{
				strcpy(buffer_RepairStaffName, buffer_input);
				//查询维修人员姓名信息
				sprintf(query_str,
						"SELECT UserID FROM user WHERE Name='%s' AND Role=2 ;", buffer_RepairStaffName);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				if (res != NULL && (row = mysql_fetch_row(res)) != NULL)
				{
					RepairStaffID = atoi(row[0]);
					clearrectangle(183, 592, 183 + 88, 592 + 22);
					settextstyle(22, 0, FONT);
					print_rect = {183, 592, 183 + 88, 592 + 22};
					drawtext(buffer_RepairStaffName, &print_rect, DT_CENTER | DT_VCENTER);
					check_RepairStaffID = true;
				}
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 42: //添加质检员
			InputBox(buffer_input, 9, "请输入维修员姓名");
			if (strlen(buffer_input) > 0)
			{
				strcpy(buffer_QualityStaffName, buffer_input);
				//查询质检人员姓名信息
				sprintf(query_str,
						"SELECT UserID FROM user WHERE Name='%s'AND Role=3;", buffer_QualityStaffName);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				if (res != NULL && (row = mysql_fetch_row(res)) != NULL)
				{
					QualityStaffID = atoi(row[0]);
					clearrectangle(295, 592, 295 + 88, 592 + 22);
					settextstyle(22, 0, FONT);
					print_rect = {295, 592, 295 + 88, 592 + 22};
					drawtext(buffer_QualityStaffName, &print_rect, DT_CENTER | DT_VCENTER);
					check_QualityStaffID = true;
				}
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		case 43: //取消
			return 90;
		case 44: //添加
			if (check_Plate && check_VIM && check_Owner && check_Phone && check_Description && check_RepairStaffID && check_QualityStaffID)
			{
				sprintf(query_str,
						"INSERT INTO order_list \
					(OrderDate, Plate, VIN, Owner, Phone, Description, RepairStaffID, QualityStaffID, Status) \
					VALUES('%s', '%s', '%s', '%s', '%s', '%s', %d, %d, 1);",
						buffer_Date, buffer_Plate, buffer_VIM, buffer_Owner, buffer_Phone,
						buffer_Description, RepairStaffID, QualityStaffID);
				mysql_query(&mysql, query_str);

				//读取订单号并验证插入是否成功
				sprintf(query_str,
						"SELECT OrderID FROM order_list \
					WHERE OrderDate = '%s' \
					AND Plate = '%s' \
					AND VIN = '%s' \
					AND Owner = '%s' \
					AND Phone ='%s' \
					AND Description = '%s' \
					AND RepairStaffID = %d \
					AND QualityStaffID = %d ;",
						buffer_Date, buffer_Plate, buffer_VIM, buffer_Owner, buffer_Phone,
						buffer_Description, RepairStaffID, QualityStaffID);
				mysql_query(&mysql, query_str);

				//获取结果集
				res = mysql_store_result(&mysql);
				//				row = mysql_fetch_row(res);
				if (res != NULL && (row = mysql_fetch_row(res)) != NULL)
				{
					OrderID = atoi(row[0]);
					putimage(490, 285, &Add_Finished_tip);
					settextcolor(BLACK);
					settextstyle(25, 0, FONT);
					outtextxy(640, 380, row[0]);
					Sleep(1500);
				}
				else
				{
					putimage(415, 235, &MySQL_fault);
					print_rect = {429, 311, 429 + 422, 311 + 160};
					settextcolor(COLOR_GREY_2);
					settextstyle(18, 0, FONT);
					drawtext(mysql_error(&mysql), &print_rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
					Sleep(2000);
				}
				return 1;
			}
			MENUchoice = ReceptionMENU_AddMENU_MENUChoose();
			break;
		}
	}
	return 0;
}

int OrderCheckMENU(int OrderID)
{
	//打印背景
	print_OrderCheckMENU_background();
	RECT print_rect;
	int x, y, w, h;

	//维修页,显示配件使用信息
	//获取配件使用数
	int part_count; //配件使用总数
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

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 303;
	print_rect = {x, y, x + w, y + h};
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 434;
	w = 50;
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 519;
	w = 75;
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 612;
	w = 100;
	print_rect = {x, y, x + w, y + h};
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
		case 41: //上一页
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
		case 42: //下一页
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
	int part_count; //配件使用总数
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

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 324;
	//质检员姓名
	print_rect = {x, y, x + w, y + h};
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 474;
	w = 50;
	//工时
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 578;
	w = 75;
	//工费
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 690;
	w = 100;
	//配件费
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 833;
	//费用总计
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 976;
	//已支付
	print_rect = {x, y, x + w, y + h};
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
	print_CarOwner_info_safe(750, 380, OrderID);

	if (part_count == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(160, 235, "暂无相关数据！");
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
		case 41: //上一页
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
		case 42: //下一页
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
	int part_count; //配件使用总数
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

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 289;
	//质检员姓名
	print_rect = {x, y, x + w, y + h};
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 424;
	w = 50;
	//工时
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 513;
	w = 75;
	//工费
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 610;
	w = 100;
	//配件费
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 738;
	//费用总计
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 866;
	//已支付
	print_rect = {x, y, x + w, y + h};
	drawtext("0", &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//打印订单号
	print_order_id(1120, 163, OrderID);
	//打印订单信息
	print_order_info(750, 200, OrderID);
	//打印车主信息模块
	print_CarOwner_info_safe(750, 380, OrderID);

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
		case 41: //上一页
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
		case 42: //下一页
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
	int count_all; //订单总数
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,显示所有订单
	// sort_flag=1,只显示当前身份订单
	int sort_flag = 0;
	char buffer_input_OrderID[32];
	int OrderID;

	//打印背景
	print_RepairMENU_MainMENU_background();
	//加载图片
	IMAGE Repair_Order_Page_BAR_0;
	loadimage(&Repair_Order_Page_BAR_0, _T(".\\IMAGES\\Repair_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Repair_Order_Page_BAR_1;
	loadimage(&Repair_Order_Page_BAR_1, _T(".\\IMAGES\\Repair_Order_Page_BAR_1.png"), 450, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
			return 1;
		case 1:
			return 102;
		case 2:
			//查询界面
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "请输入订单号");
			OrderID = atoi(buffer_input_OrderID);
			//查询订单状态
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//获取结果集
			res = mysql_store_result(&mysql);
			row = mysql_fetch_row(res);
			//没有找到相应的订单
			if (res == NULL || row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				// loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				// putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			MENUchoice = OrderCheckMENU(OrderID);
			if (MENUchoice == 3)
				MENUchoice = 1;
			break;
		case 41: //上一页
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
		case 42: //下一页
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
		case 113: //跳转到维修页面
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
		case 213: //跳转到维修页面
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
					switch (sort_flag)
					{
					case 0:
						putimage(150, 560, &Repair_Order_Page_BAR_0);
						break;
					case 1:
						putimage(150, 560, &Repair_Order_Page_BAR_1);
						break;
					}
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
	int count_all; //配件使用总数
	int current_page = 0;
	int max_page = 0;
	//维修员和质检员姓名
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	int id_RepairRecord; //维修记录编号
	char part_name[60] = "";
	int repair_record_RepairPartID; //维修零件编号
	int repair_record_num;			//维修零件使用数量
	int storage_part_num;			//维修零件库存
	int storage_part_req;
	int add_RepairPartID; //维修零件编号
	int add_part_require;

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
	int row_clicked; //当前行数（对应SQL中）

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
		case 41: //上一页
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
		case 42: //下一页
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
					AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;",
						OrderID, row_clicked);
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
						"DELETE FROM repair_record WHERE id_RepairRecord=%d;", id_RepairRecord);
				mysql_query(&mysql, query_str);

				//更新零件库存信息
				sprintf(query_str,
						"UPDATE repair_part_storage SET Num = %d,Req=%d WHERE RepairPartID =%d;", storage_part_num + repair_record_num, storage_part_req - repair_record_num, repair_record_RepairPartID);
				mysql_query(&mysql, query_str);

				return 99;
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 51:
			//添加配件
			if (InputBox(input_buffer, 19, "请输入要添加的配件名称"))
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

				while (InputBox(input_buffer, 5, "请输入添加配件的数量") == NULL)
					;
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
				outtextxy(190, 580, row[0]);	   //编号
				outtextxy(260, 580, row[1]);	   //名称
				outtextxy(510, 580, input_buffer); //数量
				MENUchoice = RepairMENU_RepairMENU_AddPart_MENUChoose();
				if (MENUchoice == 52)
					return 99;
				if (MENUchoice == 53)
				{
					if (add_part_require > storage_part_num)
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Req = %d WHERE RepairPartID =%d;", storage_part_req + add_part_require, add_RepairPartID);
						mysql_query(&mysql, query_str);
					}
					else
					{
						sprintf(query_str, "UPDATE repair_part_storage SET Num = %d WHERE RepairPartID =%d;", storage_part_num - add_part_require, add_RepairPartID);
						mysql_query(&mysql, query_str);
						sprintf(query_str, "INSERT INTO repair_record (OrderID, RepairPartID, Num) VALUES (%d,%d,%d);", OrderID, add_RepairPartID, add_part_require);
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
			while (InputBox(input_buffer, 6, "更改工时：\n正数增加工时，负数减少工时") == NULL)
				;
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
			// if (InputBox(input_buffer, 140, "140字符以内", "添加维修描述", 0, 0, true))
			//{
			//	sprintf(query_str, "UPDATE order_list SET RepairDetail = %s WHERE OrderID =%d;",input_buffer, OrderID);
			//	mysql_query(&mysql, query_str);
			// }
			//返回
			return 3;
		}
	}
}

int QualityMENU_MainMENU()
{
	//质检员主页,显示订单信息
	//获取订单数
	int count_all; //订单总数
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,显示所有订单
	// sort_flag=1,只显示当前身份订单
	int sort_flag = 0;
	char buffer_input_OrderID[32];
	int OrderID;

	//打印背景
	print_QualityMENU_MainMENU_background();
	//打印摘要栏
	print_quality_brief();
	//加载图片
	IMAGE Quality_Order_Page_BAR_0;
	loadimage(&Quality_Order_Page_BAR_0, _T(".\\IMAGES\\Quality_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Quality_Order_Page_BAR_1;
	loadimage(&Quality_Order_Page_BAR_1, _T(".\\IMAGES\\Quality_Order_Page_BAR_1.png"), 450, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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
			return 1;
		case 1:
			return 103;
		case 2:
			//查询界面
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "请输入订单号");
			OrderID = atoi(buffer_input_OrderID);
			//查询订单状态
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//获取结果集
			res = mysql_store_result(&mysql);
			row = mysql_fetch_row(res);
			//没有找到相应的订单
			if (res == NULL || row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				// loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				// putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			MENUchoice = OrderCheckMENU(OrderID);
			if (MENUchoice == 3)
				MENUchoice = 1;
			break;
		case 41: //上一页
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
		case 42: //下一页
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
					AND Status=3;",
						UserID);
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
						WHERE QualityStaffID=%d ORDER BY OrderID LIMIT %d,1;",
							UserID, row_clicked);
				}
				else
				{
					sprintf(query_str,
							"SELECT Status,OrderID FROM order_list \
						WHERE QualityStaffID=%d AND Status=3 \
						ORDER BY OrderID LIMIT %d,1;",
							UserID, row_clicked);
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
						WHERE QualityStaffID=%d ORDER BY OrderID LIMIT %d,1;",
							UserID, row_clicked);
				}
				else
				{
					sprintf(query_str,
							"SELECT OrderID FROM order_list \
						WHERE QualityStaffID=%d AND (Status=21 OR Status=22 OR Status=1) \
						ORDER BY OrderID LIMIT %d,1;",
							UserID, row_clicked);
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
					switch (sort_flag)
					{
					case 0:
						putimage(150, 560, &Quality_Order_Page_BAR_0);
						break;
					case 1:
						putimage(150, 560, &Quality_Order_Page_BAR_1);
						break;
					}
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
	int count_all; //配件使用总数
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

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
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

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			return MENUchoice;
		case 41: //上一页
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
		case 42: //下一页
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

			if (InputBox(input_buffer, 101, "50字符以内", "添加质检描述", "质检退回维修", 350, 120, true))
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

			if (InputBox(input_buffer, 101, "50字符以内", "添加质检描述", "质检通过", 350, 120, true))
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

int AdminMENU_MainMENU()
{
	//管理员主页,显示订单信息
	//获取订单数
	int count_all; //订单总数
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,显示所有订单
	// sort_flag=1,等待维修订单
	// sort_flag=2,等待质检订单
	// sort_flag=3,等待支付订单
	int sort_flag = 0;

	char buffer_input_OrderID[32];
	int OrderID;

	//打印背景
	print_AdminMENU_MainMENU_background();
	//打印摘要栏
	print_reception_brief();
	//加载图片
	IMAGE Admin_Order_Page_BAR_0;
	loadimage(&Admin_Order_Page_BAR_0, _T(".\\IMAGES\\Admin_Order_Page_BAR_0.png"), 630, 80);
	IMAGE Admin_Order_Page_BAR_1;
	loadimage(&Admin_Order_Page_BAR_1, _T(".\\IMAGES\\Admin_Order_Page_BAR_1.png"), 630, 80);
	IMAGE Admin_Order_Page_BAR_2;
	loadimage(&Admin_Order_Page_BAR_2, _T(".\\IMAGES\\Admin_Order_Page_BAR_2.png"), 630, 80);
	IMAGE Admin_Order_Page_BAR_3;
	loadimage(&Admin_Order_Page_BAR_3, _T(".\\IMAGES\\Admin_Order_Page_BAR_3.png"), 630, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询数据（全部订单数）
	sprintf(query_str, "SELECT count(*) FROM order_list;");
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
		print_order_page(current_page, count_all, sort_flag);
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
	int MENUchoice = AdminMENU_MainMENU_MENUChoose();
	int row_clicked;
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			return 1;
		case 1:
			return 100;
		case 2:
			//查询界面
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "请输入订单号");
			OrderID = atoi(buffer_input_OrderID);
			//查询订单状态
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//获取结果集
			res = mysql_store_result(&mysql);
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				// loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				// putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			row = mysql_fetch_row(res);
			//没有找到相应的订单
			if (row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "无效的订单号");
				// loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				// putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			MENUchoice = OrderCheckMENU(OrderID);
			if (MENUchoice == 3)
				MENUchoice = 1;
			break;
		case 4:
			MENUchoice = AdminMENU_PeopleMENU();
			break;
		case 41: //上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 42: //下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//鼠标按在所有订单区域
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 560, &Admin_Order_Page_BAR_0);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM order_list;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//鼠标按在等待维修订单区域
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 560, &Admin_Order_Page_BAR_1);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE (Status=1 OR Status=22 OR Status=21) ;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 45:
			//鼠标按在等待质检订单区域
			if (sort_flag != 2)
			{
				sort_flag = 2;
				putimage(150, 560, &Admin_Order_Page_BAR_2);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=3 ;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 46:
			//鼠标按在等待支付订单区域
			if (sort_flag != 3)
			{
				sort_flag = 3;
				putimage(150, 560, &Admin_Order_Page_BAR_3);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=4;");
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
					print_order_page(current_page, count_all, sort_flag);
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
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//重新显示本页信息
			//打印背景
			print_AdminMENU_MainMENU_background();
			//打印消息栏
			print_reception_brief();

			switch (sort_flag)
			{
			case 0:
				sort_flag = -1;
				MENUchoice = 43;
				break;
			case 1:
				sort_flag = -1;
				MENUchoice = 44;
				break;
			case 2:
				sort_flag = -1;
				MENUchoice = 45;
				break;
			case 3:
				sort_flag = -1;
				MENUchoice = 46;
				break;
			}
			break;
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
				switch (sort_flag)
				{
				case 0:
					sprintf(query_str,
							"SELECT OrderID FROM order_list \
						ORDER BY OrderID LIMIT % d, 1;",
							row_clicked);
					break;
				case 1:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE (Status=1 OR Status=22 OR Status=21) \
						ORDER BY OrderID LIMIT % d, 1;",
							row_clicked);
					break;
				case 2:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE Status=3 ORDER BY OrderID LIMIT %d,1;",
							row_clicked);
					break;
				case 3:
					sprintf(query_str,
							"SELECT OrderID FROM order_list\
						WHERE Status=4 ORDER BY OrderID LIMIT %d,1;",
							row_clicked);
					break;
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
					print_AdminMENU_MainMENU_background();
					switch (sort_flag)
					{
					case 0:
						putimage(150, 560, &Admin_Order_Page_BAR_0);
						break;
					case 1:
						putimage(150, 560, &Admin_Order_Page_BAR_1);
						break;
					case 3:
						putimage(150, 560, &Admin_Order_Page_BAR_2);
						break;
					case 4:
						putimage(150, 560, &Admin_Order_Page_BAR_1);
						break;
					}
					//打印消息栏
					print_reception_brief();
					print_order_page(current_page, count_all, sort_flag);
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
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		}
	}
	return 0;
}
int AdminMENU_PeopleMENU()
{
	//人员管理界面
	//打印背景
	print_AdminMENU_PeopleMENU_background();
	//打印摘要栏
	print_reception_brief();
	//加载图片
	IMAGE PNG_Right;
	loadimage(&PNG_Right, _T(".\\IMAGES\\Right.png"), 20, 20);
	IMAGE PNG_Wrong;
	loadimage(&PNG_Wrong, _T(".\\IMAGES\\Wrong.png"), 20, 20);
	IMAGE Add_People_Finished_tip;
	loadimage(&Add_People_Finished_tip, _T(".\\IMAGES\\Add_People_Finished_tip.png"), 300, 150);
	IMAGE PassWord_Changed_tip;
	loadimage(&PassWord_Changed_tip, _T(".\\IMAGES\\PassWord_Changed_tip.png"), 300, 150);
	IMAGE MySQL_fault;
	loadimage(&MySQL_fault, _T(".\\IMAGES\\MySQL_fault.png"), 450, 250);
	RECT print_rect;

	int count_all; //人员总数
	int current_page = 0;
	int max_page = 0;
	int select_UserID;
	char buffer_input[256] = "";
	char add_buffer_Name[128] = "";
	char add_buffer_UserName[128] = "";
	char add_buffer_PassWord[128] = "";
	int add_Role = -1;

	bool check_Name = false;
	bool check_UserName = false;
	bool check_PassWord = false;
	bool check_Role = false;

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询人员总数
	sprintf(query_str, "SELECT count(*) FROM user;");
	mysql_query(&mysql, query_str);
	//获取结果集
	//这步操作不可能没有信息（不然你怎么登进来的呢）
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);

	//先打印第一页
	current_page = 1;
	print_people_page(current_page, count_all);
	max_page = (int)((count_all - 1) / 10) + 1;

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
	int MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
	int row_clicked; //当前行数（对应SQL中）

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
			return MENUchoice;
		case 41: //上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_people_page(current_page, count_all);
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
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 42: //下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_people_page(current_page, count_all);
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
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
			//修改密码
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
						"SELECT UserID FROM user ORDER BY UserID LIMIT %d,1;", row_clicked);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				select_UserID = atoi(row[0]);

				InputBox(buffer_input, 13, "请输入新密码");
				if (strlen(buffer_input) != 0)
				{
					sprintf(query_str, "UPDATE user SET PassWord = '%s' WHERE UserID =%d;", buffer_input, select_UserID);
					mysql_query(&mysql, query_str);
					putimage(490, 285, &PassWord_Changed_tip);
					Sleep(1500);
				}
			}
			//重新显示本页
			print_people_page(current_page, count_all);
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
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
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
			//删除
			row_clicked = MENUchoice % 100 + 10 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//当前行
				//查询被点击的ID
				sprintf(query_str,
						"SELECT UserID FROM user ORDER BY UserID LIMIT %d,1;", row_clicked);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				select_UserID = atoi(row[0]);

				//删除该ID
				sprintf(query_str,
						"DELETE FROM user WHERE UserID=%d;", select_UserID);
				mysql_query(&mysql, query_str);

				//返回上一级并重新显示本页
				return 4;
			}
		case 51:
			//添加人员-姓名
			setbkcolor(WHITE);
			InputBox(buffer_input, 9, "请输入人员姓名");
			if (strlen(buffer_input) > 0)
			{
				check_Name = true;
				strcpy(add_buffer_Name, buffer_input);
				putimage(252, 559, &PNG_Right);
				clearrectangle(190, 580, 190 + 88, 580 + 22);
				print_rect = {190, 580, 190 + 88, 580 + 22};
				settextcolor(BLACK);
				settextstyle(22, 0, FONT);
				drawtext(add_buffer_Name, &print_rect, DT_CENTER | DT_VCENTER);
			}
			else
			{
				check_Name = false;
				clearrectangle(190, 580, 190 + 88, 580 + 22);
				putimage(252, 559, &PNG_Wrong);
			}
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 52:
			//添加人员-用户名
			setbkcolor(WHITE);
			InputBox(buffer_input, 13, "请输入用户名\n不应与现有用户名重复");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM user WHERE UserName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				if (res == NULL || row == NULL)
				{
					//没有重复的用户名
					check_UserName = true;
					strcpy(add_buffer_UserName, buffer_input);
					putimage(393, 559, &PNG_Right);
					clearrectangle(300, 580, 300 + 132, 580 + 22);
					print_rect = {300, 580, 300 + 132, 580 + 22};
					settextcolor(BLACK);
					settextstyle(22, 0, FONT);
					drawtext(add_buffer_UserName, &print_rect, DT_CENTER | DT_VCENTER);
					MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
					break;
				}
			}
			check_UserName = false;
			clearrectangle(300, 580, 300 + 132, 580 + 22);
			putimage(393, 559, &PNG_Wrong);
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 53:
			//添加人员-密码
			setbkcolor(WHITE);
			InputBox(buffer_input, 13, "请输入密码");
			if (strlen(buffer_input) > 0)
			{
				check_PassWord = true;
				strcpy(add_buffer_PassWord, buffer_input);
				putimage(500, 559, &PNG_Right);
				clearrectangle(460, 580, 460 + 44, 580 + 22);
				print_rect = {460, 580, 460 + 44, 580 + 22};
				settextcolor(BLACK);
				settextstyle(22, 0, FONT);
				drawtext("****", &print_rect, DT_CENTER | DT_VCENTER);
			}
			else
			{
				check_PassWord = false;
				clearrectangle(460, 580, 460 + 44, 580 + 22);
				putimage(500, 559, &PNG_Wrong);
			}
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 54:
			//身份-接待专员
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(565, 580, "修");
			outtextxy(595, 580, "检");
			outtextxy(625, 580, "库");
			settextcolor(COLOR_PURPLE);
			outtextxy(535, 580, "接");
			add_Role = 1;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 55:
			//身份-维修专员
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "接");
			outtextxy(595, 580, "检");
			outtextxy(625, 580, "库");
			settextcolor(COLOR_BLUE);
			outtextxy(565, 580, "修");
			add_Role = 2;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 56:
			//身份-质检专员
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "接");
			outtextxy(565, 580, "修");
			outtextxy(625, 580, "库");
			settextcolor(COLOR_ORANGE);
			outtextxy(595, 580, "检");
			add_Role = 3;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 57:
			//身份-库管专员
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "接");
			outtextxy(565, 580, "修");
			outtextxy(595, 580, "检");
			settextcolor(COLOR_RED);
			outtextxy(625, 580, "库");
			add_Role = 4;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 58:
			if (check_Name && check_UserName && check_PassWord && check_Role)
			{
				sprintf(query_str,
						"INSERT INTO user \
					(Name, UserName, PassWord, Role) \
					VALUES('%s', '%s', '%s', '%d');",
						add_buffer_Name, add_buffer_UserName, add_buffer_PassWord, add_Role);
				mysql_query(&mysql, query_str);

				//读取订单号并验证插入是否成功
				sprintf(query_str,
						"SELECT UserID FROM user \
					WHERE Name = '%s' \
					AND UserName = '%s' \
					AND PassWord = '%s' \
					AND Role = '%d' ;",
						add_buffer_Name, add_buffer_UserName, add_buffer_PassWord, add_Role);
				mysql_query(&mysql, query_str);

				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				if (res != NULL && row != NULL)
				{
					putimage(490, 285, &Add_People_Finished_tip);
					Sleep(1500);
				}
				else
				{
					putimage(415, 235, &MySQL_fault);
					print_rect = {429, 311, 429 + 422, 311 + 160};
					settextcolor(COLOR_GREY_2);
					settextstyle(18, 0, FONT);
					drawtext(mysql_error(&mysql), &print_rect, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_END_ELLIPSIS);
					Sleep(2000);
				}
				return 4;
			}
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		}
	}
}

int StorageMENU_MainMENU()
{
	//管理员主页,显示订单信息
	//获取订单数
	int count_all; //配件总数
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,显示所有库存
	// sort_flag=1,等待库存不足
	int sort_flag = 0;

	char buffer_input_PartID[32];
	int PartID;
	char page_buffer[8];
	//加载图片
	IMAGE Storage_BAR_0;
	loadimage(&Storage_BAR_0, _T(".\\IMAGES\\Storage_BAR_0.png"), 660, 170);
	IMAGE Storage_BAR_1;
	loadimage(&Storage_BAR_1, _T(".\\IMAGES\\Storage_BAR_1.png"), 660, 170);
	IMAGE Storage_Bar_Add;
	loadimage(&Storage_Bar_Add, _T(".\\IMAGES\\Storage_Bar_Add.png"), 630, 85);
	IMAGE Storage_Bar_Change;
	loadimage(&Storage_Bar_Change, _T(".\\IMAGES\\Storage_Bar_Change.png"), 630, 85);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White_9.png"), 320, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\No_Part_fault.png"), 320, 110);
	IMAGE No_Part_fault;
	loadimage(&No_Part_fault, _T(".\\IMAGES\\No_Part_fault.png"), 300, 150);

	//打印背景
	print_StorageMENU_MainMENU_background();
	//打印摘要栏
	print_storage_brief();

	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";

	//查询数据（全部库存）
	sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	//加载一下底部贴图
	putimage(150, 470, &Storage_BAR_0);
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
		print_storage_page(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 10) + 1;
	}
	//先清空页码区域
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//显示当前页码
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//等待鼠标
	int MENUchoice = StorageMENU_MainMENU_MENUChoose();
	int row_clicked = -1;
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			return 1;
		case 1:
			return 104;
		case 2:
			//查询界面
			if (InputBox(buffer_input_PartID, 19, "请输入配件名称"))
			{
				setbkcolor(COLOR_BG);
				//查询状态
				sprintf(query_str,
						"SELECT RepairPartID, PartName, Price, Num, Req FROM repair_part_storage WHERE PartName='%s';", buffer_input_PartID);
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				if (res == NULL)
				{
					putimage(490, 285, &No_Part_fault);
					Sleep(1500);
					MENUchoice = 1;
					break;
				}
				row = mysql_fetch_row(res);
				//没有找到相应的订单
				if (row == NULL)
				{
					putimage(490, 285, &No_Part_fault);
					Sleep(1500);
					MENUchoice = 1;
					break;
				}
				clearrectangle(180, 185, 180 + 650, 185 + 290);

				settextstyle(20, 0, FONT);
				print_storage_rol(180, 185, row);
				MENUchoice = StorageMENU_ChangeMENU(atoi(row[0]));
				if (MENUchoice == 3)
				{
					MENUchoice = 1;
				}
			}
			else
			{
				MENUchoice = StorageMENU_MainMENU_MENUChoose();
			}
			break;
		case 4:
			//添加配件
			MENUchoice = StorageMENU_AddMENU();
			break;
		case 41: //上一页
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_storage_page(current_page, count_all, sort_flag);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 42: //下一页
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_storage_page(current_page, count_all, sort_flag);
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//鼠标按在所有订单区域
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 470, &Storage_BAR_0);

				//查询数据
				sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 180 + 650, 185 + 290);

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
					print_storage_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 10) + 1;
				}
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//鼠标按在库存不足区域
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 470, &Storage_BAR_1);

				//查询数据
				sprintf(query_str,
						"SELECT count(*) FROM repair_part_storage \
					WHERE Req>0;");
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				mysql_free_result(res);
				count_all = atoi(row[0]);

				setbkcolor(COLOR_BG);
				clearrectangle(180, 185, 180 + 650, 185 + 290);

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
					print_storage_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 10) + 1;
				}
				//先清空页码区域
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//显示当前页码
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 90:
			return 104;
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
			//修改
			//首先判断该页的订单数量
			//当前点击行数（从0开始，整张表）
			row_clicked = MENUchoice % 100 + 10 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				switch (sort_flag)
				{
				case 0:
					sprintf(query_str,
							"SELECT RepairPartID \
						FROM repair_part_storage \
						ORDER BY RepairPartID LIMIT %d,1;",
							row_clicked);
					break;
				case 1:
					sprintf(query_str,
							"SELECT RepairPartID \
						FROM repair_part_storage \
						WHERE Req>0 \
						ORDER BY RepairPartID LIMIT %d,1;",
							row_clicked);
					break;
				}
				mysql_query(&mysql, query_str);
				//获取结果集
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				PartID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = StorageMENU_ChangeMENU(PartID);

				if (MENUchoice == 3)
				{
					//重新显示本页信息
					//打印背景
					print_StorageMENU_MainMENU_background();
					switch (sort_flag)
					{
					case 0:
						putimage(150, 470, &Storage_BAR_0);
						break;
					case 1:
						putimage(150, 470, &Storage_BAR_1);
						break;
					}
					//打印消息栏
					print_storage_brief();
					print_storage_page(current_page, count_all, sort_flag);
					//先清空页码区域
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 500, 230, 520);
					clearrectangle(240, 500, 260, 520);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//显示当前页码
					sprintf(page_buffer, _T("%2d"), current_page);
					outtextxy(210, 500, page_buffer);
					sprintf(page_buffer, _T("%d"), max_page);
					outtextxy(240, 500, page_buffer);
					MENUchoice = StorageMENU_MainMENU_MENUChoose();
					break;
				}
				break;
			}
		}
	}
}

int StorageMENU_ChangeMENU(int PartID)
{
	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";
	char buffer_input[128] = "";
	char buffer_PartName[128] = "";
	char buffer_Print[128] = "";
	int buffer_Price;
	int buffer_Num;
	int buffer_Req;

	IMAGE Storage_Changed_tip;
	loadimage(&Storage_Changed_tip, _T(".\\IMAGES\\Storage_Changed_tip.png"), 300, 150);
	IMAGE Storage_Bar_Change;
	loadimage(&Storage_Bar_Change, _T(".\\IMAGES\\Storage_Bar_Change.png"), 630, 85);
	RECT print_rect;

	putimage(165, 540, &Storage_Bar_Change);

	//显示定位
	int x, y, w, h;

	sprintf(query_str,
			"SELECT RepairPartID, PartName, Price, Num, Req \
		FROM repair_part_storage \
		WHERE RepairPartID=%d;",
			PartID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);

	x = 190;
	y = 580;
	w = 44;
	h = 22;
	settextstyle(22, 0, FONT);
	settextcolor(BLACK);
	print_rect = {x, y, x + w, y + h};
	drawtext(row[0], &print_rect, DT_CENTER | DT_VCENTER); //编号
	x += 64;
	w = 214;
	print_rect = {x, y, x + w, y + h};
	drawtext(row[1], &print_rect, DT_CENTER | DT_VCENTER); //配件名称
	x += 234;
	w = 44;
	print_rect = {x, y, x + w, y + h};
	drawtext(row[2], &print_rect, DT_CENTER | DT_VCENTER); //价格
	if (atoi(row[4]) > 0)
	{
		settextcolor(COLOR_RED);
		x += 64;
		print_rect = {x, y, x + w, y + h};
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER); //库存
	}
	else
	{
		settextcolor(COLOR_GREEN);
		x += 64;
		print_rect = {x, y, x + w, y + h};
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER); //库存
	}
	strcpy(buffer_PartName, row[1]);
	buffer_Price = atoi(row[2]);
	buffer_Num = atoi(row[3]);
	buffer_Req = atoi(row[4]);
	int MENUchoice = StorageMENU_ChangeMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 41:
		case 42:
		case 43:
		case 44:
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
			return MENUchoice;
		case 51:
			//修改名称
			InputBox(buffer_input, 19, "请输入配件名称\n不应与现有名称重复");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM repair_part_storage WHERE PartName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				res = mysql_store_result(&mysql);

				if (mysql_fetch_row(res) == NULL)
				{
					//没有重复的配件名称
					strcpy(buffer_PartName, buffer_input);
					clearrectangle(254, 580, 254 + 214, 580 + 22);
					print_rect = {254, 580, 254 + 214, 580 + 22};
					settextcolor(COLOR_PURPLE);
					settextstyle(22, 0, FONT);
					drawtext(buffer_PartName, &print_rect, DT_CENTER | DT_VCENTER);
				}
				else
				{
					clearrectangle(254, 580, 254 + 214, 580 + 22);
					print_rect = {254, 580, 254 + 214, 580 + 22};
					settextcolor(COLOR_RED);
					settextstyle(22, 0, FONT);
					drawtext("与现有配件名称重复", &print_rect, DT_CENTER | DT_VCENTER);
				}
			}
			MENUchoice = StorageMENU_ChangeMENU_MENUChoose();
			break;
		case 52:
			//修改价格
			InputBox(buffer_input, 5, "请输入配件价格");
			if (strlen(buffer_input) > 0)
			{
				buffer_Price = atoi(buffer_input);
				clearrectangle(488, 580, 488 + 44, 580 + 22);
				print_rect = {488, 580, 488 + 44, 580 + 22};
				settextcolor(COLOR_PURPLE);
				settextstyle(22, 0, FONT);
				drawtext(buffer_input, &print_rect, DT_CENTER | DT_VCENTER);
			}
			MENUchoice = StorageMENU_ChangeMENU_MENUChoose();
			break;
		case 53:
			//修改库存
			InputBox(buffer_input, 5, "请输入库存修改\n正数为增加量，负数为减少量");
			if (strlen(buffer_input) > 0)
			{
				buffer_Num += atoi(buffer_input);
				clearrectangle(552, 580, 552 + 44, 580 + 22);
				print_rect = {552, 580, 552 + 44, 580 + 22};
				settextcolor(COLOR_PURPLE);
				settextstyle(22, 0, FONT);
				sprintf(buffer_Print, "%d", buffer_Num);
				drawtext(buffer_Print, &print_rect, DT_CENTER | DT_VCENTER);
			}
			if (buffer_Num - buffer_Req >= 0)
			{
				buffer_Req = 0;
			}
			MENUchoice = StorageMENU_ChangeMENU_MENUChoose();
			break;
		case 54:
			//修改库存信息
			sprintf(query_str,
					"UPDATE repair_part_storage \
				SET PartName = '%s',Price=%d, Num=%d, Req=%d WHERE RepairPartID =%d;",
					buffer_PartName, buffer_Price, buffer_Num, buffer_Req, PartID);
			mysql_query(&mysql, query_str);
			putimage(490, 285, &Storage_Changed_tip);
			Sleep(1500);
			return 90;
		case 55:
			sprintf(query_str,
					"DELETE FROM repair_part_storage WHERE RepairPartID=%d;", PartID);
			mysql_query(&mysql, query_str);
			return 90;
		}
	}
}

int StorageMENU_AddMENU()
{
	// MYsql的查询操作
	static MYSQL_RES *res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	char query_str[512] = "";
	char buffer_input[128] = "";
	char buffer_Print[128] = "";

	char add_buffer_PartName[128] = "";
	int add_buffer_Price = 0;
	int add_buffer_Num = 0;
	int add_buffer_Req = 0;

	bool check_PartName = false;
	bool check_Price = false;
	bool check_Num = false;

	IMAGE Add_Part_Finished_tip;
	loadimage(&Add_Part_Finished_tip, _T(".\\IMAGES\\Add_Part_Finished_tip.png"), 300, 150);
	IMAGE Storage_Bar_Add;
	loadimage(&Storage_Bar_Add, _T(".\\IMAGES\\Storage_Bar_Add.png"), 630, 85);
	IMAGE Button_Add_Purple;
	loadimage(&Button_Add_Purple, _T(".\\IMAGES\\Button_Add_Purple.png"), 90, 360);
	RECT print_rect;

	putimage(165, 540, &Storage_Bar_Add);
	putimage(60, 60, &Button_Add_Purple);

	int MENUchoice = StorageMENU_AddMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 41:
		case 42:
		case 43:
		case 44:
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
			return MENUchoice;
		case 51:
			//修改名称
			InputBox(buffer_input, 19, "请输入配件名称\n不应与现有名称重复");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM repair_part_storage WHERE PartName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				res = mysql_store_result(&mysql);

				if (mysql_fetch_row(res)==NULL)
				{
					//没有重复的配件名称
					check_PartName = true;
					strcpy(add_buffer_PartName, buffer_input);
					clearrectangle(194, 580, 194 + 270, 580 + 22);
					settextcolor(BLACK);
					settextstyle(22, 0, FONT);
					outtextxy(194, 580, add_buffer_PartName);
				}
				else
				{
					check_PartName = false;
					clearrectangle(194, 580, 194 + 270, 580 + 22);
					settextcolor(COLOR_RED);
					settextstyle(22, 0, FONT);
					outtextxy(194, 580, "与现有配件名称重复");
				}
			}
			MENUchoice = StorageMENU_AddMENU_MENUChoose();
			break;
		case 52:
			//修改价格
			InputBox(buffer_input, 5, "请输入配件价格");
			if (strlen(buffer_input) > 0)
			{
				check_Price = true;
				add_buffer_Price = atoi(buffer_input);
				clearrectangle(472, 580, 472 + 55, 580 + 22);
				print_rect = {472, 580, 472 + 55, 580 + 22};
				settextcolor(BLACK);
				settextstyle(22, 0, FONT);
				drawtext(buffer_input, &print_rect, DT_CENTER | DT_VCENTER);
			}
			else
			{
				check_Price = false;
				clearrectangle(472, 580, 472 + 55, 580 + 22);
			}
			MENUchoice = StorageMENU_AddMENU_MENUChoose();
			break;
		case 53:
			//修改库存
			InputBox(buffer_input, 5, "请输入库存");
			if (strlen(buffer_input) > 0)
			{
				check_Num = true;
				add_buffer_Num = atoi(buffer_input);
				clearrectangle(537, 580, 537 + 55, 580 + 22);
				print_rect = {537, 580, 537 + 55, 580 + 22};
				settextcolor(BLACK);
				settextstyle(22, 0, FONT);
				drawtext(buffer_input, &print_rect, DT_CENTER | DT_VCENTER);
			}
			else
			{
				check_Num = false;
				clearrectangle(537, 580, 537 + 55, 580 + 22);
			}
			MENUchoice = StorageMENU_AddMENU_MENUChoose();
			break;
		case 54:
			return 90;
		case 55:
			if (check_PartName && check_Price && check_Num)
			{
				//修改库存信息
				sprintf(query_str,
						"INSERT INTO repair_part_storage \
					(PartName, Price, Num, Req) \
					VALUES('%s', %d, %d, 0);",
						add_buffer_PartName, add_buffer_Price, add_buffer_Num);
				mysql_query(&mysql, query_str);
				putimage(490, 285, &Add_Part_Finished_tip);
				Sleep(1500);
				return 90;
			}
			else
			{
				MENUchoice = StorageMENU_AddMENU_MENUChoose();
				break;
			}
		}
	}
}
