#pragma once
#include<iostream>
#include"Identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globleFile.h"
using namespace std;
class Teacher :public Identity {
public:
	//Ĭ�Ϲ���
	Teacher();
	//�вι���
	Teacher(int empId, string name, string pwd);
	//�˵�����
	virtual void operMenu();
	// �鿴����ԤԼ
	void showAllOrder();
	// ȡ��ԤԼ
	void validOrder();
	//ְ����
	int m_empId;
	//��ʼ��������Ϣ
	vector<computerRoom>vCom;
	virtual void initComputerRoom();
};