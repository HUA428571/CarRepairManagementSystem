#pragma once
#include"head.h"
#include "MENUchoose.h"
int RepairMENU_MainMENU_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//������������
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//��갴����ҳ����
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//��갴�ڶ�������
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//��갴���˳�����
				return 0;

			if (m.x > 175 && m.y > 585 && m.x < 205 && m.y < 615)//��갴����һҳ����
				return 41;
			if (m.x > 265 && m.y > 585 && m.x < 295 && m.y < 615)//��갴����һҳ����
				return 42;
			for (int i = 0; i < 13; i++)//i������������
			{
				if (m.x > 680 && m.y > 185 + 30 * i && m.x < 720 && m.y < 205 + 30 * i)//��갴��ά������
					return i + 101;
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 205 + 30 * i)//��갴�ڲ鿴����
					return i + 201;
			}
		}
	}
}

int RepairMENU_RepairMENU_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//������������
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//��갴����ҳ����
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//��갴�ڶ�������
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//��갴���˳�����
				return 0;
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//��갴�ڷ�������
				return 3;			
			
			if (m.x > 175 && m.y > 495 && m.x < 205 && m.y < 525)//��갴����һҳ����
				return 41;
			if (m.x > 265 && m.y > 495 && m.x < 295 && m.y < 525)//��갴����һҳ����
				return 42;
			for (int i = 0; i < 10; i++)//i������������
			{
				if (m.x > 685 && m.y > 180 + 30 * i && m.x < 725 && m.y < 185 + 30 * i)//��갴��ɾ������
					return i + 101;
			}
		}
	}
}