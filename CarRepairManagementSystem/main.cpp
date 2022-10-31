#pragma once
#include"head.h"
#define DEBUG

MYSQL mysql;
int UserID;

int main()
{
	//初始化数据库
	mysql_init(&mysql);
	//设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	if (mysql_real_connect(&mysql, "127.0.0.1", "B19030314", "B19030314", "curriculum_design_202210", 3306, NULL, 0) == NULL) {
		printf("错误： %s\n", mysql_error(&mysql));
		printf("数据库连接失败！\n");
		exit(-1);
	}

	//initgraph(1280, 720, EW_NOCLOSE);	// 创建绘图窗口，大小为 1280x720 像素
	initgraph(1280, 720);	// 创建绘图窗口，大小为 1280x720 像素
	setbkmode(TRANSPARENT);

	//字体相关设置
	LOGFONT format;
	gettextstyle(&format);						// 获取当前字体设置
	format.lfQuality = PROOF_QUALITY;			// 设置输出效果为最高质量  
	format.lfPitchAndFamily = FIXED_PITCH;
	settextstyle(&format);						// 设置字体样式

#ifdef DEBUG
	//在DEBUG模式下直接进入相应的界面
	int MENUchoice = 100;
	UserID = 1;
#endif // DEBUG

#ifndef DEBUG
	int MENUchoice = startMENU();
#endif // !DEBUG

	while (true)
	{
		switch (MENUchoice)
		{
		case 0:
			//程序结束
			mysql_close(&mysql);

			return 0;
		case 1:
			MENUchoice = startMENU();
			break;
		case 100:
			MENUchoice = AdminMENU_MainMENU();
			break;
		case 101:
			MENUchoice = ReceptionMENU_MainMENU();
			break;
		case 102:
			MENUchoice = RepairMENU_MainMENU();
			break;
		case 103:
			MENUchoice = QualityMENU_MainMENU();
		case 104:

			MENUchoice = 1;
			break;
		case 105:

			MENUchoice = 1;
			break;
		}
	}
}