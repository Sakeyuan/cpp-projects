#include"orderFile.h"
OrderFile::OrderFile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string s[] = { "����","ѧ��","ԤԼ����","ʱ���","������","ԤԼ״̬" };
	//string ԤԼ����;
	//string ʱ���;
	//string ѧ��;
	//string ����;
	//string ������;
	//string ״̬;//ԤԼ״̬
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
//����ԤԼ��¼
void OrderFile::updateOrder() {
	if (this->m_Size == 0) {   //�ļ�����Ϊ0
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0;i < this->m_Size;++i) {
		ofs << "����:" << this->m_OrderData[i]["����"] << " ";
		ofs << "ѧ��:" << this->m_OrderData[i]["ѧ��"] << " ";
		ofs << "ԤԼ����:" << this->m_OrderData[i]["ԤԼ����"] << " ";
		ofs << "ʱ���:" << this->m_OrderData[i]["ʱ���"] << " ";
		ofs << "������:" << this->m_OrderData[i]["������"] << " ";
		ofs << "ԤԼ״̬:" << this->m_OrderData[i]["ԤԼ״̬"] << endl;
	}
	ofs.close();
}