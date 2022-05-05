#include"speechManager.h"
//���캯��
SpeechManager::SpeechManager(){
	//��ʼ������������
	this->initSpeech();
	//����12��ѡ��
	this->createSpeaker();
	//���������¼
	this->loadRecord();
}
//��������
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "*****************************" << endl;
	cout << "******��ӭ�μ��ݽ�����*******" << endl;
	cout << "*******1.��ʼ�ݽ�����********" << endl;
	cout << "*******2.�鿴�����¼********" << endl;
	cout << "*******3.��ձ�����¼********" << endl;
	cout << "*******0.�˳���������********" << endl;
	cout << "*****************************" << endl;
	cout << endl;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHJKLI";
	for (int i = 0;i < nameSeed.size();++i) {
		string name = "ѡ��";
		name = nameSeed[i] + name;
		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0;i < 2;++i) {
			sp.m_Score[0] = 0;
		}
		//����ѡ�ֱ�ţ������뵽v1����
		this->v1.push_back(i+10001);
		//ѡ�ֱ���Լ���Ӧѡ�ַ����������ŵ�map����
		this->m_Speaker.insert(make_pair(i+10001,sp));
	}
}
//��ʼ����
void SpeechManager::startSpeech() {
	//��һ�ֱ�����ʼ
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();

	//�ڶ��ֱ�����ʼ
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore(); 
	//4.�����¼���ļ���
	this->saveRecord();

	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeech();
	//����12��ѡ��
	this->createSpeaker();
	//���������¼
	this->loadRecord();

	cout << "����������" << endl;
	system("pause");
	system("cls");
}
//��ǩ
void SpeechManager::speechDraw() {
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------" << endl;
	cout << "��ǩ˳�������£�" << endl;
	if (this->m_Index == 1) {
		//��һ�ֱ���
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin();it != v2.end();++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "----------------------------------" << endl;
	system("pause");
	cout << endl;
}
//����
void SpeechManager::speechContest() {
	cout << "------------��" << this->m_Index << "�ֱ�����ʽ��ʼ----------" << endl;
	vector<int>v_Src;//����ѡ������
	//׼����ʱ���������С��ɼ�
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//��¼��������
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//��������ѡ��
	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end();++it) {
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0;i < 10;++i) {
			double score = (rand() % 401 + 600)/10.f;//600~1000,ȡС��
			//cout << score<<" ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(),d.end(),greater<double>());//��������
		d.pop_back();//ȥ����ͷ�
		d.pop_front();//ȥ����߷�
		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();//ƽ����
		//��ƽ���ַ���map����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));//key�ǵ÷֣�value��ѡ�ֱ��
		//ÿ6����ȡǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();++it) {
				cout << "��� ��" << it->second << "  ������" << this->m_Speaker[it->second].m_Name << "  �ɼ�:" 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//ȡǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end()&&count<3;++it,++count) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//С���������	
			cout << endl;
		}
	}
	cout << "------------------��" << this->m_Index << "�ֱ������----------------" << endl;
	system("pause");
}

//��ʾ�÷�
void SpeechManager::showScore() {
	cout << "--------------��" << this->m_Index << "��ѡ�ֽ������£�--------------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();++it) {
		cout << "ѡ�ֱ�ţ�" << *it << "  ������" << this->m_Speaker[*it].m_Name 
			<< "  �÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;

	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//�������
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//��׷�ӷ�ʽд���ļ�
	//��ÿ��ѡ������д���ļ� 
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();++it) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs<< endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	//�����ļ���Ϊ�յ�״̬
	this->fileIsEmpty = false;
}
//��ȡ�����¼
void SpeechManager:: loadRecord() {
	ifstream ifs("speech.csv",ios::in);//���ļ�
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ���ȡ����
	string data;
	int index = 0;//����
	while (ifs>>data)
	{
		int pos = -1;//���Ҷ���λ��
		int start = 0;
		vector<string>v;//���6���ַ���
		
		while(true){
			pos = data.find(",", start);
			if (pos == -1) {
				//û�ҵ�
				break;
			}
			string temp = data.substr(start, pos - start);//��ȡ����ǰ���ַ�
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}
//��ʾ�����¼
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ�Ϊ�ջ��߲�����" << endl;
	}
	else {
		for (map<int, vector<string>>::iterator it = m_Record.begin();it != m_Record.end();++it) {
			cout << "��" << it->first << "��"
				<< "�ھ���ţ�" << it->second[0] << "  �÷֣�" << it->second[1] << " "
				<< "�Ǿ���ţ�" << it->second[2] << "  �÷֣�" << it->second[3] << " "
				<< "������ţ�" << it->second[4] << "  �÷֣�" << it->second[5] << endl;
		}
	}
	system("pause");
	system, ("cls");
}

void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	//����¼���������
	this->m_Record.clear();
}
//��ռ�¼
void SpeechManager:: clearRecord() {
	cout << "�Ƿ�ȷ����ռ�¼?" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������������
		this->initSpeech();
		//����12��ѡ��
		this->createSpeaker();
		//���������¼
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}