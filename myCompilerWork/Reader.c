#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512
#define MAX_SIZE 512                     /*数组长度*/  

char buf[MAX_LINE];
char f[MAX_LINE];	//存放输入中定义的float型变量 
float fr[MAX_LINE] = {0.0};
char i[MAX_LINE];	//存放输入中定义的int型变量 
int ir[MAX_LINE] = {0};
int fenhao[MAX_LINE] = {0};	//分号位置 
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
int insert_operand(float *operand , int * top_num ,float num)           /*数据压入数据栈*/  
{
    (*top_num) ++;  
    operand[*top_num] = num;                    /*保存数据*/  
    
    return 0;                           /*正常退出*/  
}  


int insert_oper (char * oper , int *top_oper , char ch)             /*操作符压入符号栈*/  
{  
    (*top_oper)++;  
    oper[*top_oper] = ch;                       /*保存操作符*/  
    return 0;                           /*正常退出*/  
}  
     
int compare(char *oper , int *top_oper , char ch)                   /*比较操作符优先级*/  
{     
    if((oper[*top_oper] == '-' || oper[*top_oper] == '+') && (ch == '*' || ch == '/'))         /*判断当前优先级是否比栈顶操作符优先级高*/  
    {  
        return 0;                      /*操作符压入栈*/   
    }   
    else if(*top_oper == -1 || ch == '('|| (oper[*top_oper] == '(' && ch != ')'))  /*判断操作符栈是否为空；栈顶操作   符是否为'('*/  
    {  
		return 0;                       /*操作符压入栈*/  
    }  
    else if (oper[*top_oper] =='(' && ch == ')' )       /*判断括号内的表达式是否计算完毕*/  
    {  
		(*top_oper)--;  
		return 1;                       /*对（）进行处理*/  
    }  
    else  
    {  
        return -1;                     /*进行操作符的运算*/  
    }  
}  


float deal_date(float *operand ,char *oper ,int *top_num, int *top_oper)    /*进行数据运算*/  
{  
    float num_1 = operand[*top_num];              /*取出数据栈中两个数据*/  
    float num_2 = operand[*top_num - 1];  
    
    float value = 0;  
    
    if(oper[*top_oper] == '+')                  /*加法操作*/  
    {  
		value = num_1 + num_2;  
    }  
    
    else if(oper[*top_oper] == '-')             /*减法操作*/  
    {  
		value = num_2 - num_1;  
    }  
    
    else if(oper[*top_oper] == '*')             /*乘法操作*/  
    { 
        value = num_2 * num_1;  
    }  
    
    else if(oper[*top_oper] == '/')             /*除法操作*/  
    {  
		value = num_2 / num_1;  
    }  
    
    (*top_num) --;                              /*将数据栈顶下移一位*/  
    operand[*top_num] = value;                  /*将得到的值压入数据栈*/  
    (*top_oper) --;                             /*将操作符栈顶下移一位*/  
}  


float compute()  
{
	char *str = computing;
    float operand[MAX_SIZE] = {0.0};                /*数据栈，初始化*/  
    int top_num = -1;  
    
    char oper[MAX_SIZE] = {0};                  /*操作符栈，初始化*/  
    int top_oper = -1;  
//    char *str = (char *) malloc (sizeof(char) * 100);               /*表达式*/   
    char* temp;  
    char dest[MAX_SIZE];  
    
    int num = 0;  
    int i = 0;  
    
    while(*str != '\0')  
    {  
		temp = dest;  
		while(*str >= '0' && *str <= '9' || *str == '.')           /*判断是否是数据*/  
        {  
   			*temp = *str;  
   			str ++;  
   			temp ++;                  
		}                                 
       
        if(*str != '(' && *(temp - 1) != '\0')      /*判断符号是否为'('*/  
		{  
		   *temp = '\0';  
		   num = atoi(dest);               /*将字符串转为数字*/  
		   insert_operand(operand, &top_num,num);      /*将数据压入数据栈*/  
		}  

		while(1)  
		{  
		   i = compare(oper,&top_oper,*str);      /*判断操作符优先级*/  
		   if(i == 0)  
		   {  
		       insert_oper(oper,&top_oper,*str);   /*压入操作符*/  
		       break;  
		   }  
		   
		   else if(i == 1)                         /*判断括号内的表达式是否结束*/  
		   {  
				str++;
		   }  
		   
		   else if(i == -1)                        /*进行数据处理*/  
		   {  
				deal_date(operand,oper,&top_num,&top_oper);  
		   }  
		}  
        str ++;                 /*指向表达式下一个字符*/  
    }  
    
//    printf("num = %f\n",operand[0]);        /*输出结果*/  
    return operand[0];                       /*正常退出*/  
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
	FILE *fp;            /*文件指针*/
	int i = 0;
	//int buf_len = 0;
	char *temp_buf_point = buf;
	if((fp = fopen("cal_test.txt","r")) == NULL)
	{
	perror("fail to read");
	exit (1) ;
	}
		while(!feof(fp))//当不为文件结尾时
	{
		fgets(temp_buf_point, 200, fp);//逐个将文件中的数据放入数组中		
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
	VS_StrTrim();	//去空格 
	
	
	int juhao;				//句号位置 
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
	//	这里我们得到了 fenhao[],denghao[],juhao.分别表示的是输入的txt中这几个符号位于字符串buf的具体位置。
	//	开始处理字符串
	//	以'start;'为合法的输入开始。 
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
		
		//	变量定义 
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
		//	变量值计算，调用compute函数，将结果按照变量定义类型写入int_result[]或float_result[]。 
		else if (buf[fenhao[take_fenhao]+2] == '=')
		{
			//	findplace函数为寻找等号前面的这个变量是否定义，为浮点型还是整型。 
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
				//存在于int中 
				if(int_or_float == 1)
				{
					int flag;
					
					for(flag=0;buf[fenhao[take_fenhao]+3+flag] != ';';flag++)
					{
						computing[flag] = buf[fenhao[take_fenhao]+3+flag];
					}
					float result = compute(computing);	//计算等号后面的字符串所对应的结果
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
					float result = compute(computing);	//计算等号后面的字符串所对应的结果
					fr[answer_place] = result;
				}
				if (buf[fenhao[take_fenhao] + 6] == '`' || buf[fenhao[take_fenhao] + 9] == '`' || buf[fenhao[take_fenhao] + 7] == '`' || buf[fenhao[take_fenhao] + 5] == '`')
				{
					printf("End of text...\n");
					break;
				}
			}
			
		}
		//	变量结果打印 
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
