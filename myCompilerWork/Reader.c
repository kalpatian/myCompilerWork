#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_SIZE 512                     /*���鳤��*/  

char buf[MAX_LINE];
char f[MAX_LINE];	//��������ж����float�ͱ��� 
float fr[MAX_LINE] = {0.0};
char i[MAX_LINE];	//��������ж����int�ͱ��� 
int ir[MAX_LINE] = {0};
int fenhao[MAX_LINE] = {0};	//�ֺ�λ�� 
char computing[MAX_SIZE] = {'0'};
int take_fenhao = 0;
int answer_place;
int int_or_float;

int initial()
{
	int k = 0;
	for(k=0;k<MAX_LINE;k++)
	{
		buf[k] = '0';
	}
	return 0;
}
int insert_operand(float *operand , int * top_num ,float num)           /*����ѹ������ջ*/  
{
    (*top_num) ++;  
    operand[*top_num] = num;                    /*��������*/  
    
    return 0;                           /*�����˳�*/  
}  


int insert_oper (char * oper , int *top_oper , char ch)             /*������ѹ�����ջ*/  
{  
    (*top_oper)++;  
    oper[*top_oper] = ch;                       /*���������*/  
    return 0;                           /*�����˳�*/  
}  
     
int compare(char *oper , int *top_oper , char ch)                   /*�Ƚϲ��������ȼ�*/  
{     
    if((oper[*top_oper] == '-' || oper[*top_oper] == '+') && (ch == '*' || ch == '/'))         /*�жϵ�ǰ���ȼ��Ƿ��ջ�����������ȼ���*/  
    {  
        return 0;                      /*������ѹ��ջ*/   
    }   
    else if(*top_oper == -1 || ch == '('|| (oper[*top_oper] == '(' && ch != ')'))  /*�жϲ�����ջ�Ƿ�Ϊ�գ�ջ������   ���Ƿ�Ϊ'('*/  
    {  
		return 0;                       /*������ѹ��ջ*/  
    }  
    else if (oper[*top_oper] =='(' && ch == ')' )       /*�ж������ڵı��ʽ�Ƿ�������*/  
    {  
		(*top_oper)--;  
		return 1;                       /*�ԣ������д���*/  
    }  
    else  
    {  
        return -1;                     /*���в�����������*/  
    }  
}  


float deal_date(float *operand ,char *oper ,int *top_num, int *top_oper)    /*������������*/  
{  
    float num_1 = operand[*top_num];              /*ȡ������ջ����������*/  
    float num_2 = operand[*top_num - 1];  
    
    float value = 0;  
    
    if(oper[*top_oper] == '+')                  /*�ӷ�����*/  
    {  
		value = num_1 + num_2;  
    }  
    
    else if(oper[*top_oper] == '-')             /*��������*/  
    {  
		value = num_2 - num_1;  
    }  
    
    else if(oper[*top_oper] == '*')             /*�˷�����*/  
    { 
        value = num_2 * num_1;  
    }  
    
    else if(oper[*top_oper] == '/')             /*��������*/  
    {  
		value = num_2 / num_1;  
    }  
    
    (*top_num) --;                              /*������ջ������һλ*/  
    operand[*top_num] = value;                  /*���õ���ֵѹ������ջ*/  
    (*top_oper) --;                             /*��������ջ������һλ*/  
}  


float compute()  
{
	char *str = computing;
    float operand[MAX_SIZE] = {0.0};                /*����ջ����ʼ��*/  
    int top_num = -1;  
    
    char oper[MAX_SIZE] = {0};                  /*������ջ����ʼ��*/  
    int top_oper = -1;  
//    char *str = (char *) malloc (sizeof(char) * 100);               /*���ʽ*/   
    char* temp;  
    char dest[MAX_SIZE];  
    
    int num = 0;  
    int i = 0;  
    
    while(*str != '\0')  
    {  
		temp = dest;  
		while(*str >= '0' && *str <= '9' || *str == '.')           /*�ж��Ƿ�������*/  
        {  
   			*temp = *str;  
   			str ++;  
   			temp ++;                  
		}                                 
       
        if(*str != '(' && *(temp - 1) != '\0')      /*�жϷ����Ƿ�Ϊ'('*/  
		{  
		   *temp = '\0';  
		   num = atoi(dest);               /*���ַ���תΪ����*/  
		   insert_operand(operand, &top_num,num);      /*������ѹ������ջ*/  
		}  

		while(1)  
		{  
		   i = compare(oper,&top_oper,*str);      /*�жϲ��������ȼ�*/  
		   if(i == 0)  
		   {  
		       insert_oper(oper,&top_oper,*str);   /*ѹ�������*/  
		       break;  
		   }  
		   
		   else if(i == 1)                         /*�ж������ڵı��ʽ�Ƿ����*/  
		   {  
				str++;
		   }  
		   
		   else if(i == -1)                        /*�������ݴ���*/  
		   {  
				deal_date(operand,oper,&top_num,&top_oper);  
		   }  
		}  
        str ++;                 /*ָ����ʽ��һ���ַ�*/  
    }  
    
//    printf("num = %f\n",operand[0]);        /*������*/  
    return operand[0];                       /*�����˳�*/  
}  

void VS_StrTrim()
{
	int i,k=0;
	for(i=0;buf[i]!='\0';i++)
	{
		if(buf[i]!=' ')
		buf[k++]=buf[i];
	}
	buf[k]=buf[i];
} 

