#pragma once
#include "../global/global.h"

namespace tool
{
	void pauseScr();
	void clearScr();
}

namespace load
{
	void image(std::string path, std::string title);
	void video(std::string getpath, std::string title);
	void cam(std::string title);
	void edgeDetect(std::string title);
	void handDetect(std::string title);
}