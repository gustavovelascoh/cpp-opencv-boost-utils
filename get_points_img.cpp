#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/version.hpp>

//#include <iostream>
#include <stdio.h>
#include <string>
#include <list>

using namespace std;
using namespace cv;
using namespace boost::filesystem;
namespace fs = boost::filesystem;

Mat img, img_pts;
vector<Point>  trainedPoints;

const string winName = "points";

static void on_mouse( int event, int x, int y, int /*flags*/, void* );
int print_help();


int main(int argc, char** argv) {

	//int i=0;
	string output_file;

	print_help();

	if(argc < 2)
		return 0;

	if (argc > 3)
	{
		output_file = string(argv[3]) + argv[2];
	}
	else
	{
		output_file = argv[2];
	}

	fs::ofstream file(output_file);


	cout << "Output file: " << output_file.c_str() << endl;

	img = imread(argv[1]);
	img.copyTo(img_pts);
	imshow(winName, img_pts);

	setMouseCallback( "points", on_mouse );



	waitKey(0);
	cout << "Selected points: " << endl;
	for( size_t i = 0; i < trainedPoints.size(); i++ )
	{
		cout << trainedPoints[i].x << " " << trainedPoints[i].y << endl;
		file << trainedPoints[i].x << " " << trainedPoints[i].y << endl;
	}

	file.close();
	if ( !exists( output_file ) )
		std::cout << "Something is rotten in " << output_file << endl;

	return 0;
}

static void on_mouse( int event, int x, int y, int /*flags*/, void* )
{
    if( img_pts.empty() )
        return;

    int updateFlag = 0;

    if( event == EVENT_LBUTTONUP )
    {
        trainedPoints.push_back( Point(x,y) );
        updateFlag = true;
    }

    if( event == EVENT_RBUTTONUP )
	{
		trainedPoints.clear();
		updateFlag = true;
		img.copyTo(img_pts);
	}

    //draw
    if( updateFlag )
    {
        if (trainedPoints.size() == 1)
        {
        	circle( img_pts, trainedPoints[0], 5, Scalar(255,20,20) );
        }
        else if (trainedPoints.size() > 1)
        {
        	img.copyTo(img_pts);
        	for( size_t i = 0; i < trainedPoints.size() - 1; i++ )
			{
				line(img_pts, trainedPoints[i], trainedPoints[i+1], Scalar(255,20,20), 1);
			}
        	line(img_pts, trainedPoints[trainedPoints.size() - 1], trainedPoints[0], Scalar(255,20,20), 1);
        }

        // draw points
        for( size_t i = 0; i < trainedPoints.size(); i++ )
        {
        	circle( img_pts, trainedPoints[i], 5, Scalar(255,20,20) );
        }

        imshow( winName, img_pts );
   }
}

int print_help()
{
	cout << "SYNTAX:" << endl;
	cout << "" << endl;
	cout << "get_points_img input_img output_file [path]" << endl;
	cout << "" << endl;
	cout << "input_img: \tImage to load" << endl;
	cout << "output file: \tFile for save selected points" << endl;
	cout << "path: \t optional path for file" << endl;
	cout << "" << endl;
	cout << "USAGE:" << endl;
	cout << "" << endl;
	cout << "After the image is load use left-click to add points," << endl;
	cout << "right-click to reset and press any key to save selected" << endl;
	cout << "point to file" << endl;

	return 0;
}
