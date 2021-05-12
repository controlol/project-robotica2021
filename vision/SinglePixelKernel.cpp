#include"SinglePixelKernel.hpp"

void SinglePixelKernel::RemoveSinglePixels(uchar *picture,  int width, int height){
    int result[width*height];
    OverlayKernel2(picture, result, width, height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(result[i*width+j]==0 )
            picture[i*width+j]=0;
        }
        
    }
}

SinglePixelKernel::SinglePixelKernel(/* args */){
    signed char temp[3][3]={1,1,1,
                   1,0,1,
                   1,1,1};
    kernel.resize(3, std::vector<signed char>(3));
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      kernel[i][j] = temp[i][j];
    }
  }
}
SinglePixelKernel::~SinglePixelKernel(){

}