#pragma once

void print_RepairMENU_MainMENU_background();

void print_QualityMENU_MainMENU_background();

void print_OrderCheckMenu_Visiter_Payed_background();

void print_OrderCheckMenu_Visiter_UnPay_background();


void print_RepairMENU_RepairMENU_background();

void print_QualityMENU_QualityMENU_background();

void print_OrderCheckMENU_background();


void print_order_id(int x, int y, int OrderID);

//��ӡά��ҳժҪģ��
void print_repair_brief();
void print_quality_brief();


//��ӡ������Ϣģ��
void print_order_info(int x, int y, int OrderID);

//��ӡ״������ģ��
void print_description_info(int x, int y, int OrderID);

//��ӡ�ʼ췴��ģ��
void print_quality_detail_info(int x, int y, int OrderID);

void print_CarOwner_info(int x, int y, int OrderID);

//��ӡһҳ������Ϣ
//void print_order_page_repair(int page, int count);
void print_order_page_repair(int page, int count, int status);

void print_order_page_quality(int page, int count, int status);


//��ӡһ�ж�����Ϣ
void print_order_rol(int x, int y, MYSQL_ROW row);

//��ӡһҳ�����Ϣ
int print_part_page_repair(int page, int count, int OrderID);
int print_part_page_quality(int page, int count, int OrderID);

int print_part_page_OrderCheckMENU(int page, int count, int OrderID);

int print_part_page_OrderCheckMENU_Visiter(int page, int count, int OrderID);

//��ӡһ�������Ϣ
int print_part_rol(int x, int y, MYSQL_ROW row);