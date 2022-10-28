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







	UserID = 23;
	//Role = 2;
	//strcpy(UserName, "B19030314");

	//RepairMENU();
	RepairMENU_MainMENU();
	
	mysql_close(&mysql);
	return 0;
}