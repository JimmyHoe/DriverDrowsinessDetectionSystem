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
//#include<mmsystem.h>
//#pragma comment(lib,"winmm.lib")
//
//using namespace cv;
//using namespace std;
//
//void templateMatching(Mat, Mat);
//void HoughCircles(Mat);
//
//CascadeClassifier face_cascade, Left_eye_cascade, Right_eye_cascade, Left_open_cascade, Right_open_cascade;
//
//bool music = false;
//
//int input = 0;
//clock_t start;
//clock_t End;
//double elapsed;
//Mat canny;
//Rect eye_size = Rect(0,0,0,0);
//Mat frame, Gray_frame, LeftEyeROI, LeftEyeROI2, LeftEyeHSV, LeftEyeThresholded, RightEyeROI, RightEyeROI2;
//Mat LeftEyeGray, RightEyeGray;
//Mat LeftEyeGray2, RightEyeGray2;
//Rect Face_Area = Rect(0,0,0,0);
//Rect Safe = Rect(0,0,0,0);
//Rect Warning = Rect(0,0,0,0);
//Rect Dangerous = Rect(0,0,0,0);
//Rect LeftEyeRect = Rect(0,0,0,0);
//Rect LeftEyeRect2 = Rect(0,0,0,0);
//int LeftEyewidth=0,LeftEyeheight=0;
//int LeftEyePositionX=0,LeftEyePositionY=0;
//int LeftEyewidth2=0,LeftEyeheight2=0;
//int LeftEyePositionX2=0,LeftEyePositionY2=0;
//Rect RightEyeRect = Rect(0,0,0,0);
//Rect RightEyeRect2 = Rect(0,0,0,0);
//int RightEyewidth=0,RightEyeheight=0;
//int RightEyePositionX=0,RightEyePositionY=0;
//vector<Rect> face, Left_eye, Right_eye, Left_open_eye, Right_open_eye;
//
//string intToString(double number)
//{
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}
//
//Point templateMatching(Mat Orig, Mat temp, Point matchLoc)
//{
//	cvtColor(temp,temp,CV_BGR2GRAY);
//	Mat result;
//	int result_cols =  Orig.cols - temp.cols + 1;
//	int result_rows = Orig.rows - temp.rows + 1;
//
//	result.create( result_cols, result_rows, CV_32FC1 );
//
//	matchTemplate( Orig, temp, result, CV_TM_SQDIFF_NORMED );
//	normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
//	double minVal; double maxVal; Point minLoc; Point maxLoc;
//	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
//	matchLoc = minLoc;
//	return matchLoc;
//}
//
//void renewLeft()
//{
//	face_cascade.detectMultiScale(Gray_frame, face, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
//	if(!face.empty())
//	{
//		for(int i=0;i<face.size();i++)
//		{
//			//find left eye Area coordinate
//			Point coordinate3(int(face[i].x+face[i].width/2), int(face[i].y+face[i].height/2));
//			Point coordinate4(int(face[i].x*1.5), int(coordinate3.y/1.5));
//			rectangle(frame, coordinate3, coordinate4, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for right eye
//
//			//crop the left eye area into another new frame
//			LeftEyePositionX = int(coordinate4.x);
//			LeftEyePositionY = int(coordinate4.y);
//			LeftEyewidth = int(coordinate3.x-coordinate4.x);
//			LeftEyeheight = int(coordinate3.y-coordinate4.y);
//
//			LeftEyeRect = Rect(LeftEyePositionX,LeftEyePositionY,LeftEyewidth,LeftEyeheight);
//			LeftEyeROI = frame(LeftEyeRect);
//			cvtColor(LeftEyeROI, LeftEyeGray, CV_BGR2GRAY);
//			equalizeHist(LeftEyeGray,LeftEyeGray);
//		}
//	}
//}
//
//int main()
//{
//	if(!face_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
//	{
//		cout<<"can't read the xml";
//		return 1;
//	}
//
//	if(!Left_eye_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_mcs_lefteye.xml"))
//	{
//		cout<<"can't read the xml";
//		return 1;
//	}
//
//	if(!Right_eye_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_mcs_righteye.xml"))
//	{
//		cout<<"can't read the xml";
//		return 1;
//	}
//
//	if(!Left_open_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\visionary_EYES_01_LBP_5k_7k_30x60.xml"))
//	{
//		cout<<"can't read the xml";
//		return 1;
//	}
//
//	if(!Right_open_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\visionary_EYES_01_LBP_5k_7k_30x60.xml"))
//	{
//		cout<<"can't read the xml";
//		return 1;
//	}
//
//	VideoCapture cap(0);//open the internal webcam device
//	if(!cap.isOpened())
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
//		cvtColor(frame,Gray_frame,CV_BGR2GRAY);
//		equalizeHist(Gray_frame,Gray_frame);
//
//		if(LeftEyeRect2.width==0&&RightEyeRect2.width==0)
//		{
//			face_cascade.detectMultiScale(Gray_frame, face, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
//		
//			if(!face.empty())
//			{
//				for(int i=0;i<face.size();i++)
//				{
//					//find face Area coordinate
//					Point coordinate1(int(face[i].x), int(face[i].y));//set the coordinate1 x and y for drawing the rectangle on detected object
//					Point coordinate2(int(face[i].x+face[i].width), int(face[i].y+face[i].height));
//					//rectangle(frame, coordinate1, coordinate2, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for face
//
//					//find left eye Area coordinate
//					Point coordinate3(int(face[i].x+face[i].width/2), int(face[i].y+face[i].height/2));
//					Point coordinate4(int(face[i].x*1.5), int(coordinate3.y/1.5));
//					//rectangle(frame, coordinate3, coordinate4, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for right eye
//
//					//find right eye Area coordinate
//					Point coordinate5(int(face[i].x+face[i].width), int(coordinate3.y/1.5));
//					//rectangle(frame, coordinate3, coordinate5, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for left eye
//
//					//crop the left eye area into another new frame
//					LeftEyePositionX = int(coordinate4.x);
//					LeftEyePositionY = int(coordinate4.y);
//					LeftEyewidth = int(coordinate3.x-coordinate4.x);
//					LeftEyeheight = int(coordinate3.y-coordinate4.y);
//
//					LeftEyeRect = Rect(LeftEyePositionX,LeftEyePositionY,LeftEyewidth,LeftEyeheight);
//					LeftEyeROI = frame(LeftEyeRect);
//					cvtColor(LeftEyeROI, LeftEyeGray, CV_BGR2GRAY);
//					equalizeHist(LeftEyeGray,LeftEyeGray);
//					Left_eye_cascade.detectMultiScale(LeftEyeGray, Left_eye, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
//
//					if(!Left_eye.empty())
//					{
//						LeftEyeRect2 = Rect(Left_eye[0].x,Left_eye[0].y,Left_eye[0].width,Left_eye[0].height);
//						LeftEyeROI2 = LeftEyeROI(LeftEyeRect2);
//						imwrite("Left_eye.jpg",LeftEyeROI2);
//					}
//				
//					//crop the right eye area into another new frame
//					RightEyePositionX = int(coordinate3.x);
//					RightEyePositionY = int(coordinate5.y);
//					RightEyewidth = LeftEyewidth;
//					RightEyeheight = LeftEyeheight;
//
//					RightEyeRect = Rect(RightEyePositionX,RightEyePositionY,RightEyewidth,RightEyeheight);
//					RightEyeROI = frame(RightEyeRect);
//					cvtColor(RightEyeROI, RightEyeGray, CV_BGR2GRAY);
//					equalizeHist(RightEyeGray,RightEyeGray);
//					Right_eye_cascade.detectMultiScale(RightEyeGray, Right_eye, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
//
//					if(!Right_eye.empty())
//					{
//						RightEyeRect2 = Rect(Right_eye[0].x,Right_eye[0].y,Right_eye[0].width,Right_eye[0].height);
//						RightEyeROI2 = RightEyeROI(RightEyeRect2);
//						imwrite("Right_eye.jpg",RightEyeROI2);
//					}
//				}
//			}
//		}
//		else
//		{
//			Mat templ;
//			Point matchloc;
//			templ = imread("Left_eye.jpg",1);
//			if(templ.empty())
//			{
//				cout<<"error1\n";
//				return -1;
//			}
//			matchloc = templateMatching(LeftEyeGray,templ,matchloc);
//			rectangle( LeftEyeROI, matchloc, Point( matchloc.x + templ.cols , matchloc.y + templ.rows ), cvScalar(255,0,0), 2, 8, 0 );
//			renewLeft();
//		}
//		imshow("DriverDrowinessDetection", frame);
//		if(waitKey(30)>=0)
//			break;
//	}
//	destroyWindow("DriverDrowinessDetection");
//
//	return 0;
//}
//
