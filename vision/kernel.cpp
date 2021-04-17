#include"Kernel.hpp"


Kernel::Kernel(/* args */)
{
}

Kernel::~Kernel()
{
}

void Kernel::OverlayKernel2(uchar *picture,int *result, int width, int height){
    std::cout << "overlay kernel 2" << std::endl;
    int tempi;
    int tempj;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tempi=row-1;
            tempj=col-1;
            if (tempi<0)
            {
                tempi=0;
            }
            if (tempj<0)
            {
                tempj=0;
            }
            if ( row == height)
            {
                tempi = height-1;
            }
            if(col == width)
            {
                tempj = width-1;
            }
            std::cout<<"width  height:  "<<width<<"  "<<height<<std::endl;
            std::cout << "getting result for pixel" << std::endl;
            //result[row*width+col]=result[row*width+col];
            std::cout<<"Original pixel: "<<(unsigned int)result[row*width+col]<<std::endl;
            int sumpixel = applyFilter2(tempi,tempj,height,width,picture);
            std::cout<<"Sum pixel: "<<sumpixel<<std::endl;
            result[row * width + col ] = sumpixel;
            std::cout << "gotResult" << std::endl;
            //return;
        }
    }
}

std::vector<std::vector<uchar>> Kernel::OverlayKernel(std::vector<std::vector<uchar>>  picture, int width, int height){
   std::cout<<"going to overlay kernel"<<std::endl;
   std::vector<std::vector<uchar>> result = picture;
   //result.resize(width,std::vector<uchar>(height));
   int tempi;
   int tempj;
   std::vector< std::vector<uchar> >::iterator row;
    std::vector<uchar>::iterator col;
    int i = 0;
    int j = 0;
   //for every row
   for (row=picture.begin();row!=picture.end(); row+=1) 
    {
        //and every column
        for (col=row->begin();col!=row->end(); col+=1) 
        {
            tempi=i-1;
            tempj=j-1;
            if (tempi<0)
            {
                tempi=0;
            }
            if (tempj<0)
            {
                tempj=0;
            }
            if ( row == picture.end())
            {
                tempi = height-1;
            }
            if(col == row->end())
            {
                tempj = width-1;
            }
            //std::cout<<" just something for the compiler"<<std::endl;
            std::cout<<"Getting result from this pixel: " <<i<<"  "<<j<<std::endl;
            result[i][j] = applyFilter(tempi,tempj,picture);
            //std::cout<<"one getting result from this pixel"<<std::endl;
            j=std::distance(row->begin(),col);
            std::cout<<"i   height  width   " << i<<"  "<<height<<"  "<< width<<std::endl;
        }
        i=std::distance(picture.begin(),row);
    }
    std::cout<<"done with overlay kernel"<<std::endl;
    return result;
}

int Kernel::applyFilter(int row, int col, std::vector<std::vector<uchar>> picture)
{
    double sum = 0;
    std::vector< std::vector<uchar> >::iterator temp;
    temp=picture.end()-1;
    int tempcol;
    int temprow = row;
    int thing;
    for (int i = 0; i < 3; i++)
    {
        temprow=row+i;
        tempcol=col;
        for (int j = 0; j < 3; j++)
        {
            
            tempcol=col+j;
            thing = std::distance(picture.begin(),temp);
            std::cout<<"Getting filter from : " <<temprow<<"  "<<tempcol<<"  "<< thing <<std::endl;
            sum+=picture[temprow][tempcol] * this->kernel[i][j];
        }
    }
    //col-=1;
    //row-=1;
    return sum;
    
}
int Kernel::applyFilter2(int row, int col,int height ,int width, uchar *picture)
{
    int sum = 0;
    int pixelkernel;
    int tempcol;
    int temprow = row;
    for (int i = 0; i < 3; i++)
    {
        temprow=row+i;
        tempcol=col;
        for (int j = 0; j < 3; j++)
        {
            tempcol=col+j;
            std::cout<<"pixel  kernel value : " <<temprow<<"  "<<tempcol<<"  "<< (unsigned int)this->kernel[i][j];
            std::cout<<"\npixel value: "<<(unsigned int)picture[temprow*width+tempcol]<<std::endl;
            pixelkernel=picture[temprow*width+tempcol] * this->kernel[i][j];
            std::cout<<"pixelvalue*kernel: "<<(unsigned int)pixelkernel<<std::endl;
            sum+=pixelkernel;
            
        }
    }
    return sum;
    
}


void Kernel::TurnKernel(bool turnCounterClockwise){
    std::vector<std::vector<signed char>> temp;
    temp.resize(3,std::vector<signed char>(3));
    int timesTurned = 0;
    if (turnCounterClockwise)
    {
        timesTurned=2;
    }
    
    while (timesTurned<3)
    {
        for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp[j][i] = kernel[i][j];
        }
    }
    turnCounterClockwise = false;
    timesTurned++;
    }
    
    
    kernel = temp;
}   