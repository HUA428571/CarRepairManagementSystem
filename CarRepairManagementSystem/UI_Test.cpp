#pragma once
#include"head.h"
//# define HEAD
//#include <time.h>
//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <stdlib.h>
//
//#include <graphics.h>
//#include <easyx.h>
//#include <conio.h>
//#include <mysql.h>
//using namespace std;
//MYSQL mysql;
//#define FONT "黑体"

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



	//临时测试代码
	initgraph(1280, 720, EW_NOCLOSE);	// 创建绘图窗口，大小为 1280x720 像素
	cleardevice();
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	LOGFONT format;
	gettextstyle(&format);						// 获取当前字体设置
	format.lfHeight = 30;						// 设置字体高度为30
	format.lfQuality = PROOF_QUALITY;			// 设置输出效果为最高质量  
	format.lfPitchAndFamily = FIXED_PITCH;
	_tcscpy_s(format.lfFaceName, _T("黑体"));	// 设置字体为FONT2_EN
	settextstyle(&format);						// 设置字体样式

	IMAGE BG;
	loadimage(&BG, _T(".\\IMAGES\\RepairMENU_Home.png"), 1280, 720);
	putimage(0, 0, &BG);

	settextstyle(20, 0, FONT);
	//outtextxy(180, 185, mysql_error(&mysql));
	outtextxy(180, 215, "连接成功");
	//outtextxy(100, 130, "注册成功 1  23456789");

	while(1);


	return 0;
}