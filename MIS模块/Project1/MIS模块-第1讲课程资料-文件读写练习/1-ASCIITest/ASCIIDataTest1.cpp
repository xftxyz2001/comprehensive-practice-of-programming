/*
本程序将input.txt 内部的数据按ASCII码形式读入，并在屏幕上输出 
*/ 
#include<stdio.h>
#include<stdlib.h>//exit函数需要的函数库
#define N 10 //数据文件里数据的个数 
main()
{
	//注意：input.txt需在本程序相同目录下 
	FILE *fpr;  //定义一个用来写的文件指针fpw和一个读文件的指针fpr
	int array[N];//定义整型数组array用来存放将要写入文件和从文件读出的数据

	if((fpr=fopen("input.txt","r"))==NULL)   
        //使用fopen函数打开文件input.txt,参数r表示以只读的方式打开
		//使用两个\\的原因请到网上查找
	{
		printf("the file which  named input.txt cannot be opened！\n");    //若fpr为空，则输出该文件不能打开的信息
		exit(1);//如果不能打开数据，直接终止程序
		//exit()用来关闭所有打开的文件并返回操作系统，参数为0时表示正常返回，为1时表示出错返回
	}   
	int i=0;
	while(!feof(fpr))  //文件结束：返回非0值；文件未结束：返回0值 
		//循环从input.txt文件中读出数据到数组array，
		//直到fpr指针指向空值（feof()函数判断文件是否结束）
		
	{
		//fscanf的使用方法和scanf基本相同
		//但是前面有个参数是已经打开的文件指针		
		fscanf(fpr,"%d",&array[i]);
		i++;
	}
	
	//在屏幕上输出这N个数字 
	printf("\n\n");
	for(i=0;i<N;i++)
        printf("%d\t",array[i]);
    printf("\n\n");

   //打开的文件必须关闭，否则下次打开会有问题
   fclose(fpr); 
    
   system("pause"); 
 }
