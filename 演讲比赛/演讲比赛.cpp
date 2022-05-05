#include"speechManager.h"
int main() {
	SpeechManager sm;
	while (true)
	{
		srand((unsigned)time(NULL));
		sm.show_Menu();
		int choice = 0;
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ" << endl;
		cin >> choice;
		switch(choice){
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:sm.exitSystem();
			break;
		default:system("cls");
			break;
		}
	}
	return 0;
}