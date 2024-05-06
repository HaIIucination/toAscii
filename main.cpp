#include <opencv2/opencv.hpp> 
#include <stdio.h> 
#include <fstream>

using namespace cv; 
std::ofstream file;

void gen_ascii(Mat image){
  file.open("result.txt");
  for(int r=0; r < image.rows ; r++)
  {
    for(int c=0 ; c < image.cols ; c++)
    {
      int intensity = static_cast<int>(image.at<uchar>(r,c));
      char out;

      if(intensity > 224)
        out = '@';
      else if(intensity < 224 && 192 < intensity)
        out = '0';
      else if(intensity < 192 && 160 < intensity)
        out = '#';
      else if(intensity < 160 && 128 < intensity)
        out = '&';
      else if(intensity < 128 && 96 < intensity)
        out = '/';
      else if(intensity < 96 && 64 < intensity)
        out = '=';
      else if(intensity < 64 && 32 < intensity)
        out = '-';
      else
        out = '\'';

     file << out << ' ';
    }
    file << '\n';
  }

}

int main() 
{ 
  Mat image,oimg; 
  std::cout << "Enter image path: ";
  std::string ImpPath;
  std::cin >> ImpPath;
  image = imread(ImpPath, 0); 
  int ro = image.rows;
  int cl = image.cols;
  int aro = ro/100;
  int acl = cl/100;
  while(ro>400 or cl>300)
  {
    ro-=aro;
    cl-=acl;

  }
  cv::Size targetSize(ro, cl);
  if (!image.data) { 
    printf("No image data \n"); 
    return -1; 
  }
  cv::resize(image, oimg, targetSize);
  gen_ascii(oimg);
  system("xdg-open result.txt");
  //system("start notepad output.txt"); For windows
  //system("open -a TextEdit output.txt"); For macOs

//  namedWindow("Display Image", WINDOW_AUTOSIZE); 
//  imshow("Display Image", oimg); 
//  waitKey(0); 
  return 0; 
}
