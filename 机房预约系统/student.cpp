#include"student.h"
#include"orderFile.h"

//默认构造
Student::Student() {

}
//有参构造
Student::Student(int id, string name, string pwd) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initComputerRoom();
}
//菜单界面
void Student::operMenu() {
	cout << "欢迎您: " << this->m_Name << "  登录！" << endl;
	cout << "\t\t ________________________________\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         1.申 请 预 约          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         2.查看我的预约         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         3.查看所有预约         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         4.取 消 预 约          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         0.注 销 登 录          |\n";
	cout << "\t\t|________________________________|\n";
	cout << "请选择您的操作:" << endl;
}
//申请预约
void Student::applyOrder() {
	cout << "机房开放时间周一到周五" << endl;
	cout << "请输入预约时间:" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房号
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请输入预约时间段:" << endl;
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请选择机房号:" << endl;
	for (int i = 0;i < vCom.size();++i) {
		cout << vCom[i].m_ComID << " 机房容量为:" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功,等待管理员同意" << endl;
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "姓名:" << this->m_Name << " ";
	ofs << "学号:" << this->m_Id << " ";
	ofs << "预约日期:" << date << " ";
	ofs << "时间:" << interval << " ";
	ofs << "机房号:" << room << " ";
	ofs << "预约状态:" << 1 << endl;//1为审核中
	ofs.close();
	system("pause");
	system("cls");
}
// 查看自身预约
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;++i) {
		if (this->m_Id == atoi(of.m_OrderData[i]["学号"].c_str())) {
			//string转int,string利用c_str转const char*,再利用atoi(const char*)转int
			cout << "预约日期:周" << of.m_OrderData[i]["预约日期"] << " ";
			cout << "时间段:" << (of.m_OrderData[i]["时间段"] == "1" ? "上午" : "下午") << " ";
			cout << "机房号:" << of.m_OrderData[i]["机房号"] << " ";
			string status = "预约状态:";
			//1-审核中 2-已预约  -1 预约失败 0-取消预约
			if (of.m_OrderData[i]["预约状态"] == "1") {
				status += "审核中";
			}
			else if (of.m_OrderData[i]["预约状态"] == "2") {
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["预约状态"] == "-1") {
				status += "预约失败，审核未通过";
			}
			else {
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}
// 查看所有预约
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_Size;++i) {
		cout << i + 1 << "、";
		cout << "预约日期:周" << of.m_OrderData[i]["预约日期"] << " ";
		cout << "时间段:" << (of.m_OrderData[i]["时间段"] == "1" ? "上午" : "下午") << " ";
		cout << "学号:" << of.m_OrderData[i]["学号"] << " ";
		cout << "姓名:" << of.m_OrderData[i]["姓名"] << " ";
		cout << "机房号:" << of.m_OrderData[i]["机房号"] << " ";
		string status = "预约状态:";
		//1-审核中 2-已预约  -1 预约失败 0-取消预约
		if (of.m_OrderData[i]["预约状态"] == "1") {
			status += "审核中";
		}
		else if (of.m_OrderData[i]["预约状态"] == "2") {
			status += "预约成功";
		}
		else if (of.m_OrderData[i]["预约状态"] == "-1") {
			status += "预约失败，审核未通过";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}
// 取消预约
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或者预约成功的记录可以取消，请输入要取消的记录" << endl;
	vector<int>v;//存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0;i < of.m_Size;++i) {
		//判断 是自身学号
		if (this->m_Id == atoi(of.m_OrderData[i]["学号"].c_str())) {
			//再筛选状态
			if (of.m_OrderData[i]["预约状态"] == "1" || of.m_OrderData[i]["预约状态"] == "2") {
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期:周" << of.m_OrderData[i]["预约日期"] << " ";
				cout << "时间段:" << (of.m_OrderData[i]["时间段"] == "1" ? "上午" : "下午") << " ";
				cout << "机房号:" << of.m_OrderData[i]["机房号"] << " ";
				string status = "预约状态:";
				//1-审核中 2-已预约  -1 预约失败 0-取消预约
				if (of.m_OrderData[i]["预约状态"] == "1") {
					status += "审核中";
				}
				else if (of.m_OrderData[i]["预约状态"] == "2") {
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入要取消的记录，0返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.m_OrderData[v[select - 1]]["预约状态"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
void Student::initComputerRoom() {
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