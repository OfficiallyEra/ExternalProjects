#include "main.h"
#include "../global/global.h"
#include "../tool/tool.h"

using namespace std;
using namespace cv;

/*
    @author : OfficiallyEra
    Date : 28th of August 2024
    update : 0 time(s)
    FileId : cpp.main.01
*/

int main()
{
	int choice = 0;
	const int scale = 5;
	string path,WinTitle;


entryMain:
	cout << endl;
	SetConsoleTitle(L"Learning OpenCv");
	tool::clearScr();
	cout << "\n\n\n\t[1]Process Image\n\t[2]Process Video\n\t[3]Process Camera(Check Your Cam)\n\t[4]Start matrix Test(Will Crash if handler returns negative)\n\t[5]Start Edge Detect(beta) \n\n[#]Your Choice > ";
	cin >> choice;

	if (choice == 0)
	{
		cout << "[ERROR] -> No Input" << endl;
		tool::pauseScr();
		goto entryMain;
	}
	else if (choice > scale || choice < 0)
	{
		cout << "[ERROR] -> I cant take " << choice << " as input!";
		tool::pauseScr();
		goto entryMain;
	}
	else
	{
		if (choice == 1)
		{
			cout << "Enter image path : ";
			cin >> path;
			cout << "Enter Window Title [No Space] : ";
			cin >> WinTitle;

			load::image(path, WinTitle);
			tool::pauseScr();
			goto entryMain;
		}
		else if (choice == 2)
		{
			cout << "Enter video path : ";
			cin >> path;
			cout << "Enter Window Title [No Space] : ";
			cin >> WinTitle;

			load::video(path, WinTitle);
			tool::pauseScr();
			goto entryMain;
		}
		else if (choice == 3)
		{
			cout << "Enter Window Title [No Space] : ";
			cin >> WinTitle;

			load::cam(WinTitle);
			tool::clearScr();
			goto entryMain;
		}
		else if (choice == 4)
		{
			cout << "Enter Window Title [No Space] : ";
			cin >> WinTitle;

			load::edgeDetect(WinTitle);
			tool::pauseScr();
			goto entryMain;
		}
		else if (choice == 5)
		{
			cout << "Enter Window Title [No Space] : ";
			cin >> WinTitle;

			load::handDetect(WinTitle);
			tool::pauseScr();
			goto entryMain;
		}
	}

	return 0;
}
