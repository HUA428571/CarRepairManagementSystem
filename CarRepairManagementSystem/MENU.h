#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// �����˵���������Ϣ���У�α��
// --------------------------------------------------

//��ӭ����
int startMENU();

//ͨ�ö����鿴����
int OrderCheckMENU(int OrderID);
int OrderCheckMenu_Visiter_Payed(int Status, int OrderID);
int OrderCheckMenu_Visiter_UnPay(int Status, int OrderID);

//�������
//�������-������
int AdminMENU_MainMENU();
//�������-��Ա����
int AdminMENU_PeopleMENU();

//�Ӵ�����
//�Ӵ�����-������
int ReceptionMENU_MainMENU();
//�Ӵ�����-�½�����
int ReceptionMENU_AddMENU();

//ά�޽���
//ά�޽���-������
int RepairMENU_MainMENU();
//ά�޽���-ά�޵���д
int RepairMENU_RepairMENU(int OrderID);

//�ʼ����
//�ʼ����-������
int QualityMENU_MainMENU();
//�ʼ����-�ʼ쵥��д
int QualityMENU_QualityMENU(int OrderID);

//��ܽ���
//��ܽ���-������
int StorageMENU_MainMENU();
//��ܽ���-�޸������Ϣ
int StorageMENU_ChangeMENU(int PartID);
//��ܽ���-������
int StorageMENU_AddMENU();
