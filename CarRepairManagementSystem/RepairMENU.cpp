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
	//ά��Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all;//��������
	int count_finish;
	int current_page=1;
	int max_page;

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);
	max_page = (int)(count_all / 13);

	//��ӡ����
	print_repair_home_background();
	//��ӡ��Ϣ��
	print_repair_brief();

	//�ȴ�ӡ��һҳ
	print_order_page_repair(current_page, count_all);
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	_stprintf(page_buffer, _T("%2d"), max_page);
	outtextxy(240, 590, page_buffer);

	//�ȴ����
	int MENUchoice = RepairMENU_MainMENU_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
			return MENUchoice;
		case 41:					//��һҳ
			if (current_page != 1)
			{
				current_page--;
				print_order_page_repair(current_page, count_all);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%2d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 42:					//��һҳ
			if (current_page != max_page)
			{
				current_page++;
				print_order_page_repair(current_page, count_all);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%2d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		//case 18:					//�����˷��ؼ���Ҳ���ǻ���ʾ��һ�εĽ���
		//	clearrectangle(1070, 165, 1220, 200);	//��ʼǰ�ѷ����������
		//	clearrectangle(380, 200, 1220, 720);	//��ʼǰ����ʾ�������
		//	PrintFlightTitle();
		//	PrintMultiFlightPage(ID, DATA, IDcount, SearchReasult, SearchCount, CurrentPage, Page);
		//	MENUchoice = AdminMENU_SearchMENU_MultiFlight_MENUChoose();
		//	break;
		//case 19:					//�����ʱ������
		//	int SortReasult[999];												//���ڴ洢������˳�������Ͳ������ԭ�еĽṹ������˳�򣬲�Ӱ���±���ʡ�
		//	SortByDepartureTime(ID, SearchReasult, SearchCount, SortReasult);	//ð�����򷨰���ʱ������������������ע��˺���������
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
		//case 115:						//��ת������ҳ��
		//	//�����жϸ�ҳ�ĺ�������
		//	int Count = (CurrentPage - 1) * 15;//count��ʾ֮ǰҳ���ܼƵĺ�����������ҳ����Ӧ�ô�count+1���±꿪ʼ
		//	if ((MENUchoice % 100 + Count) <= SearchCount)
		//	{
		//		cleardevice();
		//		IMAGE Back;
		//		IMAGE TimeAccuracy;
		//		loadimage(&TimeAccuracy, _T(".\\IMAGES\\TimeAccuracy.png"), 200, 40);
		//		loadimage(&Back, _T(".\\IMAGES\\Back.png"), 30, 30);
		//		putimage(0, 0, &BG);										//��ʾ����
		//		putimage(1280 - 60 - 30, 165, &Back);						//���ؼ�ͼƬ
		//		putimage(100, 550, &TimeAccuracy);							//��ѯ�����ͼƬ
		//		settextstyle(25, 0, FONT);
		//		outtextxy(110, 200, "��ǰ���ݿ�����");
		//		outtextxy(110, 230, count);
		//		outtextxy(162, 230, "����������");
		//		settextstyle(20, 0, FONT);
		//		outtextxy(380, 170, "���ҵ�");
		//		outtextxy(450, 170, IntChange);
		//		outtextxy(485, 170, "������");
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

	//ά��ҳ,��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int count_all;//���ʹ������
	int current_page = 1;
	int max_page;

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	//��ѯ����
	char query_str[512] = "";
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);
	max_page = (int)(count_all / 10);

	//��ӡ����
	print_repair_repair_background();

	//�ȴ�ӡ��һҳ
	print_order_page_repair(current_page, count_all);
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	_stprintf(page_buffer, _T("%2d"), max_page);
	outtextxy(240, 590, page_buffer);







	return 1;
}