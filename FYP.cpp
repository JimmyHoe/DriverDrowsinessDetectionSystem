#include<stdio.h>
#include<math.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<opencv\cvaux.h>
#include<opencv2\objdetect\objdetect.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<vector>
#include<Windows.h>
#include <mmsystem.h>  
#pragma comment(lib, "WINMM.LIB")  

using namespace cv;
using namespace std;

CascadeClassifier face_cascade, Left_eye_cascade, Right_eye_cascade;

vector<Mat> colors;
Mat frame2;
Mat frame, Gray_frame, LeftEyeROI, LeftEyeROI2, RightEyeROI, RightEyeROI2;
Mat LeftEyeGray, RightEyeGray;
Mat LeftEyeGray2, RightEyeGray2;
Rect LeftEyeRect = Rect(0,0,0,0);
Rect LeftEyeRect2 = Rect(0,0,0,0);
int LeftEyewidth=0,LeftEyeheight=0;
int LeftEyePositionX=0,LeftEyePositionY=0;
int LeftEyewidth2=0,LeftEyeheight2=0;
int LeftEyePositionX2=0,LeftEyePositionY2=0;
Rect RightEyeRect = Rect(0,0,0,0);
Rect RightEyeRect2 = Rect(0,0,0,0);
int RightEyewidth=0,RightEyeheight=0;
vector<Rect> face, Left_eye, Right_eye;
Rect faceRect; 
Mat faceROI;
int detected = 0;
int length = 0;
int length2 = 0;
int length3 = -100;
int length4 = 0;
int length5 = 0;
int length6 = -100;
int Rows_max = 0;
int Rows_min = 0;

string intToString(double t1)//convert the double detection seconds number into string
{
	stringstream s1;
	s1 << t1;
	return s1.str();
}

Point templateMatching(Mat Orig, Mat temp, Point matchLoc)//template matching function
{
	cvtColor(temp,temp,CV_BGR2GRAY);
	Mat result;
	int result_cols =  Orig.cols - temp.cols + 1;
	int result_rows = Orig.rows - temp.rows + 1;

	result.create( result_cols, result_rows, CV_32FC1 );

	matchTemplate( Orig, temp, result, CV_TM_SQDIFF_NORMED );
	normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	matchLoc = minLoc;
	return matchLoc;
}

