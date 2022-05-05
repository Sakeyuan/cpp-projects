#include<iostream>
#include<string>
#include"globleFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include<fstream>
#include"Identity.h"
using namespace std;
//ѧ����ϵͳ
void studentMenu(Identity*& student) {
	while (true)
	{
		//����ѧ���Ӳ˵�
		student->operMenu();//������ָ��תΪ�����ָ�룬�������������ӿ�
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2) {
			//�鿴ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3) {
			//�鿴������ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4) {
			//ȡ��ԤԼ
			stu->cancelOrder();

		}
		else {
			//ע����¼
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//����Ա��ϵͳ
void managerMenu(Identity*& manager) {
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->operMenu();
		//������ָ��תΪ�����ָ�룬�������������ӿ�
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//����˺�
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) {
			//�鿴�˺�
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3) {
			//�鿴������Ϣ
			//cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) {
			//���ԤԼ
			//cout << "���ԤԼ" << endl;
			man->clearFile();

		}
		else {
			delete manager;//���ٶ���
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
//��ʦ�Ӳ˵�
void teacherMenu(Identity*& teacher) {
	while (true)
	{
		//�Ӳ˵�����
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) {//�鿴����ԤԼ
			tea->showAllOrder();
		}
		else if (select == 2) {//���ԤԼ
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;

		}
	}
}
//��¼���� ����1 �����ļ� ����2 ��½���
void LoginIn(string fileName, int type) {
	//����ָ�룬����ָ���������
	Identity* person = NULL;
	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�����û���Ϣ
	int id;
	string name;
	string pwd;
	if (type == 1) {  //ѧ�����
		cout << "���������ѧ��:" << endl;
		cin >> id;
	}
	if (type == 2) {  //��ʦ���
		cout << "����������ְ����:" << endl;
		cin >> id;
	}
	cout << "�������û���:" << endl;
	cin >> name;
	cout << "����������:" << endl;
	cin >> pwd;
	if (type == 1) {
		//ѧ�������֤
		int fid;//�ļ��ж�ȡ��ѧ��id
		string fname;//�ļ��ж�ȡ������
		string fpwd;//�ļ��ж�ȡ������
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "ѧ����¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ���Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		//��ʦ�����֤
		int fid;//�ļ��ж�ȡ��ѧ��id
		string fname;//�ļ��ж�ȡ������
		string fpwd;//�ļ��ж�ȡ������
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "��ʦ��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ�Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		//����Ա�����֤
		string fname;//�ļ��ж�ȡ������
		string fpwd;//�ļ��ж�ȡ������
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd) {
				cout << "����Ա��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//�������Ա�Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��Ϣʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}

int main() {
	int select = 0;
	while (true)
	{
		cout << "****************��ӭ��������ԤԼϵͳ****************" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t ______________________________\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        1.ѧ    ��            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        2.��    ʦ            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        3.�� �� Ա            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        0.��    ��            |\n";
		cout << "\t\t|______________________________|\n";
		cout << "����������ѡ��:";
		cin >> select;//�����û�ѡ��
		switch (select) {
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:
			LoginIn(ADD_FILE, 3);
			break;
		case 0:
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��!" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}