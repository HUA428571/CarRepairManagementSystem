#pragma once
#include"head.h"
#include "MENUchoose.h"
int RepairMENU_MainMENU_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//如果左键被按下
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//鼠标按在主页区域
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//鼠标按在订单区域
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//鼠标按在退出区域
				return 0;

			if (m.x > 175 && m.y > 585 && m.x < 205 && m.y < 615)//鼠标按在上一页区域
				return 41;
			if (m.x > 265 && m.y > 585 && m.x < 295 && m.y < 615)//鼠标按在下一页区域
				return 42;
			if (m.x > 320 && m.y > 580 && m.x < 320+120 && m.y < 620)//鼠标按在所有订单区域
				return 43;
			if (m.x > 460 && m.y > 580 && m.x < 460+120 && m.y < 620)//鼠标按在待维修订单区域
				return 44;

			for (int i = 0; i < 13; i++)//i用来计算行数
			{
				if (m.x > 680 && m.y > 185 + 30 * i && m.x < 720 && m.y < 205 + 30 * i)//鼠标按在维修区域
					return i + 101;
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 205 + 30 * i)//鼠标按在查看区域
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
		// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//如果左键被按下
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//鼠标按在主页区域
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//鼠标按在订单区域
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//鼠标按在退出区域
				return 0;
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//鼠标按在返回区域
				return 3;			
			
			if (m.x > 175 && m.y > 495 && m.x < 205 && m.y < 525)//鼠标按在上一页区域
				return 41;
			if (m.x > 265 && m.y > 495 && m.x < 295 && m.y < 525)//鼠标按在下一页区域
				return 42;
			for (int i = 0; i < 10; i++)//i用来计算行数
			{
				if (m.x > 685 && m.y > 185 + 30 * i && m.x < 725 && m.y < 205 + 30 * i)//鼠标按在删除区域
					return i + 101;
			}
			if (m.x > 491 && m.y > 545 && m.x < 491+75 && m.y < 545+75)//鼠标按在添加配件区域
				return 51;
			if (m.x > 578 && m.y > 545 && m.x < 578+75 && m.y < 545 + 75)//鼠标按在添加工时区域
				return 52;
			if (m.x > 665 && m.y > 545 && m.x < 665+75 && m.y < 545 + 75)//鼠标按在完成区域
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
		// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//如果左键被按下
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//鼠标按在主页区域
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//鼠标按在订单区域
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//鼠标按在退出区域
				return 0;
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//鼠标按在返回区域
				return 3;

			if (m.x > 578 && m.y > 545 && m.x < 578 + 75 && m.y < 545 + 75)//鼠标按在取消区域
				return 52;
			if (m.x > 665 && m.y > 545 && m.x < 665 + 75 && m.y < 545 + 75)//鼠标按在添加/申请区域
				return 53;
		}
	}
}

int OrderCheckMENU_MENUChoose()
{
	FlushMouseMsgBuffer();
	while (true)
	{
		MOUSEMSG m;
		// 获取一条鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)//如果左键被按下
		{
			if (m.x > 80 && m.y > 80 && m.x < 130 && m.y < 130)//鼠标按在主页区域
				return 1;
			if (m.x > 80 && m.y > 170 && m.x < 130 && m.y < 220)//鼠标按在订单区域
				return 2;
			if (m.x > 80 && m.y > 260 && m.x < 130 && m.y < 310)//鼠标按在退出区域
				return 0;
			if (m.x > 80 && m.y > 350 && m.x < 130 && m.y < 400)//鼠标按在返回区域
				return 3;

			if (m.x > 175 && m.y > 495 && m.x < 205 && m.y < 525)//鼠标按在上一页区域
				return 41;
			if (m.x > 265 && m.y > 495 && m.x < 295 && m.y < 525)//鼠标按在下一页区域
				return 42;
		}
	}
}