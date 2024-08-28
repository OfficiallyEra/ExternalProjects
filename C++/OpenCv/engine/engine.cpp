#include "../global/global.h"
#include"../tool/tool.h"
#include "engine.h"

using namespace std;
using namespace cv;

/*
    @author : OfficiallyEra
    Date : 28th of August 2024
    update : 0 time(s)
    FileId : cpp.engine.01
*/

int start::engineEdgeDetect(Mat frame) 
{
    Mat gray, blur, thresh;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // Convert the frame to grayscale
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Apply Gaussian Blur
    GaussianBlur(gray, blur, Size(15, 15), 0);

    // Apply thresholding to create a binary image
    threshold(blur, thresh, 60, 255, THRESH_BINARY_INV);

    // Find contours
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    if (contours.empty()) return 0;

    // Find the largest contour (assuming it is the matrix0)
    int maxContourIdx = -1;
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); i++) 
    {
        double area = contourArea(contours[i]);

        if (area > maxArea) 
        {
            maxArea = area;
            maxContourIdx = static_cast<int>(i); // Casting size_t to int
        }
    }

    // Convex hull and convexity defects
    vector<int> hull;
    vector<Vec4i> defects;
    if (maxContourIdx != -1) 
    {
        convexHull(contours[maxContourIdx], hull, false);
        convexityDefects(contours[maxContourIdx], hull, defects);

        int fingerCount = 0;
        for (size_t i = 0; i < defects.size(); i++) 
        {
            Vec4i defect = defects[i];
            Point start = contours[maxContourIdx][defect[0]];
            Point end = contours[maxContourIdx][defect[1]];
            Point farPoint = contours[maxContourIdx][defect[2]];
            float depth = static_cast<float>(defect[3]) / 256.0;

            // Filter defects with a reasonable depth to count matrix
            if (depth > 20 && norm(start - farPoint) > 20 && norm(end - farPoint) > 20) 
            {
                fingerCount++;
                circle(frame, farPoint, 5, Scalar(0, 0, 255), -1);  // Mark the defect point
            }
        }

        // Return the number of matrix (defects + 1)
        return fingerCount + 1;
    }

    return 0;
}

void start::engineDetectHand(Mat& frame) 
{
    Mat gray, blur, thresh;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    // Convert the frame to grayscale
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    // Apply Gaussian Blur
    GaussianBlur(gray, blur, Size(15, 15), 0);

    // Apply thresholding to create a binary image
    threshold(blur, thresh, 60, 255, THRESH_BINARY_INV);

    // Find contours
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    if (contours.empty()) return;

    // Find the largest contour (assuming it is the edge)
    int maxContourIdx = -1;
    double maxArea = 0;
    for (size_t i = 0; i < contours.size(); i++) 
    {
        double area = contourArea(contours[i]);
        if (area > maxArea) 
        {
            maxArea = area;
            maxContourIdx = static_cast<int>(i); // Casting size_t to int
        }
    }

    // Draw the contour or bounding box around the object
    if (maxContourIdx != -1) 
    {
        // Option 1: Draw the contour
        drawContours(frame, contours, maxContourIdx, Scalar(0, 255, 0), 2);

        // Option 2: Draw a bounding box around the object
        Rect boundingBox = boundingRect(contours[maxContourIdx]);
        rectangle(frame, boundingBox, Scalar(255, 0, 0), 2);
    }
}