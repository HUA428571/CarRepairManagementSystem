#pragma once
#include"head.h"

int StartMENU_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//������������
		{
			if (m.y > 290 && m.y < 340 && m.x>470 && m.x < 810)//��갴�������˺�����
				return 1;
			if (m.y > 370 && m.y < 420 && m.x>470 && m.x < 810)//��갴��������������
				return 2;
			if (m.y > 630 && m.y < 680 && m.x>40 && m.x < 40 + 152)//��갴���˳�����
				return 61;
			if (m.y > 630 && m.y < 680 && m.x>222 && m.x < 222 + 160)//��갴�ڷÿͶ�����ѯ����
				return 62;

		}
	}
}

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
			if (m.x > 320 && m.y > 580 && m.x < 320 + 120 && m.y < 620)//��갴�����ж�������
				return 43;
			if (m.x > 460 && m.y > 580 && m.x < 460 + 120 && m.y < 620)//��갴�ڴ�ά�޶�������
				return 44;

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
				if (m.x > 685 && m.y > 185 + 30 * i && m.x < 725 && m.y < 205 + 30 * i)//��갴��ɾ������
					return i + 101;
			}
			if (m.x > 491 && m.y > 545 && m.x < 491 + 75 && m.y < 545 + 75)//��갴������������
				return 51;
			if (m.x > 578 && m.y > 545 && m.x < 578 + 75 && m.y < 545 + 75)//��갴����ӹ�ʱ����
				return 52;
			if (m.x > 665 && m.y > 545 && m.x < 665 + 75 && m.y < 545 + 75)//��갴���������
				return 53;
		}
	}
}
int RepairMENU_RepairMENU_AddPart_MENUChoose()
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

			if (m.x > 578 && m.y > 545 && m.x < 578 + 75 && m.y < 545 + 75)//��갴��ȡ������
				return 52;
			if (m.x > 665 && m.y > 545 && m.x < 665 + 75 && m.y < 545 + 75)//��갴�����/��������
				return 53;
		}
	}
}

int QualityMENU_MainMENU_MENUChoose()
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
			if (m.x > 320 && m.y > 580 && m.x < 320 + 120 && m.y < 620)//��갴�����ж�������
				return 43;
			if (m.x > 460 && m.y > 580 && m.x < 460 + 120 && m.y < 620)//��갴�ڴ��ʼ충������
				return 44;

			for (int i = 0; i < 13; i++)//i������������
			{
				if (m.x > 680 && m.y > 185 + 30 * i && m.x < 720 && m.y < 205 + 30 * i)//��갴���ʼ�����
					return i + 101;
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 205 + 30 * i)//��갴�ڲ鿴����
					return i + 201;
			}
		}
	}
}

int ReceptionMENU_MainMENU_MENUChoose()
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
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//��갴���������
				return 4;

			if (m.x > 175 && m.y > 585 && m.x < 205 && m.y < 615)//��갴����һҳ����
				return 41;
			if (m.x > 265 && m.y > 585 && m.x < 295 && m.y < 615)//��갴����һҳ����
				return 42;
			if (m.x > 315 && m.y > 580 && m.x < 315 + 100 && m.y < 620)//��갴�����ж�������
				return 43;
			if (m.x > 430 && m.y > 580 && m.x < 430 + 100 && m.y < 620)//��갴�ڵȴ�ά�޶�������
				return 44;
			if (m.x > 545 && m.y > 580 && m.x < 545 + 100 && m.y < 620)//��갴�ڵȴ��ʼ충������
				return 45;
			if (m.x > 660 && m.y > 580 && m.x < 660 + 100 && m.y < 620)//��갴�ڵȴ�֧����������
				return 46;

			for (int i = 0; i < 13; i++)//i������������
			{
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 205 + 30 * i)//��갴�ڲ鿴����
					return i + 201;
			}
		}
	}
}
int ReceptionMENU_AddMENU_MENUChoose()
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
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//��갴���������
				return 4;

			if (m.x > 333 && m.y > 215 && m.x < 333+220 && m.y < 215+20)//��갴�ڳ��ƺ�����
				return 71;
			if (m.x > 333 && m.y > 245 && m.x < 333 + 220 && m.y < 245 + 20)//��갴��VIM����
				return 72;
			if (m.x > 333 && m.y > 335 && m.x < 333 + 220 && m.y < 335 + 20)//��갴�ڳ�������
				return 73;
			if (m.x > 333 && m.y > 215 && m.x < 365 + 220 && m.y < 365 + 20)//��갴�ڳ����ֻ�����
				return 74;
			if (m.x > 183 && m.y > 455 && m.x < 183 + 370 && m.y < 455 + 80)//��갴��״����������
				return 75;

			if (m.x > 183 && m.y > 591 && m.x < 183+88 && m.y < 591+22)//��갴�����ά��Ա����
				return 41;
			if (m.x > 295 && m.y > 591 && m.x < 295 + 88 && m.y < 591 + 22)//��갴������ʼ�Ա����
				return 42;
			if (m.x > 413 && m.y > 560 && m.x < 413 + 70 && m.y < 560 + 68)//��갴��ȡ������
				return 43;
			if (m.x > 498 && m.y > 560 && m.x < 498 + 70 && m.y < 560 + 68)//��갴���������
				return 44;
		}
	}
}


int QualityMENU_QualityMENU_MENUChoose()
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

			if (m.x > 490 && m.y > 545 && m.x < 490 + 75 && m.y < 545 + 75)//��갴���˻�ά������
				return 61;
			if (m.x > 620 && m.y > 545 && m.x < 620 + 75 && m.y < 545 + 75)//��갴��ͨ���ʼ�����
				return 62;
		}
	}
}

int OrderCheckMENU_MENUChoose()
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
			//if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//��갴�ڶ�������
			//	return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//��갴���˳�����
				return 0;
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//��갴�ڷ�������
				return 3;

			if (m.x > 175 && m.y > 495 && m.x < 205 && m.y < 525)//��갴����һҳ����
				return 41;
			if (m.x > 265 && m.y > 495 && m.x < 295 && m.y < 525)//��갴����һҳ����
				return 42;
		}
	}
}
int OrderCheckMENU_Visiter_Payed_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//������������
		{
			if (m.x > 40 && m.y > 630 && m.x < 90 && m.y < 680)//��갴�ڷ�������
				return 3;

			if (m.x > 155 && m.y > 450 && m.x < 185 && m.y < 480)//��갴����һҳ����
				return 41;
			if (m.x > 245 && m.y > 450 && m.x < 275 && m.y < 480)//��갴����һҳ����
				return 42;
		}
	}
}
int OrderCheckMENU_Visiter_UnPay_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// ��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//������������
		{
			if (m.x > 40 && m.y > 630 && m.x < 90 && m.y < 680)//��갴�ڷ�������
				return 3;

			if (m.x > 155 && m.y > 450 && m.x < 185 && m.y < 480)//��갴����һҳ����
				return 41;
			if (m.x > 245 && m.y > 450 && m.x < 275 && m.y < 480)//��갴����һҳ����
				return 42;
			if (m.x > 1020 && m.y > 495 && m.x < 1130 && m.y < 570)//��갴��֧������
				return 43;
		}
	}
}