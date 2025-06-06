/*
本程序将input.txt 内部的数据按ASCII码形式读入,倒序写入output.txt 
*/ 
#include<stdio.h>
#include<stdlib.h>//exit函数需要的函数库
#define N 10
main()
{
	//注意：input.txt需在本程序相同目录下 
	FILE *fpw,*fpr;  //定义一个用来写的文件指针fpw和一个读文件的指针fpr
	int array[N];//定义整型数组array用来存放将要写入文件和从文件读出的数据

	if((fpr=fopen("input.txt","r"))==NULL)   
        //使用fopen函数打开文件input.txt,参数r表示以只读的方式打开
		//使用两个\\的原因请到网上查找
	{
		printf("The file named input.txt cannot be opened！\n");    //若fpr为空，则输出该文件不能打开的信息
		exit(1);//如果不能打开数据，直接终止程序
		//exit()用来关闭所有打开的文件并返回操作系统，参数为0时表示正常返回，为1时表示出错返回
	}   
	int i=0;
	while(!feof(fpr))  
		//循环从input.txt文件中读出数据到数组array，
		//直到fpr指针指向空值（feof()函数判断文件是否结束）
		
	{
		//fscanf的使用方法和scanf基本相同
		//但是前面有个参数是已经打开的文件指针		
		fscanf(fpr,"%d",&array[i]);
		i++;
	}
  //打开的文件必须关闭，否则下次打开会有问题
   fclose(fpr);  
   
   //建立一个新的数据文件，把数组中的数据,倒着写入文件
	//这次数据文件以写的方式打开
	if((fpw=fopen("output.txt","w"))==NULL) 
	{
		//若fpw为空，表示不能创建该文件，也许是文件夹不存在
		//则输出该文件不能打开的信息
		printf(" The file named output.txt cannot be opened！\n");    
		//exit()用来关闭所有打开的文件并返回操作系统，参数为0时表示正常返回，为1时表示出错返回
		exit(1);                                                    
	}   
	
	for(i=N-1;i>=0;i--)
		//fprintf和printf用法差不多，区别是第一个参数为文件指针
		fprintf(fpw,"%d ",array[i]);     
	    //循环输出数组array到一个新的文件

  	printf(" The file named output.txt has been written！\n");                      
	fclose(fpw); 

	//关闭文件
	//运行完之后，用“记事本”打开当前目录下的output.txt 看下，是不是倒序的数字
}
