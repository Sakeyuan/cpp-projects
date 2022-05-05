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
//����ݽ�������
class SpeechManager{
public:
	SpeechManager();
	~SpeechManager(); 
	//��ʼ������������
	void initSpeech();
	//�˵�����
	void show_Menu();
	//����12����
	void createSpeaker();
	//��ʼ���������Ʊ�������
	void startSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showScore();
	//�������
	void saveRecord();
	//��ȡ�����¼
	void loadRecord();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//��������¼������
	map<int, vector<string>>m_Record;
	//��ʾ�����¼
	void showRecord();
	//�˳�ϵͳ
	void exitSystem();
	//��Ա����
	//�����һ��ѡ�ֱ������
	vector<int>v1; 
	//��һ�ֽ���ѡ�ֱ��
	vector<int>v2;
	//ʤ��ǰ����ѡ�ֱ��
	vector<int>vVictory;
	//��ű���Լ���Ӧѡ������
	map<int, Speaker>m_Speaker;
	//��¼��������
	int m_Index;
	//��ռ�¼
	void clearRecord();
};