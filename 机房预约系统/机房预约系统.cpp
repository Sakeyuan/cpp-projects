#include<iostream>
#include<string>
#include"globleFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include<fstream>
#include"Identity.h"
using namespace std;
//学生子系统
void studentMenu(Identity*& student) {
	while (true)
	{
		//调用学生子菜单
		student->operMenu();//将父类指针转为子类的指针，调用子类其他接口
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//申请预约
			stu->applyOrder();
		}
		else if (select == 2) {
			//查看预约
			stu->showMyOrder();
		}
		else if (select == 3) {
			//查看所有人预约
			stu->showAllOrder();
		}
		else if (select == 4) {
			//取消预约
			stu->cancelOrder();

		}
		else {
			//注销登录
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

//管理员子系统
void managerMenu(Identity*& manager) {
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();
		//将父类指针转为子类的指针，调用子类其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//添加账号
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) {
			//查看账号
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) {
			//查看机房信息
			//cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) {
			//清空预约
			//cout << "清空预约" << endl;
			man->clearFile();

		}
		else {
			delete manager;//销毁堆区
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
//教师子菜单
void teacherMenu(Identity*& teacher) {
	while (true)
	{
		//子菜单界面
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) {//查看所有预约
			tea->showAllOrder();
		}
		else if (select == 2) {//审核预约
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;

		}
	}
}
//登录操作 参数1 操作文件 参数2 登陆身份
void LoginIn(string fileName, int type) {
	//父类指针，用于指向子类对象
	Identity* person = NULL;
	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//接受用户信息
	int id;
	string name;
	string pwd;
	if (type == 1) {  //学生身份
		cout << "请输入你的学号:" << endl;
		cin >> id;
	}
	if (type == 2) {  //教师身份
		cout << "请输入您的职工号:" << endl;
		cin >> id;
	}
	cout << "请输入用户名:" << endl;
	cin >> name;
	cout << "请输入密码:" << endl;
	cin >> pwd;
	if (type == 1) {
		//学生身份验证
		int fid;//文件中读取的学生id
		string fname;//文件中读取的姓名
		string fpwd;//文件中读取的密码
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "学生登录成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		//教师身份验证
		int fid;//文件中读取的学生id
		string fname;//文件中读取的姓名
		string fpwd;//文件中读取的密码
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "教师登录成功" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		//管理员身份验证
		string fname;//文件中读取的姓名
		string fpwd;//文件中读取的密码
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd) {
				cout << "管理员登录成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				//进入管理员子菜单
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证信息失败！" << endl;
	system("pause");
	system("cls");
	return;
}

int main() {
	int select = 0;
	while (true)
	{
		cout << "****************欢迎来到机房预约系统****************" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t ______________________________\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        1.学    生            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        2.老    师            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        3.管 理 员            |\n";
		cout << "\t\t|                              |\n";
		cout << "\t\t|        0.退    出            |\n";
		cout << "\t\t|______________________________|\n";
		cout << "请输入您的选择:";
		cin >> select;//接受用户选择
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
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择!" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}