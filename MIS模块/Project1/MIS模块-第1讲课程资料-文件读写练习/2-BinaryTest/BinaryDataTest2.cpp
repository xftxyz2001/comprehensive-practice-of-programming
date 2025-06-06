/*
本程序将 "BinaryData.dat" 中的数字，显示在屏幕上 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 10
int main()
{
	
	FILE *fpr;  //定义一个用来读文件的指针fpr

	//BinaryData.dat文件需在当前目录下 
	if((fpr=fopen("BinaryData.dat","rb"))==NULL)   
        //使用fopen函数打开文件参数r表示以只读二进制的方式打开
		
	{
		printf("the file which named BinaryData.dat cannot be opened\n");    //若fpr为空，则输出该文件不能打开的信息
		exit(1);//如果不能打开数据，直接终止程序
		//exit()用来关闭所有打开的文件并返回操作系统，参数为0时表示正常返回，为1时表示出错返回
	}   

    //先读入第一行字符串
    char str[N];
    fscanf(fpr,"%s",str);
    //printf("%s\n",str); 
	if(strcmp(str,"FJ")!=0)
	{
		printf("the file is not the required format!\n");    //该数据文件不是我们之前定义的格式 
		exit(1);//如果数据格式不对，下面的读取办法也不对了，直接终止程序
		
	 } 
    //一次读入所有数据的二进制流，无需使用循环 
    int array[N];//使用一个数组
	
	fread(array,sizeof(int),N,fpr);
	
    //屏幕上输出N个数字
    printf("\n\n");		
    for(int i=0;i<N;i++)
        printf("%d\t",array[i]);
    printf("\n\n");

   //打开的文件必须关闭，否则下次打开会有问题
   fclose(fpr);  
   system("pause");
  
   return 0; 
}
