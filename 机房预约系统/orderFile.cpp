#include"orderFile.h"
OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string s[] = { "姓名","学号","预约日期","时间段","机房号","预约状态" };
	//string 预约日期;
	//string 时间段;
	//string 学号;
	//string 姓名;
	//string 机房号;
	//string 状态;//预约状态
	this->m_Size = 0;
	while (ifs >> s[0] && ifs >> s[1] && ifs >> s[2] && ifs >> s[3] && ifs >> s[4] && ifs >> s[5])
	{
		//data:1
		string key;
		string value;
		map<string, string>m;
		for (int i = 0;i < 6;++i) {
			int pos = s[i].find(":");
			if (pos != -1) {
				key = s[i].substr(0, pos);
				value = s[i].substr(pos + 1, s[i].size() - pos - 1);
				m.insert(make_pair(key, value));
			}
		}
		this->m_OrderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();
}
//更新预约记录
void OrderFile::updateOrder() {
	if (this->m_Size == 0) {   //文件条数为0
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0;i < this->m_Size;++i) {
		ofs << "姓名:" << this->m_OrderData[i]["姓名"] << " ";
		ofs << "学号:" << this->m_OrderData[i]["学号"] << " ";
		ofs << "预约日期:" << this->m_OrderData[i]["预约日期"] << " ";
		ofs << "时间段:" << this->m_OrderData[i]["时间段"] << " ";
		ofs << "机房号:" << this->m_OrderData[i]["机房号"] << " ";
		ofs << "预约状态:" << this->m_OrderData[i]["预约状态"] << endl;
	}
	ofs.close();
}