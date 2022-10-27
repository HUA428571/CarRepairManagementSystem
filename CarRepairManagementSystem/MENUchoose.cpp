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
			if (m.x > 175 && m.y > 585 && m.x < 205 && m.y < 615)//鼠标按在上一页区域
				return 41;
			if (m.x > 265 && m.y > 585 && m.x < 295 && m.y < 615)//鼠标按在下一页区域
				return 42;
			for (int i = 0; i < 15; i++)//i用来计算行数
			{
				if (m.x > 680 && m.y > 185 + 30 * i && m.x < 720 && m.y < 185 + 30 * i)//鼠标按在维修区域
					return i + 101;
				if (m.x > 735 && m.y > 180 + 30 * i && m.x < 775 && m.y < 185 + 30 * i)//鼠标按在查看区域
					return i + 101;
			}



			//if (m.y > 90 && m.y < 135 && m.x>590 && m.x < 690)//鼠标按在添加区域
			//	return 2;
			//if (m.y > 90 && m.y < 135 && m.x>790 && m.x < 890)//鼠标按在删除区域
			//	return 3;
			//if (m.y > 90 && m.y < 135 && m.x>990 && m.x < 1090)//鼠标按在更改区域
			//	return 4;
		}
	}
}