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
			if (m.x > 175 && m.y > 585 && m.x < 205 && m.y < 615)//��갴����һҳ����
				return 41;
			if (m.x > 265 && m.y > 585 && m.x < 295 && m.y < 615)//��갴����һҳ����
				return 42;
			for (int i = 0; i < 15; i++)//i������������
			{
				if (m.x > 680 && m.y > 185 + 30 * i && m.x < 720 && m.y < 185 + 30 * i)//��갴��ά������
					return i + 101;
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 185 + 30 * i)//��갴�ڲ鿴����
					return i + 101;
			}



			//if (m.y > 90 && m.y < 135 && m.x>590 && m.x < 690)//��갴���������
			//	return 2;
			//if (m.y > 90 && m.y < 135 && m.x>790 && m.x < 890)//��갴��ɾ������
			//	return 3;
			//if (m.y > 90 && m.y < 135 && m.x>990 && m.x < 1090)//��갴�ڸ�������
			//	return 4;
		}
	}
}