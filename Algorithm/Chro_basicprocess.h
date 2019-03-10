#ifndef BASICPROCESS_H_
#define BASICPROCESS_H_
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "bmp.h"
#include <math.h>
/**
 * <font color="#3f7f5f">位图图像基本处理函数  图像格式转换</font>
 */
int RGB2Gray(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;
    BYTE r,g,b,gray;

    //检查图像格式是否合法
    if(src->bitCount!=24)
    {
        printf("Error(RGB2Gray): the source image must be in RGB format.\n");
        return -1;
    }

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(RGB2Gray): can't create target image.\n");
        return -1;
    }

    //计算灰度数据
    for(i=0;i<src->height;i++)
    {
        n=0;
        for(j=0;j<src->width*3;j++,n++)
        {
            b=*(src->imageData+src->widthStep*(src->height-1-i)+j);
            j++;
            g=*(src->imageData+src->widthStep*(src->height-1-i)+j);
            j++;
            r=*(src->imageData+src->widthStep*(src->height-1-i)+j);
            gray=(r*19595 + g*38469 + b*7472) >> 16;
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+n)=gray;
        }
    }

    return 0;
}

/**
 * Gray2RGB
 *
 * 使用方法：
 *        bmp=(Bitmap*)malloc(sizeof(Bitmap));
 *        ret=ReadBitmap(path, bmp);
 *        dstbmp=(Bitmap*)malloc(sizeof(Bitmap));
 *        ret=Gray2RGB(bmp,dstbmp);
 */
int Gray2RGB(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;
    BYTE r;

    //检查图像格式是否合法
    if(src->bitCount!=8)
    {
        printf("Error(Gray2RGB): the source image must be in gray scale.\n");
        return -1;
    }

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,24);
    if(ret==-1)
    {
        printf("Error(Gray2RGB): can't create target image.\n");
        return -1;
    }

    //计算灰度数据
    for(i=0;i<src->height;i++)
    {
        n=0;
        for(j=0;j<src->width;j++,n++)
        {
            r=*(src->imageData+src->widthStep*(src->height-1-i)+j);
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+n)=r;
            n++;
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+n)=r;
            n++;
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+n)=r;
        }
    }

    return 0;
}

/**
 * Gray2BW 图像二值化
 *
 * 使用方法：
 *        bmp=(Bitmap*)malloc(sizeof(Bitmap));
 *        ret=ReadBitmap(path, bmp);
 *        dstbmp=(Bitmap*)malloc(sizeof(Bitmap));
 *        ret=Gray2BW(bmp,dstbmp);
 */
int Gray2BW(Bitmap* src, Bitmap* dst, int threshold)
{
    int ret;
    int n=0,i,j;
    BYTE r;

    //检查图像格式是否合法
    if(src->bitCount!=8)
    {
        printf("Error(Gray2BW): the source image must be in gray scale.\n");
        return -1;
    }

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(Gray2BW): can't create target image.\n");
        return -1;
    }

    //计算灰度数据
    for(i=0;i<src->height;i++)
    {
        for(j=0;j<src->width;j++,n++)
        {
            r=*(src->imageData+src->widthStep*(src->height-1-i)+j);
            if(r>=threshold)
            {
                n=255;
            }
            else
            {
                n=0;
            }
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=n;
        }
    }

    return 0;
}

/**
 *  rgb2hsv
 *  r,g,b values are from 0 to 1
 *  h = [0,360], s = [0,1], v = [0,1]
 *  if s == 0, then h = -1 (undefined)
 *  使用方法：
 *      rgb2hsv(0.2,0.3,0.3,&x,&y,&z);
 */
void rgb2hsv(float R, float G, float B, float *H, float *S, float* V)
{
    float min, max, delta,tmp;
    tmp = R<G?R:G;
    min = tmp<B?tmp:B;
    tmp = R>G?R:G;
    max = tmp>B?tmp:B;
    *V = max; // v

    delta = max - min;

    if( max != 0 )
      *S = delta / max; // s
    else
    {
       // r = g = b = 0 // s = 0, v is undefined
      *S = 0;
      *H = -1;
      return;
    }
    if( R == max )
        *H = ( G - B ) / delta; // between yellow & magenta
   else if( G == max )
        *H = 2 + ( B - R ) / delta; // between cyan & yellow
   else
       *H = 4 + ( R - G ) / delta; // between magenta & cyan

    (*H) *= 60; // degrees
    if( *H < 0 )
       (*H) += 360;
}


