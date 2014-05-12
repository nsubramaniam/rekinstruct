// ReKinStruct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <sstream> 
 
#include <stdio.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/visualization/cloud_viewer.h>

#define MAX_COUNT (20)
#define WAIT_TIME (1)

void wait(unsigned int seconds)
{
	clock_t timeToWait = clock () + seconds * CLOCKS_PER_SEC ;
	while (clock() < timeToWait);
}

const std::string out = "CandleDataset_";

using namespace std; 

class SimpleOpenNIViewer 
{ 
public: 
    SimpleOpenNIViewer () : viewer ("PCL Viewer") 
    { 
                frames_saved = 0; 
                save_one = false; 
    } 

    void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud) 
    { 
                if (!viewer.wasStopped()) { 
                        viewer.showCloud (cloud); 

                        if( save_one ) { 
                                save_one = false; 
                                char out_temp[255]; 
								sprintf(out_temp,"%s%d.pcd",out.c_str(),frames_saved);
								printf("Output = %s\n",out_temp);
                                pcl::io::savePCDFileBinary( out_temp, *cloud ); 
                        } 
                } 
    } 
	  
    void run (string deviceID) 
    { 
				cout << "Device ID : " << deviceID << endl;
                pcl::Grabber* interface = new pcl::OpenNIGrabber(deviceID); 

                boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = 
                        boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1); 

                interface->registerCallback (f); 

                interface->start (); 

                char c; 

                while (!viewer.wasStopped()) 
                { 
                        wait (WAIT_TIME); 
						
                        //c = getchar(); 
                        //if( c == 's' ) { 
                                cout << "Saving frame " << frames_saved << ".\n"; 
                                frames_saved++; 
                                save_one = true; 
                        //} 
                } 

                interface->stop (); 
        } 

        pcl::visualization::CloudViewer viewer; 

        private: 
                int frames_saved; 
                bool save_one; 

}; 

int main () 
{ 
    SimpleOpenNIViewer v1; 
	v1.run ("#1"); 

	return 0; 
} 
