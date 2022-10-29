#pragma once
#include"head.h"

int RepairMENU()
{
	return 0;
}

int RepairMENU_MainMENU()
{
	//ά��Ա��ҳ,��ʾ������Ϣ
	//��ȡ������
	int count_all;//��������
	int count_finish;
	int current_page = 0;
	int max_page = 0;
	//sort_flag=0,��ʾ���ж���
	//sort_flag=1,ֻ��ʾ��ǰ��ݶ���
	int sort_flag = 0;

	//��ӡ����
	print_RepairMENU_MainMENU_background();

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
			return MENUchoice;
		case 1:
		case 2:
			MENUchoice = RepairMENU_MainMENU_MENUChoose();
			break;
		case 41:					//��һҳ
			if (current_page != 1 && current_page != 0)
			{
				current_page--;
				print_order_page_repair(current_page, count_all,sort_flag);
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
		case 42:					//��һҳ
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

				//MYsql�Ĳ�ѯ����
				static MYSQL_RES* res; //��ѯ�����
				static MYSQL_ROW row;  //��¼�ṹ��
				//��ѯ����
				char query_str[512] = "";
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
				break;
			}
			//ά��
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
		case 113:					//��ת��ά��ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				char query_str[512] = "";
				MYSQL_RES* res; //��ѯ�����
				MYSQL_ROW row;  //��¼�ṹ��
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
				//������ʾ�Ķ���ά��ҳ
				while (MENUchoice == 99)
				{
					MENUchoice = RepairMENU_RepairMENU(OrderID);
				}
				//��һ������
				if (MENUchoice == 3)
				{
					//������ʾ��ҳ��Ϣ
					//��ӡ����
					print_RepairMENU_MainMENU_background();
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
		case 213:					//��ת��ά��ҳ��
			//�����жϸ�ҳ�Ķ�������
			//��ǰ�����������0��ʼ�����ű�
			row_clicked = MENUchoice % 100 + 13 * (current_page - 1) - 1;
			if (row_clicked < count_all)
			{
				//��ǰ��
				char query_str[512] = "";
				MYSQL_RES* res; //��ѯ�����
				MYSQL_ROW row;  //��¼�ṹ��
				//��ѯ������Ķ�����
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

				if (MENUchoice != 3)
				{
					break;
				}
				//������ʾ��ҳ��Ϣ
				//��ӡ����
				print_RepairMENU_MainMENU_background();
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
	int count_all;//���ʹ������
	int current_page = 0;
	int max_page = 0;
	//ά��Ա���ʼ�Ա����
	char repair_staff_name[16] = "";
	char quality_staff_name[16] = "";
	char repair_time_buffer[16] = "";
	int repair_time = 0;

	char input_buffer[256] = "";
	int RepairPartID;			//ά��������
	int id_RepairRecord;//ά�޼�¼���
	int repair_record_RepairPartID;//ά��������
	int repair_record_part_number;//ά�����ʹ������
	char part_name[60] = "";
	int part_price;//ά������۸�
	int storage_part_number;//ά��������
	int storage_part_require;
	int part_require;

	//MYsql�Ĳ�ѯ����
	static MYSQL_RES* res; //��ѯ�����
	static MYSQL_ROW row;  //��¼�ṹ��

	//��ѯ���ʹ������
	char query_str[512] = "";
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
	print_quality_detail_info(800, 445, OrderID);

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
	int row_clicked;				//��ǰ��������ӦSQL�У�

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			return MENUchoice;
		case 41:					//��һҳ
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
		case 42:					//��һҳ
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
				char query_str[512] = "";
				MYSQL_RES* res; //��ѯ�����
				MYSQL_ROW row;  //��¼�ṹ��
				//��ѯ�������ά�޼�¼��
				sprintf(query_str,
					"SELECT \
					repair_record.id_RepairRecord,repair_record.RepairPartID,repair_record.Num, \
					repair_part_storage.Num, repair_part_storage.Req\
					FROM repair_record,repair_part_storage \
					WHERE repair_record.RepairPartID=repair_part_storage.RepairPartID \
					AND OrderID =%d ORDER BY repair_record.id_RepairRecord LIMIT %d,1;"
					, OrderID, row_clicked);
				mysql_query(&mysql, query_str);
				//��ȡ�����
				res = mysql_store_result(&mysql);
				row = mysql_fetch_row(res);
				id_RepairRecord = atoi(row[0]);
				repair_record_RepairPartID = atoi(row[1]);
				repair_record_part_number = atoi(row[2]);
				storage_part_number = atoi(row[3]);
				storage_part_require = atoi(row[4]);

				mysql_free_result(res);

				//ɾ������ά�޼�¼
				sprintf(query_str,
					"DELETE FROM repair_record WHERE id_RepairRecord=%d;"
					, id_RepairRecord);
				mysql_query(&mysql, query_str);

				//������������Ϣ
				sprintf(query_str,
					"UPDATE repair_part_storage SET Num = %d,Req=%d WHERE RepairPartID =%d"
					, storage_part_number + repair_record_part_number, storage_part_require - repair_record_part_number, repair_record_RepairPartID);
				mysql_query(&mysql, query_str);


				return 99;
			}
			MENUchoice = RepairMENU_RepairMENU_MENUChoose();
			break;
		case 51:
			//������
			if (InputBox(input_buffer, 140, "������Ҫ��ӵ��������"))
			{
				//MYsql�Ĳ�ѯ����
				static MYSQL_RES* res; //��ѯ�����
				static MYSQL_ROW row;  //��¼�ṹ��

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
				RepairPartID = atoi(row[0]);
				strcpy(part_name, row[1]);
				storage_part_number = atoi(row[2]);
				storage_part_require = atoi(row[3]);

				while (InputBox(input_buffer, 4, "������������������") == NULL);
				part_require = atoi(input_buffer);

				if (part_require > storage_part_number)
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
				outtextxy(190, 580, row[0]);//���
				outtextxy(260, 580, row[1]);//����
				outtextxy(510, 580, input_buffer);//����
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
			//��ӹ�ʱ
			while (InputBox(input_buffer, 6, "���Ĺ�ʱ��\n�������ӹ�ʱ���������ٹ�ʱ") == NULL);
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
			//if (InputBox(input_buffer, 140, "140�ַ�����", "���ά������", 0, 0, true))
			//{
			//	sprintf(query_str, "UPDATE order_list SET RepairDetail = %s WHERE OrderID =%d;",input_buffer, OrderID);
			//	mysql_query(&mysql, query_str);
			//}
			//����
			return 3;
		}
	}
}