#pragma once

/* 打印背景 */
//打印维修 主页背景
void print_RepairMENU_MainMENU_background();
//打印维修 维修单详情页背景
void print_RepairMENU_RepairMENU_background();
//打印质检 主页背景
void print_QualityMENU_MainMENU_background();
//打印质检 质检单详情页背景
void print_QualityMENU_QualityMENU_background();
//打印订单查看 背景
void print_OrderCheckMENU_background();
//打印订单查看 客户 已支付（状态5） 背景
void print_OrderCheckMenu_Visiter_Payed_background();
//打印订单查看 客户 未支付背景
void print_OrderCheckMenu_Visiter_UnPay_background();


/* 打印订单号 */
// 打印订单号
void print_order_id(int x, int y, int OrderID);

/* 打印摘要模块 */
//打印维修 摘要模块
void print_repair_brief();
//打印质检 摘要模块
void print_quality_brief();

//打印订单信息模块
void print_order_info(int x, int y, int OrderID);
//打印状况描述模块
void print_description_info(int x, int y, int OrderID);
//打印质检反馈模块
void print_quality_detail_info(int x, int y, int OrderID);
//打印车主信息模块
void print_CarOwner_info(int x, int y, int OrderID);

//打印一页订单信息
void print_order_page_repair(int page, int count, int status);
void print_order_page_quality(int page, int count, int status);

//打印一行订单信息
void print_order_rol(int x, int y, MYSQL_ROW row);

//打印一页配件信息
int print_part_page_repair(int page, int count, int OrderID);
int print_part_page_quality(int page, int count, int OrderID);
int print_part_page_OrderCheckMENU(int page, int count, int OrderID);
int print_part_page_OrderCheckMENU_Visiter(int page, int count, int OrderID);

//打印一行配件信息
int print_part_rol(int x, int y, MYSQL_ROW row);