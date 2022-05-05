#pragma once 
#include<iostream>
#include"Identity.h"
#include<fstream>
#include<vector>
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include<string>
#include"globleFile.h"
#include"computerRoom.h"
using namespace std;
class Manager :public Identity {
public:
	//Ĭ�Ϲ���
	Manager();
	//�вι���
	Manager(string name, string pwd);
	//�˵�����
	virtual void operMenu();
	//����˺�
	void addPerson();
	//�鿴�˻�
	void showPerson();
	//�鿴������Ϣ
	void showComputer();
	//���ԤԼ��¼
	void clearFile();
	//��ʼ������
	void initVector();
	//ѧ������
	vector<Student>vStu;
	//��ʦ����
	vector<Teacher>vTea;
	//����,����1 ���ѧ��/ְ���� ����2 �������
	bool checkRepeat(int id, int type);
	//��ʼ��������Ϣ
	vector<computerRoom>vCom;
	virtual void initComputerRoom();
};