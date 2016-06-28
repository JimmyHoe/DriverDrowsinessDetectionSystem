//#include<stdio.h>
//#include<math.h>
//#include<opencv\cv.h>
//#include<opencv\highgui.h>
//#include<opencv\cvaux.h>
//#include<opencv2\objdetect\objdetect.hpp>
//#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
//#include<vector>
//#include<Windows.h>
//#include <mmsystem.h>  
//#pragma comment(lib, "WINMM.LIB")  
//
//using namespace cv;
//using namespace std;
//
//Mat frame2, Gray_frame2,Gray_frame3;
//Mat frame, Gray_frame, LeftEyeROI, LeftEyeROI2, RightEyeROI, RightEyeROI2;
//Mat LeftEyeGray, RightEyeGray;
//Mat LeftEyeGray2, RightEyeGray2;
//Rect LeftEyeRect = Rect(0,0,0,0);
//Rect LeftEyeRect2 = Rect(0,0,0,0);
//int LeftEyewidth=0,LeftEyeheight=0;
//int LeftEyePositionX=0,LeftEyePositionY=0;
//int LeftEyewidth2=0,LeftEyeheight2=0;
//int LeftEyePositionX2=0,LeftEyePositionY2=0;
//Rect RightEyeRect = Rect(0,0,0,0);
//Rect RightEyeRect2 = Rect(0,0,0,0);
//int RightEyewidth=0,RightEyeheight=0;
//vector<Rect> face, Left_eye, Right_eye;
//Rect faceRect; 
//Mat faceROI;
//int detected = 0;
//int length = 0;
//int length2 = 0;
//int length3 = -100;
//int length4 = 0;
//int length5 = 0;
//int length6 = -100;
//int Rows_max = 0;
//int Rows_min = 0;
//
//int main(int argc, char *argv[])
//{
//
//	VideoCapture cap(0);//open the webcam device, 0 for automatic searching the device, 1 for external device
//	if(!cap.isOpened())//check whether can open the webcam
//	{
//		cout<<"can't open the webcam\n";
//		return 0;
//	}
//
//	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
//	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
//
//	while(1)
//	{
//		cap>>frame;//store the capture video into frame
//		if(!cap.read(frame))
//		{
//			cout<<"can't read the frame\n";
//			break;
//		}
//		flip(frame,frame,1);//rotate the reverse capture frame
//		vector<Mat> colors;
//		split(frame, colors);
//		equalizeHist(colors[0], colors[0]);
//		equalizeHist(colors[1], colors[1]);
//		equalizeHist(colors[2], colors[2]);
//		merge(colors, frame2);
//
//		cvtColor(frame,Gray_frame,CV_BGR2GRAY);
//		cvtColor(frame2,Gray_frame2,CV_BGR2GRAY);
//		
//		equalizeHist(Gray_frame2,Gray_frame3);
//
//		imshow("dark", Gray_frame2);
//		imshow("brightness", Gray_frame3);
//
//		if(waitKey(30)>=0)
//			break;
//	}
//
//    return 0;
//}