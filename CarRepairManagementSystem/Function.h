#pragma once
// --------------------------------------------------
// Copyright 2022 HuaCL
// ��������
// --------------------------------------------------

//������������ݣ��������ƣ���������λ�ã����������λ�ã�Ĭ����ʾ�����ݣ�
int C_InputBox(char* Input, int Limit, int x, int y, const char* Default);
//������������ݣ��������ƣ���������λ�ã����������λ�ã�������ܳ��ȣ�����߶ȣ�Ĭ����ʾ�����ݣ�
int C_InputBox(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//�����_��¼���棨�������ݣ��������ƣ���������λ�ã����������λ�ã�������ܳ��ȣ�����߶ȣ�Ĭ����ʾ�����ݣ�
int InputBox_show(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//�����_����ʾ�ַ�_��¼���棨�������ݣ��������ƣ���������λ�ã����������λ�ã�������ܳ��ȣ�����߶ȣ�Ĭ����ʾ�����ݣ�
int InputBox_no_show(char* Input, int Limit, int x, int y, int Lsize, int Hsize, const char* Default);
//���ID��Ϣ
int CheckID(char* input_UserName, char* input_PassWord);
//��������ܼ�
int calaulate_part_total_price(int OrderID);
