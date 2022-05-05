#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<string>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include"speaker.h"
#include<fstream>
#include<ctime>
using namespace std;
//设计演讲管理类
class SpeechManager{
public:
	SpeechManager();
	~SpeechManager(); 
	//初始化容器和属性
	void initSpeech();
	//菜单功能
	void show_Menu();
	//创建12个人
	void createSpeaker();
	//开始比赛，控制比赛流程
	void startSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showScore();
	//保存分数
	void saveRecord();
	//读取往届记录
	void loadRecord();
	//判断文件是否为空
	bool fileIsEmpty;
	//存放往届记录的容器
	map<int, vector<string>>m_Record;
	//显示往届记录
	void showRecord();
	//退出系统
	void exitSystem();
	//成员属性
	//保存第一轮选手编号容器
	vector<int>v1; 
	//第一轮晋级选手编号
	vector<int>v2;
	//胜出前三名选手编号
	vector<int>vVictory;
	//存放编号以及对应选手容器
	map<int, Speaker>m_Speaker;
	//记录比赛轮数
	int m_Index;
	//清空记录
	void clearRecord();
};