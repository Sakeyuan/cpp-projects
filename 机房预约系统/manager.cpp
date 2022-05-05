#include"manager.h"

//默认构造
Manager::Manager() {

}
//有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	//初始化老师和学生信息，读入
	this->initVector();
	this->initComputerRoom();
}
//菜单界面
void Manager::operMenu() {
	cout << "欢迎管理员: " << this->m_Name << " 登录！" << endl;
	cout << "\t\t ____________________________\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         1.添加账号         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         2.查看账号         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         3.查看机房         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         4.清空预约         |\n";
	cout << "\t\t|                            |\n";
	cout << "\t\t|         0.注销登录         |\n";
	cout << "\t\t|____________________________|\n";
	cout << "请选择您的操作:" << endl;
}
//添加账号
void Manager::addPerson() {
	cout << "请输入添加账号类型:" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;
	string fileName;//操作文件名
	string tip;//提示id号
	ofstream ofs;//文件操作对象
	string errorTip;//错误重复提示
	int select;
	cin >> select;
	if (select == 1) {
		//添加学生
		fileName = STUDENT_FILE;
		tip = "请输入学号:";
		errorTip = "学号重复，请重新输入";
	}
	else {
		//添加教师
		fileName = TEACHER_FILE;
		tip = "请输入职工号:";
		errorTip = "职工号重复，请重新输入";
	}
	ofs.open(fileName, ios::out | ios::app);//利用追加方式写入文件
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	//重复检测
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret) {
			//有重复
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名:" << endl;
	cin >> name;
	cout << "请输入密码:" << endl;
	cin >> pwd;
	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	ofs.close();
	//初始化，获取最新数据
	this->initVector();
}
//输出函数
void printStudent(Student& s) {
	cout << "学号:" << s.m_Id << "  姓名:" << s.m_Name << "  密码:" << s.m_Pwd << endl;
}
void printTeacher(Teacher& t) {
	cout << "职工号:" << t.m_empId << "  姓名:" << t.m_Name << "  密码:" << t.m_Pwd << endl;
}
//查看账户
void Manager::showPerson() {
	cout << "请输入查看内容:" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有教师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//查看学生
		cout << "所有学生信息如下:" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else {
		//查看学生
		cout << "所有教师信息如下:" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
//查看机房信息
void Manager::showComputer() {
	cout << "机房信息如下:" << endl;
	for (vector<computerRoom>::iterator it = vCom.begin();it != vCom.end();++it) {
		cout << "机房号:" << it->m_ComID << "  机房最大容量:" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}
//清空预约记录
void Manager::clearFile() {
	int select = 0;
	cout << "是否确认清空预约？" << endl;
	cout << "1.yes" << endl;
	cout << "2.no" << endl;
	cin >> select;
	if (select == 1) {
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "清空成功！" << endl;
	}
	else if (select == 2) {
		system("cls");
		return;
	}
	system("pause");
	system("cls");
}
void Manager::initVector() {
	//读取信息
	vStu.clear();//确保文件清空状态
	vTea.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生数量" << vStu.size() << endl;
	ifs.close();
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前教师数量" << vTea.size() << endl;
	ifs.close();
}
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		//检测学生
		for (vector<Student>::iterator it = vStu.begin();it != vStu.end();++it) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin();it != vTea.end();++it) {
			if (id == it->m_empId) {
				return true;
			}
		}
	}
	return false;
}
void Manager::initComputerRoom() {
	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	computerRoom com;
	while (ifs >> com.m_ComID && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
	cout << "机房数量" << vCom.size() << endl;
}