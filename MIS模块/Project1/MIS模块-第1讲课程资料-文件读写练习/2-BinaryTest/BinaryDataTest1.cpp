/*
本程序以二进制形式，将数组中的数据写入文件 "BinaryData.dat" 
*/
#include<stdio.h> 
#include<stdlib.h>
#define N 10
main()
{
	
	FILE *fpw;  //定义一个用来写的文件指针fpw
	int array[N]={10,9,8,7,6,5,4,3,2,1};//定义整型数组array用来存放将要写入文件
	
	 //建立一个新的数据文件，把数组中的数据,以二进制文件的方式写入文件 
	//数据文件以写二进制文件的wb方式打开
	if((fpw=fopen("BinaryData.dat","wb"))==NULL) 
	{
		//若fpw为空，表示不能创建该文件，也许是文件夹不存在或者磁盘满了，或者磁盘写保护了 
		//则输出该文件不能打开的信息
		printf(" The file named BinaryData.dat cannot be opened\n");    
		//exit()用来关闭所有打开的文件并返回操作系统，参数为0时表示正常返回，为1时表示出错返回
		exit(1);                                                    
	}   
	
	fprintf(fpw,"FJ");
	
	//给文件中写入二进制流，一次性写入一个数组的所有数据，不用循环 
	
	fwrite(array,sizeof(int),N,fpw);   
	printf("The file named BinaryData.dat has been written!\n") ;
		                           
	fclose(fpw); 

	//关闭文件


}