int Reader()
{
	FILE *fp;            /*�ļ�ָ��*/
	int i = 0;
	//int buf_len = 0;
	char *temp_buf_point = buf;
	if((fp = fopen("cal_test.txt","r")) == NULL)
	{
	perror("fail to read");
	exit (1) ;
	}
		while(!feof(fp))//����Ϊ�ļ���βʱ
	{
		fgets(temp_buf_point, 200, fp);//������ļ��е����ݷ���������		
		temp_buf_point = strlen(temp_buf_point) + temp_buf_point - 1;
		//buf_len = strlen(buf);
		
	}
	fclose(fp);
//	printf("%s",buf[0]);
	return 0;
}

int *findplace(char target,char *f,char *i)
{
	int j; 
	
	for(j=0;j<30;j++)
	{
		if(f[j] == target)
		{
			answer_place = j;
			int_or_float = 0;
			break;
		}
		else if(i[j] == target)
		{
			answer_place = j;
			int_or_float = 1;
			break;
		}
		else
		{
			answer_place = -1;
			int_or_float = 2;
		}
	}
	int a[2];
	a[0] = answer_place;
	a[1] = int_or_float;
	return a;
}

int main()
{
	initial();
	Reader();
	VS_StrTrim();	//ȥ�ո� 
	
	
	int juhao;				//���λ�� 
	int fenhao_flag = 0;
	int int_flag = 0;
	int float_flag = 0;
	
	int m;
	for(m=0;m<1024;m++)
	{
		if(buf[m] == ';')
		{
			
			fenhao[fenhao_flag] = m;
			fenhao_flag++;
			
		}
	}
	//	�������ǵõ��� fenhao[],denghao[],juhao.�ֱ��ʾ���������txt���⼸������λ���ַ���buf�ľ���λ�á�
	//	��ʼ�����ַ���
	//	��'start;'Ϊ�Ϸ������뿪ʼ�� 
	if (buf[0] == 's' && buf[1] == 't' && buf[2] == 'a' && buf[3] == 'r' && buf[4] == 't')
	{
//		continue;
	}
	else
	{
		printf("Error(Line 1):Please start with a 'start;'!!\n");
		return 0;
	}
	
	
	while(1)
	{
		
		//	�������� 
		if (buf[fenhao[take_fenhao]+1] == 'i' && buf[fenhao[take_fenhao]+2] == 'n' && buf[fenhao[take_fenhao]+3] == 't')
		{
			i[int_flag] = buf[fenhao[take_fenhao]+4];
			int_flag++;
			if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
			{
				printf("End of text...\n");
				break;
			}
		}
		else if (buf[fenhao[take_fenhao]+1] == 'f' && buf[fenhao[take_fenhao]+2] == 'l' && buf[fenhao[take_fenhao]+3] == 'o' && buf[fenhao[take_fenhao]+4] == 'a' && buf[fenhao[take_fenhao]+5] == 't')
		{
			f[float_flag] = buf[fenhao[take_fenhao]+6];
			float_flag++;
			if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
			{
				printf("End of text...\n");
				break;
			}
		}
		//	����ֵ���㣬����compute��������������ձ�����������д��int_result[]��float_result[]�� 
		else if (buf[fenhao[take_fenhao]+2] == '=')
		{
			//	findplace����ΪѰ�ҵȺ�ǰ�����������Ƿ��壬Ϊ�����ͻ������͡� 
			//  
			int int_or_float;
			int answer_place;
			int *ret = findplace(buf[fenhao[take_fenhao]+1],f,i);
			int_or_float = ret[1];
			answer_place = ret[0];
			if (answer_place == -1)
			{
				printf("Error(Line %d):Undefined variable!\n",take_fenhao+2);
				return 0;
			}
			else
			{
				//������int�� 
				if(int_or_float == 1)
				{
					int flag;
					
					for(flag=0;buf[fenhao[take_fenhao]+3+flag] != ';';flag++)
					{
						computing[flag] = buf[fenhao[take_fenhao]+3+flag];
					}
					float result = compute(computing);	//����Ⱥź�����ַ�������Ӧ�Ľ��
					int int_result = (int)result;
					ir[answer_place] = int_result;
				}
				else if(int_or_float == 0)
				{
					int flag;
					
					for(flag=0;buf[fenhao[take_fenhao]+3+flag] != ';';flag++)
					{
						computing[flag] = buf[fenhao[take_fenhao]+3+flag];
					}
					float result = compute(computing);	//����Ⱥź�����ַ�������Ӧ�Ľ��
					fr[answer_place] = result;
				}
				if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
				{
					printf("End of text...\n");
					break;
				}
			}
			
		}
		//	���������ӡ 
		else if (buf[fenhao[take_fenhao]+1] == 'w' && buf[fenhao[take_fenhao]+2] == 'r' && buf[fenhao[take_fenhao]+3] == 'i' && buf[fenhao[take_fenhao]+4] == 't' && buf[fenhao[take_fenhao]+5] == 'e' && buf[fenhao[take_fenhao]+6] == '(')
		{
			
			int *ret = findplace(buf[fenhao[take_fenhao]+7],f,i);
			int_or_float = ret[1];
			answer_place = ret[0];
			if(int_or_float == 1)
			{
				printf("Answer is %d \n",ir[answer_place]);
			}
			else if(int_or_float == 0)
			{
				printf("Answer is %f \n",fr[answer_place]);
			}
			else
			{
			printf("Error:Comuputing UNKNOWN WRONG!\n");
			return 0;
			}
			if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
			{
				printf("End of text...\n");
				break;
			}
		}
		else
		{
			if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
			{
				printf("End of text...\n");
				break;
			}
			printf("Error(Line %d):Ending or UNKNOWN WRONG!\n",take_fenhao+1);
			return 0;
		}
		take_fenhao++;
	}
	return 0;
}
