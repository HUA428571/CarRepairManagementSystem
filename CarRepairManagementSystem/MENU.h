#pragma once

int startMENU();

int OrderCheckMENU(int OrderID);
int OrderCheckMenu_Visiter_Payed(int Status, int OrderID);
int OrderCheckMenu_Visiter_UnPay(int Status, int OrderID);

int RepairMENU_MainMENU();
int RepairMENU_RepairMENU(int OrderID);

int QualityMENU_MainMENU();
int QualityMENU_QualityMENU(int OrderID);

int ReceptionMENU_MainMENU();
int ReceptionMENU_AddMENU();

int AdminMENU_MainMENU();
int AdminMENU_PeopleMENU();

