#pragma once
#include<iostream>
#include"globleFile.h"
#include<fstream>
#include<map>
#include<string>
using namespace std;
class OrderFile {
public:
	OrderFile();
	//����ԤԼ��¼
	void updateOrder();
	//��¼ԤԼ����
	int m_Size;
	//��¼����ԤԼ��Ϣ������,key�����¼������value�����¼��ֵ����Ϣ
	map<int, map<string, string>>m_OrderData;

};