/**
 *  hsv2rgb
 *  r,g,b values are from 0 to 1
 *  h = [0,360], s = [0,1], v = [0,1]
 *  if s == 0, then h = -1 (undefined)
 *  使用方法：
 *       hsv2rgb(60,0.3,0.5,&x,&y,&z);
*/
void hsv2rgb(float H, float S, float V, float *R, float *G, float *B)
{
     int i;
    float f, p, q, t;

    if( S == 0 )
    {
        *R =*G = *B = V;
        return;
    }

    H /= 60; // sector 0 to 5
    i = floor( H );
    f = H - i; // factorial part of h
    p = V * ( 1 - S );
    q = V * ( 1 - S * f );
    t = V * ( 1 - S * ( 1 - f ) );

    switch( i )
    {
    case 0:
        *R = V;
        *G = t;
        *B = p;
       break;
    case 1:
       *R = q;
       *G = V;
       *B = p;
       break;
    case 2:
       *R = p;
       *G = V;
       *B = t;
       break;
    case 3:
       *R = p;
       *G = q;
       *B = V;
       break;
    case 4:
       *R = t;
       *G = p;
       *B = V;
       break;
    default: // case 5:
       *R = V;
       *G = p;
       *B = q;
       break;
    }
}



/**
 * 直方图均衡化
 * 返回 0正确 -1错误
 */
int HistEqualization(Bitmap* dstBmp, Bitmap* srcBmp)
{
    return 0;
}

/*
 * 中值滤波 
*/


int MedFilt(Bitmap* dstBmp, Bitmap* srcBmp)
{
    return 0;
}



//平滑去噪

int smooth(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;
    int sum;

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(Gray2BW): can't create target image.\n");
        return -1;
    }

    for(i=1;i<src->height-1;i++)
    {
        for(j=1;j<src->width-1;j++)
        {   
            sum = 0;//clear sum
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j+1);

            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j);// 该点
            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j+1);

            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j+1);

            *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=(sum/9);//赋值给目标


        }
    }

    return 0;
}




//膨胀

int pengzhang(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;
    int r;

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(Gray2BW): can't create target image.\n");
        return -1;
    }

    for(i=1;i<src->height-1;i++)
    {
        for(j=1;j<src->width-1;j++)
        {   
            r=*(src->imageData+src->widthStep*(src->height-1-i)+j);     
            if(r==0)
            {
            *(dst->imageData+dst->widthStep*(dst->height-1-i-1)+j-1)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i-1)+j)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i-1)+j+1)=0;

            *(dst->imageData+dst->widthStep*(dst->height-1-i)+j-1)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i)+j+1)=0;

            *(dst->imageData+dst->widthStep*(dst->height-1-i+1)+j-1)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i+1)+j)=0;
            *(dst->imageData+dst->widthStep*(dst->height-1-i+1)+j+1)=0;
            }
            else *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=r;
        }
    }

    return 0;
}







int fushi(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;
    int r,sum;

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(Gray2BW): can't create target image.\n");
        return -1;
    }

    for(i=1;i<src->height-1;i++)
    {
        for(j=1;j<src->width-1;j++)
        {   
            r=*(src->imageData+src->widthStep*(src->height-1-i)+j);     

            if(r==0)
            {
            sum = 0;//clear sum
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i-1)+j+1);

            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j);// 该点
            sum+=*(src->imageData+src->widthStep*(src->height-1-i)+j+1);

            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j-1);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j);
            sum+=*(src->imageData+src->widthStep*(src->height-1-i+1)+j+1);
            if(sum>=255){
                *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=255;}
            else {*(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=r;}
            }
            else *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=255;
        }
    }

    return 0;
}







int qufan(Bitmap* src, Bitmap* dst)
{
    int ret;
    int n=0,i,j;

    //为dst图像分配数据空间
    ret=CreateBitmap(dst,src->width,src->height,8);
    if(ret==-1)
    {
        printf("Error(Gray2BW): can't create target image.\n");
        return -1;
    }
    for(i=1;i<src->height-1;i++)
    {
        for(j=1;j<src->width-1;j++)
        {   

        *(dst->imageData+dst->widthStep*(dst->height-1-i)+j)=255-*(src->imageData+src->widthStep*(src->height-1-i)+j);
        }
    }

    return 0;
}

#endif /* BASICPROCESS_H_ */
