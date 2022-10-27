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
	int current_page=1;
	int max_page;

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
	max_page = (int)(count_all / 13);

	//打印背景
	print_repair_home_background();
	//打印消息栏
	print_repair_brief();

	//先打印第一页
	print_order_page_repair(current_page, count_all);
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
	_stprintf(page_buffer, _T("%2d"), max_page);
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
			if (current_page != 1)
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
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%2d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 42:					//下一页
			if (current_page != max_page)
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
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%2d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		//case 18:					//按下了返回键，也就是还显示上一次的界面
		//	clearrectangle(1070, 165, 1220, 200);	//开始前把返回区域清空
		//	clearrectangle(380, 200, 1220, 720);	//开始前把显示区域清空
		//	PrintFlightTitle();
		//	PrintMultiFlightPage(ID, DATA, IDcount, SearchReasult, SearchCount, CurrentPage, Page);
		//	MENUchoice = AdminMENU_SearchMENU_MultiFlight_MENUChoose();
		//	break;
		//case 19:					//按起飞时间排序
		//	int SortReasult[999];												//用于存储排序后的顺序，这样就不会更改原有的结构体数组顺序，不影响下标访问。
		//	SortByDepartureTime(ID, SearchReasult, SearchCount, SortReasult);	//冒泡排序法按照时间排序搜索航班结果；注意此函数有重载
		//	return PrintMultiFlight(ID, DATA, IDcount, SortReasult, SearchCount);
		//case 101:
		//case 102:
		//case 103:
		//case 104:
		//case 105:
		//case 106:
		//case 107:
		//case 108:
		//case 109:
		//case 110:
		//case 111:
		//case 112:
		//case 113:
		//case 114:
		//case 115:						//跳转到详情页面
		//	//首先判断该页的航班数量
		//	int Count = (CurrentPage - 1) * 15;//count表示之前页数总计的航班数，即本页航班应该从count+1的下标开始
		//	if ((MENUchoice % 100 + Count) <= SearchCount)
		//	{
		//		cleardevice();
		//		IMAGE Back;
		//		IMAGE TimeAccuracy;
		//		loadimage(&TimeAccuracy, _T(".\\IMAGES\\TimeAccuracy.png"), 200, 40);
		//		loadimage(&Back, _T(".\\IMAGES\\Back.png"), 30, 30);
		//		putimage(0, 0, &BG);										//显示背景
		//		putimage(1280 - 60 - 30, 165, &Back);						//返回键图片
		//		putimage(100, 550, &TimeAccuracy);							//查询正晚点图片
		//		settextstyle(25, 0, FONT);
		//		outtextxy(110, 200, "当前数据库中有");
		//		outtextxy(110, 230, count);
		//		outtextxy(162, 230, "个航线数据");
		//		settextstyle(20, 0, FONT);
		//		outtextxy(380, 170, "共找到");
		//		outtextxy(450, 170, IntChange);
		//		outtextxy(485, 170, "个航班");
		//		PrintFlightDetail(ID, DATA, IDcount, SearchReasult[MENUchoice % 100 + Count - 1]);
		//		PrintTimeAccuracyBar(ID, DATA, SearchReasult[MENUchoice % 100 + Count - 1]);
		//		int MenuCloice;
		//		MenuCloice = AdminMENU_SearchMENU_MultiFlight_FlightDetail_MENUChoose();
		//		if (MenuCloice == 17)
		//		{
		//			MenuCloice = PrintTicket(ID, DATA, SearchReasult[MENUchoice % 100 + Count - 1]);
		//			if (MenuCloice == 18)
		//				break;
		//		}
		//		MENUchoice = MenuCloice;
		//	}
		//	else
		//		MENUchoice = AdminMENU_SearchMENU_MultiFlight_MENUChoose();
			break;
		}
	}










	while (1);

	return 0;









}

int RepairMENU_RepairMENU(int OrderID)
{
	print_repair_repair_background();

	//维修页,显示配件使用信息
	//获取配件使用数
	int count_all;//配件使用总数
	int current_page = 1;
	int max_page;

	//MYsql的查询操作
	static MYSQL_RES* res; //查询结果集
	static MYSQL_ROW row;  //记录结构体
	//查询数据
	char query_str[512] = "";
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//获取结果集
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);
	max_page = (int)(count_all / 10);

	//打印背景
	print_repair_repair_background();

	//先打印第一页
	print_order_page_repair(current_page, count_all);
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
	_stprintf(page_buffer, _T("%2d"), max_page);
	outtextxy(240, 590, page_buffer);







	return 1;
}