#include"teacher.h"
#include"orderFile.h"

//默认构造
Teacher::Teacher() {

}
//有参构造
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_empId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;

}
//菜单界面
void Teacher::operMenu() {
	cout << "欢迎您: " << this->m_Name << "  登录！" << endl;
	cout << "\t\t ________________________________\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         1.查看所有预约         |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         2.审核预约             |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|         0.注 销 登 录          |\n";
	cout << "\t\t|________________________________|\n";
	cout << "请选择您的操作:" << endl;
}
// 查看所有预约
void Teacher::showAllOrder() {
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
// 审核预约
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约记录如下: " << endl;
	vector<int>v;//存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0;i < of.m_Size;++i) {
		//判断 是自身学号
		if (of.m_OrderData[i]["预约状态"] == "1") {

			v.push_back(i);
			cout << index++ << "、";
			cout << "学号:" << of.m_OrderData[i]["学号"] << " ";
			cout << "姓名:" << of.m_OrderData[i]["姓名"] << " ";
			cout << "预约日期:周" << of.m_OrderData[i]["预约日期"] << " ";
			cout << "时间段:" << (of.m_OrderData[i]["时间段"] == "1" ? "上午" : "下午") << " ";
			cout << "机房号:" << of.m_OrderData[i]["机房号"] << " ";
			string status = "预约状态:审核中";
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录，0返回" << endl;
	int select = 0;
	int ret = 0;//结束预约结果记录
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "请输入审核结果:" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;
				if (ret == 1) {//通过
					of.m_OrderData[v[select - 1]]["预约状态"] = "2";
				}
				else {//不通过
					of.m_OrderData[v[select - 1]]["预约状态"] = "-1";
				}
				of.updateOrder();
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}
void Teacher::initComputerRoom() {
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