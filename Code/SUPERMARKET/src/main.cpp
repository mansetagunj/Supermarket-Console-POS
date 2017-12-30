#include <iostream>
#include "CUserInterface.h"
#include "common_helper.h"

using namespace std;

int main(){

	system("Color F0");
	cout << "\n\t" << getDateString();
	UserInterface UI;


	UI.displayUI();

	//to hold the screen
	//int m;
	//cin>>m;
}