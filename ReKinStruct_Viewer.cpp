#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

#define MAX_COUNT (2)
#define WAIT_TIME (1)
const char * out = "KinectFusion_";

void wait(unsigned int seconds)
{
	clock_t timeToWait = clock () + seconds * CLOCKS_PER_SEC ;
	while (clock() < timeToWait);
}

int main()
{
	char c;
	int count=1;
	char output[255];
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud1 (new pcl::PointCloud<pcl::PointXYZRGBA>);
	pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud2 (new pcl::PointCloud<pcl::PointXYZRGBA>);
	sprintf(output,"%s%d.pcd",out,count);
	count=(count%MAX_COUNT)+1;
	if (pcl::io::loadPCDFile<pcl::PointXYZRGBA> (output, *cloud1) == -1) //* load the file
	{
		PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
		return -1;
	}
	sprintf(output,"%s%d.pcd",out,count);
	count=(count%MAX_COUNT)+1;
	if (pcl::io::loadPCDFile<pcl::PointXYZRGBA> (output, *cloud2) == -1) //* load the file
			{
				PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
				return -1;
			}

	pcl::visualization::CloudViewer viewer("PCD viewer");
	viewer.showCloud(cloud1);
	while(1)
	{
		wait(WAIT_TIME);
		//cin >>c;
		cout << "Changing point clouds"<<endl;
		viewer.showCloud(cloud2);
		sprintf(output,"%s%d.pcd",out,count);
		count=(count%MAX_COUNT)+1;
		if (pcl::io::loadPCDFile<pcl::PointXYZRGBA> (output, *cloud1) == -1) //* load the file
		{
			PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
			return -1;
		}

		wait(WAIT_TIME);
		cin>>c;
		cout << "Changing point clouds"<<endl;
		viewer.showCloud(cloud1);
		sprintf(output,"%s%d.pcd",out,count);
		count=(count%MAX_COUNT)+1;
		if (pcl::io::loadPCDFile<pcl::PointXYZRGBA> (output, *cloud2) == -1) //* load the file
		{
			PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
			return -1;
		}
	}

	while(!viewer.wasStopped())
	{ 
	}
	 
	return 0;
}