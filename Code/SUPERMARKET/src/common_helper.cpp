
#include "common_helper.h"
#include <fstream>
#include <string>
#include <map>
#include <iostream>

#include "CError.h"
#include "CProduct.h"

#include <ctime>

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;



const std::string getDateString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	localtime_s(&tstruct, &now);
	return std::string(std::to_string(tstruct.tm_mon+1)+"/"+ std::to_string(tstruct.tm_mday)+"/" + std::to_string(tstruct.tm_year+1900));
}

const std::string getTimeString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	localtime_s(&tstruct,&now);
	return std::string(std::to_string(tstruct.tm_hour) + ":" + std::to_string(tstruct.tm_min) + ":" + std::to_string(tstruct.tm_sec));
}

multimap<unsigned long, Product> getCart_FromFile(const char *inFileName) {

	multimap<unsigned long, Product> cartMap;
	Product prod;
	unsigned long custid;
	ifstream cartfile;
	cartfile.open(inFileName);


	if (cartfile && (cartfile.peek() != std::ifstream::traits_type::eof()))
	{
		while (!cartfile.eof())
		{
			cartfile >> prod >> custid;

			cartMap.insert(make_pair(custid, prod));
		}
		return cartMap;
	}
	else
	{
		if (!cartfile)
		{
			errClass err("File Cannot be Opened", 2);
			throw err;
		}
		else if (cartfile.peek() == std::ifstream::traits_type::eof())
		{
			cartfile.close();
			
		}
		return cartMap;
	}

}


bool checkName(string x)
{
	if (x.length()>2)
	{
		for (unsigned i = 0; i<x.length(); i++)
		{
			if (isalpha(x[i]))
			{
				continue;
			}
			else
				return 0;
		}
		return 1;
	}
	else
		return 0;

}
/*Function to check value for password*/
bool checkPass(string x)
{
	unsigned num = 0, alph = 0;
	if (x.length()>5)
	{
		for (unsigned i = 0; i<x.length(); i++)
		{
			if (isalpha(x[i]))
			{
				alph++;
				continue;
			}
			else if (isdigit(x[i]))
			{
				num++;
				continue;
			}
			else
				return 0;
		}
		if (num>0 && alph>0)
			return 1;
		else return 0;
	}
	else
		return 0;

}


istream& takePassword(istream &in, string s) {

	char ch;
	do {
		in.get(ch);
		s.push_back(ch);
		cout << '*';
	} while (ch != ' ' && ch != '\n');
	return in;


}

void set_stdinEcho(bool enable_echo = true)
{
#ifdef WIN32
	HANDLE h_stdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(h_stdin, &mode);

	if (!enable_echo)
		mode &= ~ENABLE_ECHO_INPUT;
	else
		mode |= ENABLE_ECHO_INPUT;

	SetConsoleMode(h_stdin, mode);

#else
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	if (!enable_echo)
		tty.c_lflag &= ~ECHO;
	else
		tty.c_lflag |= ECHO;

	(void)tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}