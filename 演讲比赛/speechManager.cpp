#include"speechManager.h"
//构造函数
SpeechManager::SpeechManager(){
	//初始化容器和属性
	this->initSpeech();
	//创建12名选手
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
}
//析构函数
SpeechManager::~SpeechManager() {

}
void SpeechManager::show_Menu() {
	cout << "*****************************" << endl;
	cout << "******欢迎参加演讲比赛*******" << endl;
	cout << "*******1.开始演讲比赛********" << endl;
	cout << "*******2.查看往届记录********" << endl;
	cout << "*******3.清空比赛记录********" << endl;
	cout << "*******0.退出比赛程序********" << endl;
	cout << "*****************************" << endl;
	cout << endl;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHJKLI";
	for (int i = 0;i < nameSeed.size();++i) {
		string name = "选手";
		name = nameSeed[i] + name;
		//创建具体选手
		Speaker sp;
		sp.m_Name = name;
		for (int i = 0;i < 2;++i) {
			sp.m_Score[0] = 0;
		}
		//创建选手编号，并加入到v1容器
		this->v1.push_back(i+10001);
		//选手编号以及对应选手放入容器，放到map容器
		this->m_Speaker.insert(make_pair(i+10001,sp));
	}
}
//开始比赛
void SpeechManager::startSpeech() {
	//第一轮比赛开始
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();

	//第二轮比赛开始
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore(); 
	//4.保存记录到文件中
	this->saveRecord();

	//重置比赛，获取记录
	//初始化容器和属性
	this->initSpeech();
	//创建12名选手
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕" << endl;
	system("pause");
	system("cls");
}
//抽签
void SpeechManager::speechDraw() {
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "-------------------------------" << endl;
	cout << "抽签顺序结果如下：" << endl;
	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin();it != v1.end();++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {//第二轮比赛
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
//比赛
void SpeechManager::speechContest() {
	cout << "------------第" << this->m_Index << "轮比赛正式开始----------" << endl;
	vector<int>v_Src;//比赛选手容器
	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;
	int num = 0;//记录人数个数
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历所有选手
	for (vector<int>::iterator it = v_Src.begin();it != v_Src.end();++it) {
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0;i < 10;++i) {
			double score = (rand() % 401 + 600)/10.f;//600~1000,取小数
			//cout << score<<" ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(),d.end(),greater<double>());//降序排序
		d.pop_back();//去除最低分
		d.pop_front();//去除最高分
		double sum = accumulate(d.begin(),d.end(),0.0f);
		double avg = sum / (double)d.size();//平均分
		//将平均分放入map容器
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));//key是得分，value是选手编号
		//每6个人取前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end();++it) {
				cout << "编号 ：" << it->second << "  姓名：" << this->m_Speaker[it->second].m_Name << "  成绩:" 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//取前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();it != groupScore.end()&&count<3;++it,++count) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//小组容器清空	
			cout << endl;
		}
	}
	cout << "------------------第" << this->m_Index << "轮比赛完毕----------------" << endl;
	system("pause");
}

//显示得分
void SpeechManager::showScore() {
	cout << "--------------第" << this->m_Index << "轮选手晋级如下：--------------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();++it) {
		cout << "选手编号：" << *it << "  姓名：" << this->m_Speaker[*it].m_Name 
			<< "  得分：" << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;

	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//保存分数
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用追加方式写入文件
	//将每个选手数据写入文件 
	for (vector<int>::iterator it = vVictory.begin();it != vVictory.end();++it) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs<< endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	//更改文件不为空的状态
	this->fileIsEmpty = false;
}
//读取往届记录
void SpeechManager:: loadRecord() {
	ifstream ifs("speech.csv",ios::in);//读文件
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符读取回来
	string data;
	int index = 0;//届数
	while (ifs>>data)
	{
		int pos = -1;//查找逗号位置
		int start = 0;
		vector<string>v;//存放6个字符串
		
		while(true){
			pos = data.find(",", start);
			if (pos == -1) {
				//没找到
				break;
			}
			string temp = data.substr(start, pos - start);//截取逗号前面字符
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}
//显示往届记录
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空或者不存在" << endl;
	}
	else {
		for (map<int, vector<string>>::iterator it = m_Record.begin();it != m_Record.end();++it) {
			cout << "第" << it->first << "届"
				<< "冠军编号：" << it->second[0] << "  得分：" << it->second[1] << " "
				<< "亚军编号：" << it->second[2] << "  得分：" << it->second[3] << " "
				<< "季军编号：" << it->second[4] << "  得分：" << it->second[5] << endl;
		}
	}
	system("pause");
	system, ("cls");
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
	//将记录的容器清空
	this->m_Record.clear();
}
//清空记录
void SpeechManager:: clearRecord() {
	cout << "是否确定清空记录?" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化容器和属性
		this->initSpeech();
		//创建12名选手
		this->createSpeaker();
		//加载往届记录
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}