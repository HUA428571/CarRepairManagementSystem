#pragma once

void print_repair_home_background();

void print_repair_repair_background();

void print_order_id(int x, int y, int OrderID);

//��ӡά��ҳժҪģ��
void print_repair_brief();

//��ӡ������Ϣģ��
void print_order_info(int x, int y, int OrderID);

//��ӡ״������ģ��
void print_description_info(int x, int y, int OrderID);
//��ӡ�ʼ췴��ģ��
void print_quality_detail_info(int x, int y, int OrderID);

//��ӡһҳ������Ϣ
void print_order_page_repair(int page, int count);

//��ӡһ�ж�����Ϣ
void print_order_rol(int x, int y, MYSQL_ROW row);

//��ӡһҳ�����Ϣ
int print_part_page_repair(int page, int count, int OrderID);

//��ӡһ�������Ϣ
int print_part_rol(int x, int y, MYSQL_ROW row);