int main()
{
	if(!face_cascade.load("haarcascade_frontalface_alt.xml"))//load the xml file
	{
		cout<<"can't read the xml";
		return 1;
	}

	if(!Left_eye_cascade.load("Closed_Eye.xml"))//load the xml file
	{
		cout<<"can't read the xml";
		return 1;
	}

	if(!Right_eye_cascade.load("Closed_Eye.xml"))//load the xml file
	{
		cout<<"can't read the xml";
		return 1;
	}


	VideoCapture cap(0);//open the webcam device, 0 for automatic searching the device, 1 for external device
	if(!cap.isOpened())//check whether can open the webcam
	{
		cout<<"can't open the webcam\n";
		return 0;
	}

	long frameToStart = 1;
	int frameToStop = 100;
	long currentFrame = frameToStart;

	//set the webcam resolution into 320*240
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	while(1)
	{
		cap>>frame;//store the capture video into frame
		if(!cap.read(frame))
		{
			cout<<"can't read the frame\n";
			break;
		}
		flip(frame,frame,1);//rotate the reverse capture frame

		putText(frame,"frame:"+intToString(currentFrame),cvPoint(0,240),2,1,Scalar(0,255,0));

		split(frame, colors);
		equalizeHist(colors[0], colors[0]);
		equalizeHist(colors[1], colors[1]);
		equalizeHist(colors[2], colors[2]);
		merge(colors, frame2);

		cvtColor(frame2,Gray_frame,CV_BGR2GRAY);//convert the frame into gray frame
		//equalizeHist(Gray_frame,Gray_frame);

		if(length3<-20||length3>20||length6<-20||length6>20)
		{
			face_cascade.detectMultiScale(Gray_frame, face, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));//detected the face
			if(!face.empty())
			{
				Point coordinate1(int(face[0].x), int(face[0].y));
				Point coordinate2(int(face[0].x+face[0].width/2), int(face[0].y+face[0].height/1.8));
				rectangle(frame, coordinate1, coordinate2, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for left part of face
				faceRect = Rect(coordinate1.x,coordinate1.y,(coordinate2.x-coordinate1.x),(coordinate2.y-coordinate1.y));
				faceROI = frame2(faceRect);
				imwrite("face.jpg",faceROI);//create the template image

				Point coordinate3(int(face[0].x+face[0].width/2), int(face[0].y));
				Point coordinate4(int(face[0].x+face[0].width), int(face[0].y+face[0].height/1.8));
				rectangle(frame, coordinate3, coordinate4, cvScalar(255, 255, 0), 2, 8, 0);//rectangle for right part of face
				Rect faceRect2 = Rect(coordinate3.x,coordinate3.y,(coordinate4.x-coordinate3.x),(coordinate4.y-coordinate3.y));
				Mat faceROI2 = frame2(faceRect2);
				imwrite("face2.jpg",faceROI2);//create the template image

				length3=0;
				length6=0;
			}
		}
		else
		{
			Mat templ;
			Point matchloc;
			templ = imread("face.jpg",1);//store the img into templ
			if(templ.empty())
			{
				cout<<"error1\n";
				return -1;
			} 
			matchloc = templateMatching(Gray_frame,templ,matchloc);//call the template matching function
			rectangle( frame, matchloc, Point( matchloc.x + templ.cols , matchloc.y + templ.rows ), cvScalar(255,0,0), 2, 8, 0 );
			Rect faceRect3 = Rect( matchloc.x, matchloc.y, templ.cols, templ.rows);
			Mat faceROI3 = frame2(faceRect3);
			imwrite("face.jpg",faceROI3);

			Mat templ2;
			Point matchloc2;
			templ2 = imread("face2.jpg",1);//store the img into templ2
			if(templ2.empty())
			{
				cout<<"error1\n";
				return -1; 
			}
			matchloc2 = templateMatching(Gray_frame,templ2,matchloc2);//call the template matching function
			rectangle( frame, matchloc2, Point( matchloc2.x + templ2.cols , matchloc2.y + templ2.rows ), cvScalar(255,0,0), 2, 8, 0 );
			Rect faceRect4 = Rect( matchloc2.x, matchloc2.y, templ2.cols, templ2.rows);
			Mat faceROI4 = frame2(faceRect4);
			imwrite("face2.jpg",faceROI4);

			//Point line1(int(matchloc.x),int(matchloc.y));
			//Point line2(int(matchloc2.x+templ2.cols),int(matchloc2.y));
			//Point line3(int(matchloc.x),int(matchloc.y+templ.rows));
			//Point line4(int(matchloc2.x+templ2.cols),int(matchloc2.y+templ2.rows));
			//line(frame,line1,line2,cvScalar(255,255,0), 2, 8, 0);
			//line(frame,line3,line4,cvScalar(255,255,0), 2, 8, 0);
			//line(frame,line1,line3,cvScalar(255,255,0), 2, 8, 0);
			//line(frame,line2,line4,cvScalar(255,255,0), 2, 8, 0);

			cvtColor(faceROI3, LeftEyeGray, CV_BGR2GRAY);
			Left_eye_cascade.detectMultiScale(LeftEyeGray, Left_eye, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
			for(int j=0;j<Left_eye.size();j++)
			{
				Point coordinate3(int(Left_eye[j].x), int(Left_eye[j].y));//set the coordinate1 x and y for drawing the rectangle on detected object
				Point coordinate4(int(Left_eye[j].x+Left_eye[j].width), int(Left_eye[j].y+Left_eye[j].height));
				rectangle(faceROI3, coordinate3, coordinate4, cvScalar(153, 51, 255), 2, 8, 0);//rectangle for left closed eye
			}

			cvtColor(faceROI4, RightEyeGray, CV_BGR2GRAY);
			Right_eye_cascade.detectMultiScale(RightEyeGray, Right_eye, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(0,0));
			for(int k=0;k<Right_eye.size();k++)
			{
				Point coordinate5(int(Right_eye[k].x), int(Right_eye[k].y));//set the coordinate1 x and y for drawing the rectangle on detected object
				Point coordinate6(int(Right_eye[k].x+Right_eye[k].width), int(Right_eye[k].y+Right_eye[k].height));
				rectangle(faceROI4, coordinate5, coordinate6, cvScalar(153, 51, 255), 2, 8, 0);//rectangle for right closed eye
			}

			//calculated the time of closed eye detection
			clock_t Start;
			if(Left_eye.empty()&&Right_eye.empty())
			{  
				Start = clock();
				putText(frame,"Eye Open",cvPoint(0,30),2,1,Scalar(0,255,0));
				mciSendString(TEXT("close MySong"), NULL, 0, NULL);//close the alert alam
			}
			else if(!Left_eye.empty()||!Right_eye.empty())//if eye is closed
			{  
				double FINDTIME =((double) clock() - Start ) / CLOCKS_PER_SEC;//closed eye time
				putText(frame,"Eye Close",cvPoint(0,30),2,1,Scalar(0,255,0));
				putText(frame,intToString(FINDTIME),cvPoint(0,60),2,1,Scalar(0,255,0));//display the closed eye time on screen
				if(FINDTIME>1.5)//if closed eye time over 1.5 seconds
				{
					putText(frame,"Warning",cvPoint(400,30),2,1,Scalar(0,255,0));
					if(!Left_eye.empty()||!Right_eye.empty())
					{
						//play the sound the alert the driver if found he/she are closed the eye more than 2 seconds
						mciSendString(TEXT("open AlertAlam.wav alias mysong"), NULL, 0,NULL);  
						mciSendString(TEXT("play MySong"), NULL, 0, NULL);
					}
				}
				FINDTIME = 0.0;//reset back the time to 0.0
			}

			//the distance between the left part and right part of face
			length = int(matchloc.x+templ.cols);
			length2 = int(matchloc2.x);
			length3 = length2-length;

			length4 = int(matchloc.y);
			length5 = int(matchloc2.y);
			length6 = length5-length4;

			//Rows_max = int(templ.rows/2);
			//Rows_min = -Rows_max;

			//cout<<"X "<<length3<<"\n";
			//cout<<"Y "<<length6<<"\n";
		}
		imshow("DriverDrowinessDetection", frame);
		imshow("DriverDrowinessDetection2", Gray_frame);

		stringstream str;
		str<<"Demo"<<currentFrame<<".jpg";
		imwrite(str.str(), frame);

		if(waitKey(30)>=0/*||currentFrame>=frameToStop*/)
			break;
		currentFrame++;
	}
	return 0;
}
