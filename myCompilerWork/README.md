### 计算表达式的完整文法：

Program -> block 						//程序由block组成

Block -> {statement,expressions} //block 	//可以为声明和语句

Expressions -> expressions | expression 		//语句可以为表达式

Expressions -> write(id)					//语句可以为write( )

Statement -> type id						//声明可以为type id

Type -> int | float							//type只能为int或float

Loc ->id									//赋值语句

Expression -> term + expression 			//表达式计算法

Expression -> term - expression			

Term -> term * factor			

Term -> term / factor							

Term -> factor

Factor -> id | (expression) //factor			//可为id或者表达式

Id -> a-z | A-Z 							//id只能为单个字母

 

单行终结符为’;’

总终结符为’`’

由于害怕与小数点冲突，所以总终结符进行了一点改动。

 

首先读取文件内容，将内容以字符串形式存入buf数组；

将表达式进行预处理，去空格；

根据float或int，将定义的变量分别存入f[ ]和i[ ]；

读取到’=’号时，将等号右边的字符串存入computing[ ]，并进行计算，所得到的结果返回值根据等号左边的变量，存入ir[ ]或fr[ ]（int result & float result)；

当读取到write( )类似的字符时，根据括号内的变量名称，去寻找其结果，如果没有定义则报错，如果有定义则根据其定义类型打印结果。

 

### 测试用例

为cal_test.txt，以下为其内容

start;

int b;

float a;

b = 5*2/3;

a = (10.44*356+1.28) / 2 + 1024 * 1.6;

write(a);

write(b)`

测试结果

![img](file:///C:\Users\ADMINI~1\AppData\Local\Temp\ksohtml11176\wps2.jpg) 

 