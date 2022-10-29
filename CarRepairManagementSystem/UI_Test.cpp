#pragma once
#include"head.h"

MYSQL mysql;
int UserID;
//char UserName[46]="";
//int Role;

//MYsql的查询操作
//MYSQL_RES* res; //查询结果集
//MYSQL_ROW row;  //记录结构体


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







	//UserID = 34;
	//Role = 2;
	//strcpy(UserName, "B19030314");

	//RepairMENU();
	//RepairMENU_MainMENU();

	int MENUchoice = startMENU();

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

			MENUchoice = 1;
			break;
		case 101:

			MENUchoice = 1;
			break;
		case 102:
			RepairMENU_MainMENU();
			MENUchoice = 1;
			break;
		case 103:
			QualityMENU_MainMENU();
			break;
		case 104:

			MENUchoice = 1;
			break;
		case 105:

			MENUchoice = 1;
			break;
		}
	}
}