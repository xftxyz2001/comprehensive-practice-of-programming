/*
������input.txt �ڲ������ݰ�ASCII����ʽ����,����д��output.txt 
*/ 
#include<stdio.h>
#include<stdlib.h>//exit������Ҫ�ĺ�����
#define N 10
main()
{
	//ע�⣺input.txt���ڱ�������ͬĿ¼�� 
	FILE *fpw,*fpr;  //����һ������д���ļ�ָ��fpw��һ�����ļ���ָ��fpr
	int array[N];//������������array������Ž�Ҫд���ļ��ʹ��ļ�����������

	if((fpr=fopen("input.txt","r"))==NULL)   
        //ʹ��fopen�������ļ�input.txt,����r��ʾ��ֻ���ķ�ʽ��
		//ʹ������\\��ԭ���뵽���ϲ���
	{
		printf("The file named input.txt cannot be opened��\n");    //��fprΪ�գ���������ļ����ܴ򿪵���Ϣ
		exit(1);//������ܴ����ݣ�ֱ����ֹ����
		//exit()�����ر����д򿪵��ļ������ز���ϵͳ������Ϊ0ʱ��ʾ�������أ�Ϊ1ʱ��ʾ������
	}   
	int i=0;
	while(!feof(fpr))  
		//ѭ����input.txt�ļ��ж������ݵ�����array��
		//ֱ��fprָ��ָ���ֵ��feof()�����ж��ļ��Ƿ������
		
	{
		//fscanf��ʹ�÷�����scanf������ͬ
		//����ǰ���и��������Ѿ��򿪵��ļ�ָ��		
		fscanf(fpr,"%d",&array[i]);
		i++;
	}
  //�򿪵��ļ�����رգ������´δ򿪻�������
   fclose(fpr);  
   
   //����һ���µ������ļ����������е�����,����д���ļ�
	//��������ļ���д�ķ�ʽ��
	if((fpw=fopen("output.txt","w"))==NULL) 
	{
		//��fpwΪ�գ���ʾ���ܴ������ļ���Ҳ�����ļ��в�����
		//��������ļ����ܴ򿪵���Ϣ
		printf(" The file named output.txt cannot be opened��\n");    
		//exit()�����ر����д򿪵��ļ������ز���ϵͳ������Ϊ0ʱ��ʾ�������أ�Ϊ1ʱ��ʾ������
		exit(1);                                                    
	}   
	
	for(i=N-1;i>=0;i--)
		//fprintf��printf�÷���࣬�����ǵ�һ������Ϊ�ļ�ָ��
		fprintf(fpw,"%d ",array[i]);     
	    //ѭ���������array��һ���µ��ļ�

  	printf(" The file named output.txt has been written��\n");                      
	fclose(fpw); 

	//�ر��ļ�
	//������֮���á����±����򿪵�ǰĿ¼�µ�output.txt ���£��ǲ��ǵ��������
}
