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

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
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
			InputBox_show(buffer_input_OrderID, 10, 236, 644, 132, 22, "�����붩����");
			OrderID = atoi(buffer_input_OrderID);
			//��ѯ����״̬
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//��ȡ�����
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
			//û���ҵ���Ӧ�Ķ���
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
	//�Ӵ�Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all; //��������
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,��ʾ���ж���
	// sort_flag=1,�ȴ�ά�޶���
	// sort_flag=2,�ȴ��ʼ충��
	// sort_flag=3,�ȴ�֧������
	int sort_flag = 0;

	char buffer_input_OrderID[32];
	int OrderID;

	//��ӡ����
	print_ReceptionMENU_MainMENU_background();
	//��ӡժҪ��
	print_reception_brief();
	//����ͼƬ
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

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ݣ�ȫ����������
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_order_page(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//�ȴ����
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
			//��ѯ����
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "�����붩����");
			OrderID = atoi(buffer_input_OrderID);
			//��ѯ����״̬
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//��ȡ�����
			res = mysql_store_result(&mysql);
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			row = mysql_fetch_row(res);
			//û���ҵ���Ӧ�Ķ���
			if (row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//��갴�����ж�������
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 560, &Reception_Order_Page_BAR_0);

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM order_list;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//��갴�ڵȴ�ά�޶�������
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 560, &Reception_Order_Page_BAR_1);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE (Status=1 OR Status=22 OR Status=21) ;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 45:
			//��갴�ڵȴ��ʼ충������
			if (sort_flag != 2)
			{
				sort_flag = 2;
				putimage(150, 560, &Reception_Order_Page_BAR_2);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=3 ;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 46:
			//��갴�ڵȴ�֧����������
			if (sort_flag != 3)
			{
				sort_flag = 3;
				putimage(150, 560, &Reception_Order_Page_BAR_3);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=4;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = ReceptionMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//������ʾ��ҳ��Ϣ
			//��ӡ����
			print_ReceptionMENU_MainMENU_background();
			//��ӡ��Ϣ��
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
			//��ת���鿴ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
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
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//������ʾ��ҳ��Ϣ
					//��ӡ����
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
					//��ӡ��Ϣ��
					print_reception_brief();
					print_order_page(current_page, count_all, sort_flag);
					//�����ҳ������
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 590, 230, 610);
					clearrectangle(240, 590, 260, 610);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//��ʾ��ǰҳ��
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
	//�Ӵ�Ա��Ӷ�����Ϣ

	//��ӡ����
	print_ReceptionMENU_AddMENU_background();
	//��ӡժҪ��
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

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//�ȴ����
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
		case 71: //��ӳ��ƺ�
			InputBox(buffer_input, 9, "�����복�ƺ�");
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
		case 72: //��ӳ��ܺ�
			InputBox(buffer_input, 18, "�����복�ܺţ�����ʶ���룩");
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
		case 73: //��ӳ�����Ϣ
			InputBox(buffer_input, 9, "�����복������");
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
		case 74: //��ӳ����ֻ���
			InputBox(buffer_input, 12, "�����복���ֻ���");
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
		case 75: //���״������
			InputBox(buffer_input, 101, "������ά����Ϣ����\n���ܳ���50�ַ�");
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
		case 41: //���ά��Ա
			InputBox(buffer_input, 9, "������ά��Ա����");
			if (strlen(buffer_input) > 0)
			{
				strcpy(buffer_RepairStaffName, buffer_input);
				//��ѯά����Ա������Ϣ
				sprintf(query_str,
						"SELECT UserID FROM user WHERE Name='%s' AND Role=2 ;", buffer_RepairStaffName);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
		case 42: //����ʼ�Ա
			InputBox(buffer_input, 9, "������ά��Ա����");
			if (strlen(buffer_input) > 0)
			{
				strcpy(buffer_QualityStaffName, buffer_input);
				//��ѯ�ʼ���Ա������Ϣ
				sprintf(query_str,
						"SELECT UserID FROM user WHERE Name='%s'AND Role=3;", buffer_QualityStaffName);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
		case 43: //ȡ��
			return 90;
		case 44: //���
			if (check_Plate && check_VIM && check_Owner && check_Phone && check_Description && check_RepairStaffID && check_QualityStaffID)
			{
				sprintf(query_str,
						"INSERT INTO order_list \
					(OrderDate, Plate, VIN, Owner, Phone, Description, RepairStaffID, QualityStaffID, Status) \
					VALUES('%s', '%s', '%s', '%s', '%s', '%s', %d, %d, 1);",
						buffer_Date, buffer_Plate, buffer_VIM, buffer_Owner, buffer_Phone,
						buffer_Description, RepairStaffID, QualityStaffID);
				mysql_query(&mysql, query_str);

				//��ȡ�����Ų���֤�����Ƿ�ɹ�
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

				//��ȡ�����
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
	//��ӡ����
	print_OrderCheckMENU_background();
	RECT print_rect;
	int x, y, w, h;

	//ά��ҳ,��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int part_count; //���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//��ʱ
	char repair_time[16] = "";
	int time_price_total = 0;
	//���������
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ʹ������
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_count = atoi(row[0]);

	//��ѯά��Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(repair_staff_name, row[0]);
	}

	//��ѯ�ʼ�Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(quality_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(quality_staff_name, row[0]);
	}
	mysql_free_result(res);

	//��ѯ��ʱ
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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

	//��ӡά��Ա���ʼ�Ա����ʱ�����ѡ��������Ϣ
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

	//��ӡ������
	print_order_id(1170, 100, OrderID);
	//��ӡ������Ϣ
	print_order_info(800, 150, OrderID);
	//��ӡ״������ģ��
	print_description_info(800, 330, OrderID);
	//��ӡ�ʼ췴��ģ��
	print_quality_detail_info(800, 479, OrderID);

	if (part_count == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
		max_page = (int)((part_count - 1) / 10) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//�ȴ����
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = OrderCheckMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_OrderCheckMENU(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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
	//��ӡ����
	print_OrderCheckMenu_Visiter_Payed_background();
	RECT print_rect;
	int x, y, w, h;

	//��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int part_count; //���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//��ʱ
	char repair_time[16] = "";
	int time_price_total = 0;
	//���������
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ʹ������
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_count = atoi(row[0]);

	//��ѯά��Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(repair_staff_name, row[0]);
	}

	//��ѯ�ʼ�Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(quality_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(quality_staff_name, row[0]);
	}
	mysql_free_result(res);

	//��ѯ��ʱ
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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

	//��ӡά��Ա���ʼ�Ա����ʱ�����ѡ�����ѣ������ܼƣ���֧��
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);

	x = 190;
	y = 530;
	w = 100;
	h = 25;
	//ά��Ա����
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 324;
	//�ʼ�Ա����
	print_rect = {x, y, x + w, y + h};
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 474;
	w = 50;
	//��ʱ
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 578;
	w = 75;
	//����
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 690;
	w = 100;
	//�����
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 833;
	//�����ܼ�
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 976;
	//��֧��
	print_rect = {x, y, x + w, y + h};
	if (Status == 5)
	{
		drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext("0", &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//��ӡ������
	print_order_id(1120, 163, OrderID);
	//��ӡ������Ϣ
	print_order_info(750, 200, OrderID);
	//��ӡ������Ϣģ��
	print_CarOwner_info_safe(750, 380, OrderID);

	if (part_count == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(160, 235, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
		max_page = (int)((part_count - 1) / 7) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(190, 455, 210, 475);
	clearrectangle(220, 455, 240, 475);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(190, 455, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(220, 455, page_buffer);

	//�ȴ����
	int MENUchoice = OrderCheckMENU_Visiter_Payed_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 3:
			return MENUchoice;
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_Payed_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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
	//��ӡ����
	print_OrderCheckMenu_Visiter_UnPay_background();
	RECT print_rect;
	int x, y, w, h;
	//��ҳͼƬ
	IMAGE Pay_Finished_tip;
	loadimage(&Pay_Finished_tip, _T(".\\IMAGES\\Pay_Finished_tip.png"), 300, 150);

	//��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int part_count; //���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	//��ʱ
	char repair_time[16] = "";
	int time_price_total = 0;
	//���������
	int part_price_total = calaulate_part_total_price(OrderID);

	char PrintBuffer[255];

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ʹ������
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	part_count = atoi(row[0]);

	//��ѯά��Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(repair_staff_name, row[0]);
	}

	//��ѯ�ʼ�Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(quality_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(quality_staff_name, row[0]);
	}
	mysql_free_result(res);

	//��ѯ��ʱ
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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

	//��ӡά��Ա���ʼ�Ա����ʱ�����ѡ�����ѣ������ܼƣ���֧��
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);

	x = 170;
	y = 530;
	w = 100;
	h = 25;
	//ά��Ա����
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 289;
	//�ʼ�Ա����
	print_rect = {x, y, x + w, y + h};
	drawtext(quality_staff_name, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 424;
	w = 50;
	//��ʱ
	print_rect = {x, y, x + w, y + h};
	drawtext(repair_time, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 513;
	w = 75;
	//����
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 610;
	w = 100;
	//�����
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 738;
	//�����ܼ�
	print_rect = {x, y, x + w, y + h};
	sprintf(PrintBuffer, "%d", part_price_total + time_price_total);
	drawtext(PrintBuffer, &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	x = 866;
	//��֧��
	print_rect = {x, y, x + w, y + h};
	drawtext("0", &print_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//��ӡ������
	print_order_id(1120, 163, OrderID);
	//��ӡ������Ϣ
	print_order_info(750, 200, OrderID);
	//��ӡ������Ϣģ��
	print_CarOwner_info_safe(750, 380, OrderID);

	if (part_count == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
		max_page = (int)((part_count - 1) / 7) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(190, 455, 210, 475);
	clearrectangle(220, 455, 240, 475);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(190, 455, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(220, 455, page_buffer);

	//�ȴ����
	int MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
	while (true)
	{
		switch (MENUchoice)
		{
		case 3:
			return MENUchoice;
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_OrderCheckMENU_Visiter(current_page, part_count, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(190, 455, 210, 475);
				clearrectangle(220, 455, 240, 475);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(190, 455, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(220, 455, page_buffer);
			}
			MENUchoice = OrderCheckMENU_Visiter_UnPay_MENUChoose();
			break;
		case 43:
			//����֧��

			sprintf(query_str, "UPDATE order_list SET Status = 5 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			putimage(490, 285, &Pay_Finished_tip);
			Sleep(1500);
			//����
			return 3;
		}
	}
}

int RepairMENU_MainMENU()
{
	//ά��Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all; //��������
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,��ʾ���ж���
	// sort_flag=1,ֻ��ʾ��ǰ��ݶ���
	int sort_flag = 0;
	char buffer_input_OrderID[32];
	int OrderID;

	//��ӡ����
	print_RepairMENU_MainMENU_background();
	//����ͼƬ
	IMAGE Repair_Order_Page_BAR_0;
	loadimage(&Repair_Order_Page_BAR_0, _T(".\\IMAGES\\Repair_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Repair_Order_Page_BAR_1;
	loadimage(&Repair_Order_Page_BAR_1, _T(".\\IMAGES\\Repair_Order_Page_BAR_1.png"), 450, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ����
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);
	mysql_free_result(res);

	//��ӡժҪ��
	print_repair_brief();

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_order_page_repair(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
	}
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
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//�ȴ����
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
			//��ѯ����
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "�����붩����");
			OrderID = atoi(buffer_input_OrderID);
			//��ѯ����״̬
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//��ȡ�����
			res = mysql_store_result(&mysql);
			row = mysql_fetch_row(res);
			//û���ҵ���Ӧ�Ķ���
			if (res == NULL || row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_repair(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page_repair(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d;", UserID);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page_repair(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
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

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1);", UserID);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page_repair(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
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
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//������ʾ��ҳ��Ϣ
			//��ӡ����
			print_RepairMENU_MainMENU_background();
			//��ӡ��Ϣ��
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
		case 113: //��ת��ά��ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				//��ѯ������Ķ�����
				if (sort_flag == 0)
				{
					sprintf(query_str, "SELECT Status,OrderID FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}
				else
				{
					sprintf(query_str, "SELECT Status,OrderID FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1) ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				//����������������ά��״̬
				int order_status = atoi(row[0]);
				if (order_status == 3 || order_status == 4 || order_status == 5)
				{
					MENUchoice = RepairMENU_MainMENU_MENUChoose();
					break;
				}
				int OrderID = atoi(row[1]);
				mysql_free_result(res);

				MENUchoice = RepairMENU_RepairMENU(OrderID);
				//��һ��ɾ��
				//���¼�����ʾ����ά��ҳ
				while (MENUchoice == 99)
				{
					MENUchoice = RepairMENU_RepairMENU(OrderID);
				}
				//��һ������
				if (MENUchoice == 3)
				{
					MENUchoice = 90;
					break;
				}
			}
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
			//�鿴
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
		case 213: //��ת��ά��ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				if (sort_flag == 0)
				{
					sprintf(query_str, "SELECT OrderID FROM order_list WHERE RepairStaffID=%d ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}
				else
				{
					sprintf(query_str, "SELECT OrderID FROM order_list WHERE RepairStaffID=%d AND (Status=21 OR Status=22 OR Status=1) ORDER BY OrderID LIMIT %d,1;", UserID, row_clicked);
				}

				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//���´�ӡ��ҳ
					//��ӡ����
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
					//��ӡ��Ϣ��
					print_repair_brief();
					print_order_page_repair(current_page, count_all, sort_flag);
					//�����ҳ������
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 590, 230, 610);
					clearrectangle(240, 590, 260, 610);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//��ʾ��ǰҳ��
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
	//��ӡ����
	print_RepairMENU_RepairMENU_background();

	//ά��ҳ,��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int count_all; //���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	int id_RepairRecord; //ά�޼�¼���
	char part_name[60] = "";
	int repair_record_RepairPartID; //ά��������
	int repair_record_num;			//ά�����ʹ������
	int storage_part_num;			//ά��������
	int storage_part_req;
	int add_RepairPartID; //ά��������
	int add_part_require;

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ʹ������
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);

	//��ѯά��Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(repair_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(repair_staff_name, row[0]);
	}

	//��ѯ�ʼ�Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
	{
		strcpy(quality_staff_name, "����Ϣ");
	}
	else
	{
		strcpy(quality_staff_name, row[0]);
	}
	mysql_free_result(res);

	//��ѯ��ʱ
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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

	//��ӡά��Ա���ʼ�Ա��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time_buffer);
	//��ӡ������
	print_order_id(1170, 100, OrderID);
	//��ӡ������Ϣ
	print_order_info(800, 150, OrderID);
	//��ӡ״������ģ��
	print_description_info(800, 330, OrderID);
	//��ӡ�ʼ췴��ģ��
	print_quality_detail_info(800, 470, OrderID);

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_part_page_repair(current_page, count_all, OrderID);
		max_page = (int)((count_all - 1) / 10) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//�ȴ����
	int MENUchoice = RepairMENU_RepairMENU_MENUChoose();
	int row_clicked; //��ǰ��������ӦSQL�У�

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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_repair(current_page, count_all, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_repair(current_page, count_all, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
			//ɾ��
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
				//��ǰ��
				//��ѯ�������ά�޼�¼��
				sprintf(query_str,
						"SELECT \
					repair_record.id_RepairRecord,repair_record.RepairPartID,repair_record.Num, \
					repair_part_storage.Num, repair_part_storage.Req\
					FROM repair_record,repair_part_storage \
					WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
					AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;",
						OrderID, row_clicked);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				id_RepairRecord = atoi(row[0]);
				repair_record_RepairPartID = atoi(row[1]);
				repair_record_num = atoi(row[2]);
				storage_part_num = atoi(row[3]);
				storage_part_req = atoi(row[4]);

				mysql_free_result(res);

				//ɾ������ά�޼�¼
				sprintf(query_str,
						"DELETE FROM repair_record WHERE id_RepairRecord=%d;", id_RepairRecord);
				mysql_query(&mysql, query_str);

				//������������Ϣ
				sprintf(query_str,
						"UPDATE repair_part_storage SET Num = %d,Req=%d WHERE RepairPartID =%d;", storage_part_num + repair_record_num, storage_part_req - repair_record_num, repair_record_RepairPartID);
				mysql_query(&mysql, query_str);

				return 99;
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 51:
			//������
			if (InputBox(input_buffer, 19, "������Ҫ��ӵ��������"))
			{
				sprintf(query_str, "SELECT RepairPartID,PartName,Num,Req FROM repair_part_storage WHERE PartName='%s';", input_buffer);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				//û�в��ҵ����õ����
				if (row == NULL)
				{
					IMAGE No_Part_fault;
					loadimage(&No_Part_fault, _T(".\\IMAGES\\No_Part_fault.png"), 300, 150);
					putimage(490, 285, &No_Part_fault);
					Sleep(1500);
					return 99;
				}
				//�����������
				add_RepairPartID = atoi(row[0]);
				strcpy(part_name, row[1]);
				storage_part_num = atoi(row[2]);
				storage_part_req = atoi(row[3]);

				while (InputBox(input_buffer, 5, "������������������") == NULL)
					;
				add_part_require = atoi(input_buffer);

				if (add_part_require > storage_part_num)
				{
					//��治��
					//���ر���
					IMAGE Add_Part_Request_BAR;
					loadimage(&Add_Part_Request_BAR, _T(".\\IMAGES\\Add_Part_Request_BAR.png"), 610, 115);
					putimage(150, 525, &Add_Part_Request_BAR);

					IMAGE Part_Not_Sufficient_tip;
					loadimage(&Part_Not_Sufficient_tip, _T(".\\IMAGES\\Part_Not_Sufficient_tip.png"), 300, 150);
					putimage(490, 285, &Part_Not_Sufficient_tip);
				}
				else
				{
					//������
					//���ر���
					IMAGE Add_Part_Add_BAR;
					loadimage(&Add_Part_Add_BAR, _T(".\\IMAGES\\Add_Part_Add_BAR.png"), 610, 115);
					putimage(150, 525, &Add_Part_Add_BAR);
				}

				//�����ѯ���������Ϣ
				settextcolor(BLACK);
				settextstyle(25, 0, FONT);
				outtextxy(190, 580, row[0]);	   //���
				outtextxy(260, 580, row[1]);	   //����
				outtextxy(510, 580, input_buffer); //����
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
			//��ӹ�ʱ
			while (InputBox(input_buffer, 6, "���Ĺ�ʱ��\n�������ӹ�ʱ���������ٹ�ʱ") == NULL)
				;
			repair_time += atoi(input_buffer);
			sprintf(query_str, "UPDATE order_list SET RepairTime = %d WHERE OrderID =%d;", repair_time, OrderID);
			mysql_query(&mysql, query_str);
			return 99;
		case 53:
			//���
			sprintf(query_str, "UPDATE order_list SET Status = 3 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			IMAGE Repair_Finished_tip;
			loadimage(&Repair_Finished_tip, _T(".\\IMAGES\\Repair_Finished_tip.png"), 300, 150);
			putimage(490, 285, &Repair_Finished_tip);
			Sleep(1500);
			// if (InputBox(input_buffer, 140, "140�ַ�����", "���ά������", 0, 0, true))
			//{
			//	sprintf(query_str, "UPDATE order_list SET RepairDetail = %s WHERE OrderID =%d;",input_buffer, OrderID);
			//	mysql_query(&mysql, query_str);
			// }
			//����
			return 3;
		}
	}
}

int QualityMENU_MainMENU()
{
	//�ʼ�Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all; //��������
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,��ʾ���ж���
	// sort_flag=1,ֻ��ʾ��ǰ��ݶ���
	int sort_flag = 0;
	char buffer_input_OrderID[32];
	int OrderID;

	//��ӡ����
	print_QualityMENU_MainMENU_background();
	//��ӡժҪ��
	print_quality_brief();
	//����ͼƬ
	IMAGE Quality_Order_Page_BAR_0;
	loadimage(&Quality_Order_Page_BAR_0, _T(".\\IMAGES\\Quality_Order_Page_BAR_0.png"), 450, 80);
	IMAGE Quality_Order_Page_BAR_1;
	loadimage(&Quality_Order_Page_BAR_1, _T(".\\IMAGES\\Quality_Order_Page_BAR_1.png"), 450, 80);
	IMAGE SearchBlock_White;
	loadimage(&SearchBlock_White, _T(".\\IMAGES\\SearchBlock_White.png"), 255, 110);
	IMAGE SearchBlock_Black;
	loadimage(&SearchBlock_Black, _T(".\\IMAGES\\SearchBlock_Black.png"), 255, 110);

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ����
	sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_order_page_quality(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//�ȴ����
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
			//��ѯ����
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "�����붩����");
			OrderID = atoi(buffer_input_OrderID);
			//��ѯ����״̬
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//��ȡ�����
			res = mysql_store_result(&mysql);
			row = mysql_fetch_row(res);
			//û���ҵ���Ӧ�Ķ���
			if (res == NULL || row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_quality(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page_quality(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM order_list WHERE QualityStaffID=%d;", UserID);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page_quality(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list WHERE QualityStaffID=%d \
					AND Status=3;",
						UserID);
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page_quality(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);

				MENUchoice = QualityMENU_MainMENU_MENUChoose();
				break;
			}
		case 90:
			//������ʾ��ҳ��Ϣ
			//��ӡ����
			print_QualityMENU_MainMENU_background();
			//��ӡ��Ϣ��
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
			//�ʼ�
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
			//��ת���ʼ�ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				//��ѯ������Ķ�����
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
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int order_status = atoi(row[0]);
				int OrderID = atoi(row[1]);
				//�����������������ʼ�״̬
				if (order_status != 3)
				{
					MENUchoice = QualityMENU_MainMENU_MENUChoose();
					break;
				}
				mysql_free_result(res);

				MENUchoice = QualityMENU_QualityMENU(OrderID);
				//��һ������
				if (MENUchoice == 3)
				{
					MENUchoice = 90;
					break;
				}
			}
			MENUchoice = QualityMENU_MainMENU_MENUChoose();
			break;
			//�鿴
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
			//��ת���鿴ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
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
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//������ʾ��ҳ��Ϣ
					//��ӡ����
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
					//��ӡ��Ϣ��
					print_quality_brief();
					print_order_page_quality(current_page, count_all, sort_flag);
					//�����ҳ������
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 590, 230, 610);
					clearrectangle(240, 590, 260, 610);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//��ʾ��ǰҳ��
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
	//��ӡ����
	print_QualityMENU_QualityMENU_background();

	//ά��ҳ,��ʾ���ʹ����Ϣ
	//��ȡ���ʹ����
	int count_all; //���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	//��ҳͼƬ
	IMAGE Quality_Return_tip;
	loadimage(&Quality_Return_tip, _T(".\\IMAGES\\Quality_Return_tip.png"), 300, 150);
	IMAGE Quality_Finished_tip;
	loadimage(&Quality_Finished_tip, _T(".\\IMAGES\\Quality_Finished_tip.png"), 300, 150);

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ʹ������
	sprintf(query_str, "SELECT count(*) FROM repair_record WHERE OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);

	//��ѯά��Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.RepairStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
		strcpy(repair_staff_name, "����Ϣ");
	else
		strcpy(repair_staff_name, row[0]);

	//��ѯ�ʼ�Ա����
	sprintf(query_str, "SELECT user.Name FROM order_list,user WHERE order_list.QualityStaffID=user.UserID AND order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (row == NULL)
		strcpy(quality_staff_name, "����Ϣ");
	else
		strcpy(quality_staff_name, row[0]);

	//��ѯ��ʱ
	sprintf(query_str, "SELECT RepairTime FROM order_list WHERE order_list.OrderID=%d;", OrderID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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

	//��ӡά��Ա���ʼ�Ա��Ϣ
	settextcolor(BLACK);
	settextstyle(25, 0, FONT);
	outtextxy(190, 580, repair_staff_name);
	outtextxy(305, 580, quality_staff_name);
	outtextxy(420, 580, repair_time_buffer);
	//��ӡ������
	print_order_id(1170, 100, OrderID);
	//��ӡ������Ϣ
	print_order_info(800, 150, OrderID);
	//��ӡ״������ģ��
	print_description_info(800, 330, OrderID);
	//��ӡ�ʼ췴��ģ��
	print_quality_detail_info(800, 470, OrderID);

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_part_page_quality(current_page, count_all, OrderID);
		max_page = (int)((count_all - 1) / 10) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//�ȴ����
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_part_page_quality(current_page, count_all, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = QualityMENU_QualityMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_part_page_quality(current_page, count_all, OrderID);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = QualityMENU_QualityMENU_MENUChoose();
			break;
		case 61:
			//�˻�ά��
			sprintf(query_str, "UPDATE order_list SET Status = 22 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			if (InputBox(input_buffer, 101, "50�ַ�����", "����ʼ�����", "�ʼ��˻�ά��", 350, 120, true))
			{
				sprintf(query_str, "UPDATE order_list SET QualityDetail = '%s' WHERE OrderID =%d;", input_buffer, OrderID);
				mysql_query(&mysql, query_str);
			}

			putimage(490, 285, &Quality_Return_tip);
			Sleep(1500);
			//����
			return 3;
		case 62:
			//ͨ���ʼ�
			sprintf(query_str, "UPDATE order_list SET Status = 4 WHERE OrderID =%d;", OrderID);
			mysql_query(&mysql, query_str);

			if (InputBox(input_buffer, 101, "50�ַ�����", "����ʼ�����", "�ʼ�ͨ��", 350, 120, true))
			{
				sprintf(query_str, "UPDATE order_list SET QualityDetail = '%s' WHERE OrderID =%d;", input_buffer, OrderID);
				mysql_query(&mysql, query_str);
			}

			putimage(490, 285, &Quality_Finished_tip);
			Sleep(1500);
			//����
			return 3;
		}
	}
}

int AdminMENU_MainMENU()
{
	//����Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all; //��������
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,��ʾ���ж���
	// sort_flag=1,�ȴ�ά�޶���
	// sort_flag=2,�ȴ��ʼ충��
	// sort_flag=3,�ȴ�֧������
	int sort_flag = 0;

	char buffer_input_OrderID[32];
	int OrderID;

	//��ӡ����
	print_AdminMENU_MainMENU_background();
	//��ӡժҪ��
	print_reception_brief();
	//����ͼƬ
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

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ݣ�ȫ����������
	sprintf(query_str, "SELECT count(*) FROM order_list;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_order_page(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 13) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 590, 230, 610);
	clearrectangle(240, 590, 260, 610);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 590, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 590, page_buffer);

	//�ȴ����
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
			//��ѯ����
			setbkcolor(COLOR_BG);
			clearrectangle(50, 140, 50 + 130, 140 + 110);
			putimage(50, 140, &SearchBlock_White, SRCAND);
			putimage(50, 140, &SearchBlock_Black, SRCPAINT);
			setbkcolor(WHITE);
			clearrectangle(130, 184, 130 + 132, 184 + 22);
			InputBox_show(buffer_input_OrderID, 10, 130, 184, 132, 22, "�����붩����");
			OrderID = atoi(buffer_input_OrderID);
			//��ѯ����״̬
			sprintf(query_str, "SELECT Status FROM order_list WHERE OrderID=%s;", buffer_input_OrderID);
			mysql_query(&mysql, query_str);
			//��ȡ�����
			res = mysql_store_result(&mysql);
			if (res == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
				// loadimage(&No_Order_fault, _T(".\\IMAGES\\No_Order_fault.png"), 300, 150);
				// putimage(490, 285, &No_Order_fault);
				Sleep(1500);
				MENUchoice = 1;
				break;
			}
			row = mysql_fetch_row(res);
			//û���ҵ���Ӧ�Ķ���
			if (row == NULL)
			{
				IMAGE No_Order_fault;
				settextcolor(COLOR_RED);
				settextstyle(22, 0, FONT);
				clearrectangle(130, 184, 130 + 132, 184 + 22);
				outtextxy(130, 184, "��Ч�Ķ�����");
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
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_order_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//��갴�����ж�������
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 560, &Admin_Order_Page_BAR_0);

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM order_list;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//��갴�ڵȴ�ά�޶�������
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 560, &Admin_Order_Page_BAR_1);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE (Status=1 OR Status=22 OR Status=21) ;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 45:
			//��갴�ڵȴ��ʼ충������
			if (sort_flag != 2)
			{
				sort_flag = 2;
				putimage(150, 560, &Admin_Order_Page_BAR_2);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=3 ;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 46:
			//��갴�ڵȴ�֧����������
			if (sort_flag != 3)
			{
				sort_flag = 3;
				putimage(150, 560, &Admin_Order_Page_BAR_3);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM order_list\
					WHERE Status=4;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_order_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 13) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 590, 230, 610);
				clearrectangle(240, 590, 260, 610);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 590, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 590, page_buffer);
			}
			MENUchoice = AdminMENU_MainMENU_MENUChoose();
			break;
		case 90:
			//������ʾ��ҳ��Ϣ
			//��ӡ����
			print_AdminMENU_MainMENU_background();
			//��ӡ��Ϣ��
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
			//��ת���鿴ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
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
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				int OrderID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = OrderCheckMENU(OrderID);

				if (MENUchoice == 3)
				{
					//������ʾ��ҳ��Ϣ
					//��ӡ����
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
					//��ӡ��Ϣ��
					print_reception_brief();
					print_order_page(current_page, count_all, sort_flag);
					//�����ҳ������
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 590, 230, 610);
					clearrectangle(240, 590, 260, 610);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//��ʾ��ǰҳ��
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
	//��Ա�������
	//��ӡ����
	print_AdminMENU_PeopleMENU_background();
	//��ӡժҪ��
	print_reception_brief();
	//����ͼƬ
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

	int count_all; //��Ա����
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

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ��Ա����
	sprintf(query_str, "SELECT count(*) FROM user;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	//�ⲽ����������û����Ϣ����Ȼ����ô�ǽ������أ�
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	count_all = atoi(row[0]);

	//�ȴ�ӡ��һҳ
	current_page = 1;
	print_people_page(current_page, count_all);
	max_page = (int)((count_all - 1) / 10) + 1;

	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	char page_buffer[8];
	_stprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	_stprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//�ȴ����
	int MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
	int row_clicked; //��ǰ��������ӦSQL�У�

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
			return MENUchoice;
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_people_page(current_page, count_all);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_people_page(current_page, count_all);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				char page_buffer[8];
				_stprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				_stprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
			//�޸�����
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
				//��ǰ��
				//��ѯ�������ά�޼�¼��
				sprintf(query_str,
						"SELECT UserID FROM user ORDER BY UserID LIMIT %d,1;", row_clicked);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				select_UserID = atoi(row[0]);

				InputBox(buffer_input, 13, "������������");
				if (strlen(buffer_input) != 0)
				{
					sprintf(query_str, "UPDATE user SET PassWord = '%s' WHERE UserID =%d;", buffer_input, select_UserID);
					mysql_query(&mysql, query_str);
					putimage(490, 285, &PassWord_Changed_tip);
					Sleep(1500);
				}
			}
			//������ʾ��ҳ
			print_people_page(current_page, count_all);
			//�����ҳ������
			setbkcolor(COLOR_WHITE);
			clearrectangle(210, 500, 230, 520);
			clearrectangle(240, 500, 260, 520);
			settextcolor(BLACK);
			settextstyle(20, 0, FONT);
			//��ʾ��ǰҳ��
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
			//ɾ��
			row_clicked = MENUchoice % 100 + 10 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				//��ѯ�������ID
				sprintf(query_str,
						"SELECT UserID FROM user ORDER BY UserID LIMIT %d,1;", row_clicked);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				select_UserID = atoi(row[0]);

				//ɾ����ID
				sprintf(query_str,
						"DELETE FROM user WHERE UserID=%d;", select_UserID);
				mysql_query(&mysql, query_str);

				//������һ����������ʾ��ҳ
				return 4;
			}
		case 51:
			//�����Ա-����
			setbkcolor(WHITE);
			InputBox(buffer_input, 9, "��������Ա����");
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
			//�����Ա-�û���
			setbkcolor(WHITE);
			InputBox(buffer_input, 13, "�������û���\n��Ӧ�������û����ظ�");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM user WHERE UserName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				if (res == NULL || row == NULL)
				{
					//û���ظ����û���
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
			//�����Ա-����
			setbkcolor(WHITE);
			InputBox(buffer_input, 13, "����������");
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
			//���-�Ӵ�רԱ
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(565, 580, "��");
			outtextxy(595, 580, "��");
			outtextxy(625, 580, "��");
			settextcolor(COLOR_PURPLE);
			outtextxy(535, 580, "��");
			add_Role = 1;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 55:
			//���-ά��רԱ
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "��");
			outtextxy(595, 580, "��");
			outtextxy(625, 580, "��");
			settextcolor(COLOR_BLUE);
			outtextxy(565, 580, "��");
			add_Role = 2;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 56:
			//���-�ʼ�רԱ
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "��");
			outtextxy(565, 580, "��");
			outtextxy(625, 580, "��");
			settextcolor(COLOR_ORANGE);
			outtextxy(595, 580, "��");
			add_Role = 3;
			check_Role = true;
			MENUchoice = AdminMENU_PeopleMENU_MENUChoose();
			break;
		case 57:
			//���-���רԱ
			settextstyle(22, 0, FONT);
			settextcolor(COLOR_GREY_3);
			outtextxy(535, 580, "��");
			outtextxy(565, 580, "��");
			outtextxy(595, 580, "��");
			settextcolor(COLOR_RED);
			outtextxy(625, 580, "��");
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

				//��ȡ�����Ų���֤�����Ƿ�ɹ�
				sprintf(query_str,
						"SELECT UserID FROM user \
					WHERE Name = '%s' \
					AND UserName = '%s' \
					AND PassWord = '%s' \
					AND Role = '%d' ;",
						add_buffer_Name, add_buffer_UserName, add_buffer_PassWord, add_Role);
				mysql_query(&mysql, query_str);

				//��ȡ�����
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
	//����Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all; //�������
	int current_page = 0;
	int max_page = 0;
	// sort_flag=0,��ʾ���п��
	// sort_flag=1,�ȴ���治��
	int sort_flag = 0;

	char buffer_input_PartID[32];
	int PartID;
	char page_buffer[8];
	//����ͼƬ
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

	//��ӡ����
	print_StorageMENU_MainMENU_background();
	//��ӡժҪ��
	print_storage_brief();

	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
	char query_str[512] = "";

	//��ѯ���ݣ�ȫ����棩
	sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
	mysql_query(&mysql, query_str);
	//��ȡ�����
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	count_all = atoi(row[0]);

	//����һ�µײ���ͼ
	putimage(150, 470, &Storage_BAR_0);
	if (count_all == 0)
	{
		settextcolor(COLOR_GREY_2);
		settextstyle(20, 0, FONT);
		outtextxy(180, 185, "����������ݣ�");
		current_page = 0;
		max_page = 0;
	}
	else
	{
		//�ȴ�ӡ��һҳ
		current_page = 1;
		print_storage_page(current_page, count_all, sort_flag);
		max_page = (int)((count_all - 1) / 10) + 1;
	}
	//�����ҳ������
	setbkcolor(COLOR_WHITE);
	clearrectangle(210, 500, 230, 520);
	clearrectangle(240, 500, 260, 520);
	settextcolor(BLACK);
	settextstyle(20, 0, FONT);
	//��ʾ��ǰҳ��
	sprintf(page_buffer, _T("%2d"), current_page);
	outtextxy(210, 500, page_buffer);
	sprintf(page_buffer, _T("%d"), max_page);
	outtextxy(240, 500, page_buffer);

	//�ȴ����
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
			//��ѯ����
			if (InputBox(buffer_input_PartID, 19, "�������������"))
			{
				setbkcolor(COLOR_BG);
				//��ѯ״̬
				sprintf(query_str,
						"SELECT RepairPartID, PartName, Price, Num, Req FROM repair_part_storage WHERE PartName='%s';", buffer_input_PartID);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				if (res == NULL)
				{
					putimage(490, 285, &No_Part_fault);
					Sleep(1500);
					MENUchoice = 1;
					break;
				}
				row = mysql_fetch_row(res);
				//û���ҵ���Ӧ�Ķ���
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
			//������
			MENUchoice = StorageMENU_AddMENU();
			break;
		case 41: //��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_storage_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 42: //��һҳ
			if (current_page != max_page && current_page != 0)
			{
				current_page++;
				print_storage_page(current_page, count_all, sort_flag);
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 43:
			//��갴�����ж�������
			if (sort_flag != 0)
			{
				sort_flag = 0;
				putimage(150, 470, &Storage_BAR_0);

				//��ѯ����
				sprintf(query_str, "SELECT count(*) FROM repair_part_storage;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_storage_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 10) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
				sprintf(page_buffer, _T("%2d"), current_page);
				outtextxy(210, 500, page_buffer);
				sprintf(page_buffer, _T("%d"), max_page);
				outtextxy(240, 500, page_buffer);
			}
			MENUchoice = StorageMENU_MainMENU_MENUChoose();
			break;
		case 44:
			//��갴�ڿ�治������
			if (sort_flag != 1)
			{
				sort_flag = 1;
				putimage(150, 470, &Storage_BAR_1);

				//��ѯ����
				sprintf(query_str,
						"SELECT count(*) FROM repair_part_storage \
					WHERE Req>0;");
				mysql_query(&mysql, query_str);
				//��ȡ�����
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
					outtextxy(180, 185, "����������ݣ�");
					current_page = 0;
					max_page = 0;
				}
				else
				{
					//�ȴ�ӡ��һҳ
					current_page = 1;
					print_storage_page(current_page, count_all, sort_flag);
					max_page = (int)((count_all - 1) / 10) + 1;
				}
				//�����ҳ������
				setbkcolor(COLOR_WHITE);
				clearrectangle(210, 500, 230, 520);
				clearrectangle(240, 500, 260, 520);
				settextcolor(BLACK);
				settextstyle(20, 0, FONT);
				//��ʾ��ǰҳ��
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
			//�޸�
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
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
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				PartID = atoi(row[0]);
				mysql_free_result(res);

				MENUchoice = StorageMENU_ChangeMENU(PartID);

				if (MENUchoice == 3)
				{
					//������ʾ��ҳ��Ϣ
					//��ӡ����
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
					//��ӡ��Ϣ��
					print_storage_brief();
					print_storage_page(current_page, count_all, sort_flag);
					//�����ҳ������
					setbkcolor(COLOR_WHITE);
					clearrectangle(210, 500, 230, 520);
					clearrectangle(240, 500, 260, 520);
					settextcolor(BLACK);
					settextstyle(20, 0, FONT);
					//��ʾ��ǰҳ��
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
	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
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

	//��ʾ��λ
	int x, y, w, h;

	sprintf(query_str,
			"SELECT RepairPartID, PartName, Price, Num, Req \
		FROM repair_part_storage \
		WHERE RepairPartID=%d;",
			PartID);
	mysql_query(&mysql, query_str);
	//��ȡ�����
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
	drawtext(row[0], &print_rect, DT_CENTER | DT_VCENTER); //���
	x += 64;
	w = 214;
	print_rect = {x, y, x + w, y + h};
	drawtext(row[1], &print_rect, DT_CENTER | DT_VCENTER); //�������
	x += 234;
	w = 44;
	print_rect = {x, y, x + w, y + h};
	drawtext(row[2], &print_rect, DT_CENTER | DT_VCENTER); //�۸�
	if (atoi(row[4]) > 0)
	{
		settextcolor(COLOR_RED);
		x += 64;
		print_rect = {x, y, x + w, y + h};
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER); //���
	}
	else
	{
		settextcolor(COLOR_GREEN);
		x += 64;
		print_rect = {x, y, x + w, y + h};
		drawtext(row[3], &print_rect, DT_CENTER | DT_VCENTER); //���
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
			//�޸�����
			InputBox(buffer_input, 19, "�������������\n��Ӧ�����������ظ�");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM repair_part_storage WHERE PartName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				res = mysql_store_result(&mysql);

				if (mysql_fetch_row(res) == NULL)
				{
					//û���ظ����������
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
					drawtext("��������������ظ�", &print_rect, DT_CENTER | DT_VCENTER);
				}
			}
			MENUchoice = StorageMENU_ChangeMENU_MENUChoose();
			break;
		case 52:
			//�޸ļ۸�
			InputBox(buffer_input, 5, "����������۸�");
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
			//�޸Ŀ��
			InputBox(buffer_input, 5, "���������޸�\n����Ϊ������������Ϊ������");
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
			//�޸Ŀ����Ϣ
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
	// MYsql�Ĳ�ѯ����
	static MYSQL_RES *res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��
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
			//�޸�����
			InputBox(buffer_input, 19, "�������������\n��Ӧ�����������ظ�");
			if (strlen(buffer_input) > 0)
			{
				sprintf(query_str, "SELECT * FROM repair_part_storage WHERE PartName='%s';", buffer_input);
				mysql_query(&mysql, query_str);
				res = mysql_store_result(&mysql);

				if (mysql_fetch_row(res)==NULL)
				{
					//û���ظ����������
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
					outtextxy(194, 580, "��������������ظ�");
				}
			}
			MENUchoice = StorageMENU_AddMENU_MENUChoose();
			break;
		case 52:
			//�޸ļ۸�
			InputBox(buffer_input, 5, "����������۸�");
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
			//�޸Ŀ��
			InputBox(buffer_input, 5, "��������");
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
				//�޸Ŀ����Ϣ
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
