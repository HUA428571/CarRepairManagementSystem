#pragma once

/* ��ӡ���� */
//��ӡά�� ��ҳ����
void print_RepairMENU_MainMENU_background();
//��ӡά�� ά�޵�����ҳ����
void print_RepairMENU_RepairMENU_background();
//��ӡ�ʼ� ��ҳ����
void print_QualityMENU_MainMENU_background();
//��ӡ�ʼ� �ʼ쵥����ҳ����
void print_QualityMENU_QualityMENU_background();
//��ӡ�����鿴 ����
void print_OrderCheckMENU_background();
//��ӡ�����鿴 �ͻ� ��֧����״̬5�� ����
void print_OrderCheckMenu_Visiter_Payed_background();
//��ӡ�����鿴 �ͻ� δ֧������
void print_OrderCheckMenu_Visiter_UnPay_background();


/* ��ӡ������ */
// ��ӡ������
void print_order_id(int x, int y, int OrderID);

/* ��ӡժҪģ�� */
//��ӡά�� ժҪģ��
void print_repair_brief();
//��ӡ�ʼ� ժҪģ��
void print_quality_brief();

//��ӡ������Ϣģ��
void print_order_info(int x, int y, int OrderID);
//��ӡ״������ģ��
void print_description_info(int x, int y, int OrderID);
//��ӡ�ʼ췴��ģ��
void print_quality_detail_info(int x, int y, int OrderID);
//��ӡ������Ϣģ��
void print_CarOwner_info(int x, int y, int OrderID);

//��ӡһҳ������Ϣ
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