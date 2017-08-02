
#include "App.h"

HANDLE App::hMutex = CreateMutex(NULL, FALSE, NULL);

App::App() : serverport(0) {
	memset(serverip, 0, sizeof(serverip));
}

App::~App() {
	delete chattingclient;
}

void App::start() {
	int result = 0;

	printStart();
	chattingclient = new ChattingClient(this->serverip, this->serverport);

	try { 
		result = chattingclient->run();
	} catch (ChatException e) {
		e.printError();
		return;
	}

	if (result == 0){
		printExit();
	} else {
		printError();
	}
}

void App::printStart() {
	char buf[16];
	int port;

	cout <<	"========< ä�� Ŭ���̾�Ʈ ���α׷� >========\n"
				"============================================\n"
				"====\t\t\t\t\t====\n"
				"====\tVersion : v1.0.0\t\t====\n"
				"====\t\t\t\t\t====\n"
				"====\tCreate By : ������������������\t====\n"
				"====\t\t\t\t\t====\n"
				"====\tEmail : lead788@gmail.com\t====\n"
				"====\t\t\t\t\t====\n"
				"============================================\n"
				"============================================\n";
	cout << "���� IP�ּ� => ";
	cin >> buf;
	cout << "���� Port��ȣ => ";
	cin >> port;

	sprintf(this->serverip, "%s", buf);
	this->serverport = port;
}

void App::printExit() {
	cout << "������ ������ ����ƽ��ϴ�." << endl;
}
void App::printError() {
	cout << "������ ������ ������ϴ�." << endl;
}