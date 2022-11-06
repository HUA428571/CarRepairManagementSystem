#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// 各级菜单函数和消息队列（伪）
// --------------------------------------------------

//欢迎界面
int startMENU();

//通用订单查看界面
int OrderCheckMENU(int OrderID);
int OrderCheckMenu_Visiter_Payed(int Status, int OrderID);
int OrderCheckMenu_Visiter_UnPay(int Status, int OrderID);

//管理界面
//管理界面-主界面
int AdminMENU_MainMENU();
//管理界面-人员管理
int AdminMENU_PeopleMENU();

//接待界面
//接待界面-主界面
int ReceptionMENU_MainMENU();
//接待界面-新建订单
int ReceptionMENU_AddMENU();

//维修界面
//维修界面-主界面
int RepairMENU_MainMENU();
//维修界面-维修单填写
int RepairMENU_RepairMENU(int OrderID);

//质检界面
//质检界面-主界面
int QualityMENU_MainMENU();
//质检界面-质检单填写
int QualityMENU_QualityMENU(int OrderID);

//库管界面
//库管界面-主界面
int StorageMENU_MainMENU();
//库管界面-修改配件信息
int StorageMENU_ChangeMENU(int PartID);
//库管界面-添加配件
int StorageMENU_AddMENU();
