#pragma once
#include<iostream>
#include"Identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globleFile.h"
using namespace std;
class Student :public Identity {
public:
	//Ĭ�Ϲ���
	Student();
	//�вι���
	Student(int id, string name, string pwd);
	//�˵�����
	virtual void operMenu();
	//����ԤԼ
	void applyOrder();
	// �鿴����ԤԼ
	void showMyOrder();
	// �鿴����ԤԼ
	void showAllOrder();
	// ȡ��ԤԼ
	void cancelOrder();
	//ѧ��
	int m_Id;
	//������Ϣ
	vector<computerRoom>vCom;
	virtual void initComputerRoom();
};