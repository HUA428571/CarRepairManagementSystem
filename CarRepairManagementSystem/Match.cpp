#pragma once
#include "head.h"

//匹配订单状态（状态代码，输出字符串）
void MatchStatus(int status, char* STATUS)
{
	switch (status)
	{
	case 1:
		strcpy(STATUS, "订单创建");
		settextcolor(COLOR_PURPLE);
		return;
	case 21:
		strcpy(STATUS, "等待配件");
		settextcolor(COLOR_BLUE);
		return;
	case 22:
		strcpy(STATUS, "质检退回");
		settextcolor(COLOR_RED);
		return;
	case 3:
		strcpy(STATUS, "等待质检");
		settextcolor(COLOR_ORANGE);
		return;
	case 4:
		strcpy(STATUS, "待支付");
		settextcolor(COLOR_DEEP_BLUE);
		return;
	case 5:
		strcpy(STATUS, "订单完成");
		settextcolor(COLOR_GREEN);
		return;
	default:
		strcpy(STATUS, "无状态信息");
		settextcolor(COLOR_GREY_2);
		return;
	}
}

//匹配人员类型（人员代码，输出字符串）
void MatchRole(int role, char* ROLE)
{
	switch (role)
	{
	case 0:
		strcpy(ROLE, "    管理员");
		return;
	case 1:
		strcpy(ROLE, "  接待专员");
		return;
	case 2:
		strcpy(ROLE, "  维修专员");
		return;
	case 3:
		strcpy(ROLE, "  质检专员");
		return;
	case 4:
		strcpy(ROLE, "  库管专员");
		return;
	default:
		strcpy(ROLE, "无人员信息");
		return;
	}
}
void MatchRole_with_color(int role, char* ROLE)
{
	switch (role)
	{
	case 0:
		strcpy(ROLE, "管理员");
		settextcolor(COLOR_GREEN);
		return;
	case 1:
		strcpy(ROLE, "接待专员");
		settextcolor(COLOR_PURPLE);
		return;
	case 2:
		strcpy(ROLE, "维修专员");
		settextcolor(COLOR_BLUE);
		return;
	case 3:
		strcpy(ROLE, "质检专员");
		settextcolor(COLOR_ORANGE);
		return;
	case 4:
		strcpy(ROLE, "库管专员");
		settextcolor(COLOR_RED);
		return;
	default:
		strcpy(ROLE, "无信息");
		return;
	}
}


//输出符合MySQL格式的日期
void MatchDate(char* buffer_Date)
{
	time_t NOW;
	tm* Local;
	NOW = time(NULL);
	Local = localtime(&NOW);
	sprintf(buffer_Date, "%04d-%02d-%02d", Local->tm_year + 1900, Local->tm_mon + 1, Local->tm_mday);
	return;
}
