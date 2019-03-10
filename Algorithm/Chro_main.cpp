void main()
{
    Bitmap *bmp = (Bitmap *)malloc(sizeof(Bitmap));// build an empty bmp to put the img.空变量呈放图片
    Bitmap *dstBmp = (Bitmap *)malloc(sizeof(Bitmap));
    Bitmap *graybmp = (Bitmap *)malloc(sizeof(Bitmap));
    Bitmap *smoothbmp = (Bitmap *)malloc(sizeof(Bitmap));
    Bitmap *binbmp = (Bitmap *)malloc(sizeof(Bitmap));
    Bitmap *temp = (Bitmap *)malloc(sizeof(Bitmap));
    int ret;
    char *path ="C:\\Users\\Ali\\Desktop\\1.bmp";
    ret = ReadBitmap(path, bmp);//读取图片
    char *savePath ="C:\\Users\\Ali\\Desktop\\zuizhong.bmp";
    RGB2Gray(bmp,graybmp);//转换成灰度图
    smooth(graybmp,smoothbmp);
    Gray2BW(smoothbmp,binbmp,155);//二值化
    pengzhang(binbmp, dstBmp);  
    pengzhang(dstBmp, temp);
    fushi(temp,dstBmp);
    qufan(dstBmp,temp);
    /*BYTE *bitmap = temp->imageData;
    int width = temp->width;
    int height = temp->height;
    int *labelmap;
    ConnectedComponentLabeling(bitmap, width, height,labelmap); 有待调整 此处是调用本博客的另一篇文章
    二值图像统计连通区域*/
    SaveBitmap(savePath,temp);//保存图片    
}
