#include<bitset>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<filesystem>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iostream>
#include<iterator>
#include<locale>
#include<map>
#include<mutex>
#include<numeric>
#include<optional>
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main()
{
    CascadeClassifier cascade;
    cascade.load("./images/haarcascade_frontalface_alt.xml"); //正面顔情報が入っているカスケードファイル読み込み
    Mat img = imread("./images/sample.jpeg", IMREAD_UNCHANGED); //入力画像読み込み
    std::vector<Rect> faces; //輪郭情報を格納場所
    cascade.detectMultiScale(img, faces, 1.1, 3, 0, Size(20, 20)); //カスケードファイルに基づいて顔を検知する．検知した顔情報をベクトルfacesに格納

    for(int i = 0; i<faces.size(); i++) //検出した顔の個数"faces.size()"分ループを行う
    {
        rectangle(img, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 0, 255), 3, CV_AA); //検出した顔を赤色矩形で囲む
    }

    imshow("detect face", img);
    waitKey(0);
}