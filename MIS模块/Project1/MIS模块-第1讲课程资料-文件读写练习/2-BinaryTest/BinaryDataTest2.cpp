/*
������ "BinaryData.dat" �е����֣���ʾ����Ļ�� 
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 10
int main()
{
	
	FILE *fpr;  //����һ���������ļ���ָ��fpr

	//BinaryData.dat�ļ����ڵ�ǰĿ¼�� 
	if((fpr=fopen("BinaryData.dat","rb"))==NULL)   
        //ʹ��fopen�������ļ�����r��ʾ��ֻ�������Ƶķ�ʽ��
		
	{
		printf("the file which named BinaryData.dat cannot be opened\n");    //��fprΪ�գ���������ļ����ܴ򿪵���Ϣ
		exit(1);//������ܴ����ݣ�ֱ����ֹ����
		//exit()�����ر����д򿪵��ļ������ز���ϵͳ������Ϊ0ʱ��ʾ�������أ�Ϊ1ʱ��ʾ������
	}   

    //�ȶ����һ���ַ���
    char str[N];
    fscanf(fpr,"%s",str);
    //printf("%s\n",str); 
	if(strcmp(str,"FJ")!=0)
	{
		printf("the file is not the required format!\n");    //�������ļ���������֮ǰ����ĸ�ʽ 
		exit(1);//������ݸ�ʽ���ԣ�����Ķ�ȡ�취Ҳ�����ˣ�ֱ����ֹ����
		
	 } 
    //һ�ζ����������ݵĶ�������������ʹ��ѭ�� 
    int array[N];//ʹ��һ������
	
	fread(array,sizeof(int),N,fpr);
	
    //��Ļ�����N������
    printf("\n\n");		
    for(int i=0;i<N;i++)
        printf("%d\t",array[i]);
    printf("\n\n");

   //�򿪵��ļ�����رգ������´δ򿪻�������
   fclose(fpr);  
   system("pause");
  
   return 0; 
}
