#include"manager.h"

//Ĭ�Ϲ���
Manager::Manager() {

}
//�вι���
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	//��ʼ����ʦ��ѧ����Ϣ������
	this->initVector();
	this->initComputerRoom();
}
//�˵�����
void Manager::operMenu() {
	cout << "��ӭ����Ա: " << this->m_Name << " ��¼��" << endl;
	cout << "\t\t ____________________________\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         1.����˺�         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         2.�鿴�˺�         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         3.�鿴����         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         4.���ԤԼ         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         0.ע����¼         |\n";
	cout << "\t\t|____________________________|\n";
	cout << "��ѡ�����Ĳ���:" << endl;
}
//����˺�
void Manager::addPerson() {
	cout << "����������˺�����:" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;
	string fileName;//�����ļ���
	string tip;//��ʾid��
	ofstream ofs;//�ļ���������
	string errorTip;//�����ظ���ʾ
	int select;
	cin >> select;
	if (select == 1) {
		//���ѧ��
		fileName = STUDENT_FILE;
		tip = "������ѧ��:";
		errorTip = "ѧ���ظ�������������";
	}
	else {
		//��ӽ�ʦ
		fileName = TEACHER_FILE;
		tip = "������ְ����:";
		errorTip = "ְ�����ظ�������������";
	}
	ofs.open(fileName, ios::out | ios::app);//����׷�ӷ�ʽд���ļ�
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	//�ظ����
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) {
			//���ظ�
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "����������:" << endl;
	cin >> name;
	cout << "����������:" << endl;
	cin >> pwd;
	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
	ofs.close();
	//��ʼ������ȡ��������
	this->initVector();
}
//�������
void printStudent(Student& s) {
	cout << "ѧ��:" << s.m_Id << "  ����:" << s.m_Name << "  ����:" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t) {
	cout << "ְ����:" << t.m_empId << "  ����:" << t.m_Name << "  ����:" << t.m_Pwd << endl;
}
//�鿴�˻�
void Manager::showPerson() {
	cout << "������鿴����:" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴���н�ʦ" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//�鿴ѧ��
		cout << "����ѧ����Ϣ����:" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else {
		//�鿴ѧ��
		cout << "���н�ʦ��Ϣ����:" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
//�鿴������Ϣ
void Manager::showComputer() {
	cout << "������Ϣ����:" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin();it != vCom.end();++it) {
		cout << "������:" << it->m_ComID << "  �����������:" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//���ԤԼ��¼
void Manager::clearFile() {
	int select = 0;
	cout << "�Ƿ�ȷ�����ԤԼ��" << endl;
	cout << "1.yes" << endl;
	cout << "2.no" << endl;
	cin >> select;
	if (select == 1) {
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "��ճɹ���" << endl;
	}
	else if (select == 2) {
		system("cls");
		return;
	}
	system("pause");
	system("cls");
}
void Manager::initVector() {
	//��ȡ��Ϣ
	vStu.clear();//ȷ���ļ����״̬
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "��ǰѧ������" << vStu.size() << endl;
	ifs.close();
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����" << vTea.size() << endl;
	ifs.close();
}
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		//���ѧ��
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();++it) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		//�����ʦ
		for (vector<Teacher>::iterator it = vTea.begin();it != vTea.end();++it) {
			if (id == it->m_empId) {
				return true;
			}
		}
	}
	return false;
}
void Manager::initComputerRoom() {
	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom com;
	while (ifs >> com.m_ComID && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
	cout << "��������" << vCom.size() << endl;
}