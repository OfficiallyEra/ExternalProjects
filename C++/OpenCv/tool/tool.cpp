#include "tool.h"
#include "../global/global.h"
#include "../src/main.h"
#include "../engine/engine.h"

using namespace std;
using namespace cv;

void tool::pauseScr()
{
	system("pause>nul");
}

void tool::clearScr()
{
	system("cls");
}

void load::image(std::string path, std::string title)
{
	std::string imgOne = path;
	Mat img = imread(imgOne);
	imshow(title, img);
	waitKey(0);
}

void load::video(std::string getpath, std::string title)
{
	std::string path = getpath;
	VideoCapture vCap(path);
	Mat img;

	while (1)
	{
		vCap.read(img);

		imshow(title, img);
		waitKey(10);
	}
}

void load::cam(std::string title)
{

	VideoCapture camCap(0);
	Mat img;

	if (!camCap.isOpened()) {
		cerr << "Error: Could not open camera." << endl;
	}
	else
	{
		while (1)
		{
			camCap.read(img);

			imshow(title, img);
			waitKey(1);
		}
	}
}

void load::edgeDetect(std::string title)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "Error: Could not open camera." << endl;
		tool::pauseScr();
	}
	else
	{


		while (true)
		{
			Mat frame;
			cap >> frame;

			if (frame.empty()) break;

			int fingerCount = start::engineEdgeDetect(frame);

			// Display the count on the frame
			putText(frame, "Matrix Value : " + to_string(fingerCount), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 255, 0), 2);

			// Show the frame with the count
			imshow("Camera Matrix", frame);

			if (waitKey(30) >= 0) break;
		}
	}
}

void load::handDetect(std::string title)
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "Error: Could not open camera." << endl;
		tool::pauseScr();
	}

	while (true) {
		Mat frame;
		cap >> frame;

		if (frame.empty()) break;

		start::engineDetectHand(frame);

		// Show the frame with the hand detection
		imshow("Hand Detection", frame);

		if (waitKey(30) >= 0) break;
	}
}