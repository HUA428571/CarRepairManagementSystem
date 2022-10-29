#pragma once

void print_RepairMENU_MainMENU_background();

void print_QualityMENU_MainMENU_background();

void print_RepairMENU_RepairMENU_background();

void print_QualityMENU_QualityMENU_background();

void print_OrderCheckMENU_background();


void print_order_id(int x, int y, int OrderID);

//打印维修页摘要模块
void print_repair_brief();
void print_quality_brief();


//打印订单信息模块
void print_order_info(int x, int y, int OrderID);

//打印状况描述模块
void print_description_info(int x, int y, int OrderID);

//打印质检反馈模块
void print_quality_detail_info(int x, int y, int OrderID);

//打印一页订单信息
//void print_order_page_repair(int page, int count);
void print_order_page_repair(int page, int count, int status);

void print_order_page_quality(int page, int count, int status);


//打印一行订单信息
void print_order_rol(int x, int y, MYSQL_ROW row);

//打印一页配件信息
int print_part_page_repair(int page, int count, int OrderID);
int print_part_page_quality(int page, int count, int OrderID);

int print_part_page_OrderCheckMENU(int page, int count, int OrderID);

//打印一行配件信息
int print_part_rol(int x, int y, MYSQL_ROW row);