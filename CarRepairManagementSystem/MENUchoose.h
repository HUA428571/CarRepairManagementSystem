#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// 鼠标处理函数
// --------------------------------------------------

//欢迎界面
int StartMENU_MENUChoose();

//通用订单查看界面
int OrderCheckMENU_MENUChoose();
int OrderCheckMENU_Visiter_Payed_MENUChoose();
int OrderCheckMENU_Visiter_UnPay_MENUChoose();

//管理界面
int AdminMENU_MainMENU_MENUChoose();
int AdminMENU_PeopleMENU_MENUChoose();

//接待界面
int ReceptionMENU_MainMENU_MENUChoose();
int ReceptionMENU_AddMENU_MENUChoose();

//维修界面
int RepairMENU_MainMENU_MENUChoose();
int RepairMENU_RepairMENU_MENUChoose();
int RepairMENU_RepairMENU_AddPart_MENUChoose();

//质检界面
int QualityMENU_MainMENU_MENUChoose();
int QualityMENU_QualityMENU_MENUChoose();

//库管界面
int StorageMENU_MainMENU_MENUChoose();
int StorageMENU_ChangeMENU_MENUChoose();
int StorageMENU_AddMENU_MENUChoose();
