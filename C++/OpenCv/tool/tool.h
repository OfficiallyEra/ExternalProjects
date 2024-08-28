#pragma once
/*
    @author : OfficiallyEra
    Date : 28th of August 2024
    update : 0 time(s)
    FileId : h.tool.01
*/

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