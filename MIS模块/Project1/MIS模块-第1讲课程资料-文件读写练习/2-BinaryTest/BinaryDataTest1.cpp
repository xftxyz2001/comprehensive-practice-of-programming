/*
�������Զ�������ʽ���������е�����д���ļ� "BinaryData.dat" 
*/
#include<stdio.h> 
#include<stdlib.h>
#define N 10
main()
{
	
	FILE *fpw;  //����һ������д���ļ�ָ��fpw
	int array[N]={10,9,8,7,6,5,4,3,2,1};//������������array������Ž�Ҫд���ļ�
	
	 //����һ���µ������ļ����������е�����,�Զ������ļ��ķ�ʽд���ļ� 
	//�����ļ���д�������ļ���wb��ʽ��
	if((fpw=fopen("BinaryData.dat","wb"))==NULL) 
	{
		//��fpwΪ�գ���ʾ���ܴ������ļ���Ҳ�����ļ��в����ڻ��ߴ������ˣ����ߴ���д������ 
		//��������ļ����ܴ򿪵���Ϣ
		printf(" The file named BinaryData.dat cannot be opened\n");    
		//exit()�����ر����д򿪵��ļ������ز���ϵͳ������Ϊ0ʱ��ʾ�������أ�Ϊ1ʱ��ʾ������
		exit(1);                                                    
	}   
	
	fprintf(fpw,"FJ");
	
	//���ļ���д�����������һ����д��һ��������������ݣ�����ѭ�� 
	
	fwrite(array,sizeof(int),N,fpw);   
	printf("The file named BinaryData.dat has been written!\n") ;
		                           
	fclose(fpw); 

	//�ر��ļ�


}
