#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// 图形化界面函数
// --------------------------------------------------

/* 打印背景 */
//打印维修界面 主页背景
void print_RepairMENU_MainMENU_background();
//打印维修界面 维修单详情页背景
void print_RepairMENU_RepairMENU_background();
//打印质检界面 主页背景
void print_QualityMENU_MainMENU_background();
//打印质检界面 质检单详情页背景
void print_QualityMENU_QualityMENU_background();
//打印接待界面 主页背景
void print_ReceptionMENU_MainMENU_background();
//打印接待界面 添加订单背景
void print_ReceptionMENU_AddMENU_background();
//打印管理界面 主页背景
void print_AdminMENU_MainMENU_background();
//打印管理界面 人员管理背景
void print_AdminMENU_PeopleMENU_background();
//打印库管界面 主页背景
void print_StorageMENU_MainMENU_background();
//打印订单查看 背景
void print_OrderCheckMENU_background();
//打印订单查看 客户 已支付（状态5） 背景
void print_OrderCheckMenu_Visiter_Payed_background();
//打印订单查看 客户 未支付背景
void print_OrderCheckMenu_Visiter_UnPay_background();

//打印订单号
void print_order_id(int x, int y, int OrderID);

/* 打印摘要模块 */
//打印维修 摘要模块
void print_repair_brief();
//打印质检 摘要模块
void print_quality_brief();
//打印接待 摘要模块
void print_reception_brief();
//打印库管 摘要模块
void print_storage_brief();

/* 打印信息模块 */
//打印订单信息模块
void print_order_info(int x, int y, int OrderID);
//打印状况描述模块
void print_description_info(int x, int y, int OrderID);
//打印质检反馈模块
void print_quality_detail_info(int x, int y, int OrderID);
//打印车主信息模块
void print_CarOwner_info(int x, int y, int OrderID);
//打印车主信息模块 隐去手机号
void print_CarOwner_info_safe(int x, int y, int OrderID);

/* 打印一页订单信息 */
//含有“维修”字样，限定打印状态
void print_order_page_repair(int page, int count, int status);
//含有“质检”字样，限定打印状态
void print_order_page_quality(int page, int count, int status);
//除了“查看”没有别的操作，在接待员页面和管理员页面可用
void print_order_page(int page, int count, int status);

//打印一行订单信息
void print_order_rol(int x, int y, MYSQL_ROW row);

/* 打印一页配件-订单详情信息 */
//打印一页配件-订单详情信息 维修单详情页
int print_part_page_repair(int page, int count, int OrderID);
//打印一页配件-订单详情信息 质检单详情页
int print_part_page_quality(int page, int count, int OrderID);
//打印一页配件-订单详情信息 通用信息查看模块
int print_part_page_OrderCheckMENU(int page, int count, int OrderID);
//打印一页配件-订单详情信息 通用信息查看模块（访客）
int print_part_page_OrderCheckMENU_Visiter(int page, int count, int OrderID);

//打印一行配件信息
int print_part_rol(int x, int y, MYSQL_ROW row);

//打印一页人员信息
void print_people_page(int page, int count);
//打印一行人员信息
void print_people_rol(int x, int y, MYSQL_ROW row);

//打印一页配件-库管信息
void print_storage_page(int page, int count, int flag);
//打印一行配件-库管信息
void print_storage_rol(int x, int y, MYSQL_ROW row);
