/*
������input.txt �ڲ������ݰ�ASCII����ʽ���룬������Ļ����� 
*/ 
#include<stdio.h>
#include<stdlib.h>//exit������Ҫ�ĺ�����
#define N 10 //�����ļ������ݵĸ��� 
main()
{
	//ע�⣺input.txt���ڱ�������ͬĿ¼�� 
	FILE *fpr;  //����һ������д���ļ�ָ��fpw��һ�����ļ���ָ��fpr
	int array[N];//������������array������Ž�Ҫд���ļ��ʹ��ļ�����������

	if((fpr=fopen("input.txt","r"))==NULL)   
        //ʹ��fopen�������ļ�input.txt,����r��ʾ��ֻ���ķ�ʽ��
		//ʹ������\\��ԭ���뵽���ϲ���
	{
		printf("the file which  named input.txt cannot be opened��\n");    //��fprΪ�գ���������ļ����ܴ򿪵���Ϣ
		exit(1);//������ܴ����ݣ�ֱ����ֹ����
		//exit()�����ر����д򿪵��ļ������ز���ϵͳ������Ϊ0ʱ��ʾ�������أ�Ϊ1ʱ��ʾ������
	}   
	int i=0;
	while(!feof(fpr))  //�ļ����������ط�0ֵ���ļ�δ����������0ֵ 
		//ѭ����input.txt�ļ��ж������ݵ�����array��
		//ֱ��fprָ��ָ���ֵ��feof()�����ж��ļ��Ƿ������
		
	{
		//fscanf��ʹ�÷�����scanf������ͬ
		//����ǰ���и��������Ѿ��򿪵��ļ�ָ��		
		fscanf(fpr,"%d",&array[i]);
		i++;
	}
	
	//����Ļ�������N������ 
	printf("\n\n");
	for(i=0;i<N;i++)
        printf("%d\t",array[i]);
    printf("\n\n");

   //�򿪵��ļ�����رգ������´δ򿪻�������
   fclose(fpr); 
    
   system("pause"); 
 }
