//============================================================================
// Class            : SE9
// Batch            : F9
// Roll No.         : 23121
// Author           : Yash Gupta
// Assignment No.   : 1
// Problem Statement: Implement stack as an abstract data type using linked list and use this
//                    ADT for conversion of infix expression to postfix, prefix and evaluation of
//                    postfix/prefix expression.
//============================================================================
#include <iostream>
#include "expression.h"
#include "stack.cpp"
#include <math.h>
#include <string.h>
#include <iomanip>
using namespace std;

//Constructor
expression :: expression()
{
	postFix = NULL;
	infix=NULL;
	exp_size = 0;
	preFix = NULL;
	postFix_size = 0;
}

//Function to set expression
void expression :: setExp()
{

	/* Pre- No expression in char array
	 *
	 * Post - Taken expression from user
	 * 		  Validate the expression according to math rule
	 * 		  Assign values to required varilable ex.Infix
	 */

	cout<<"\tEnter the expression : ";
	cin.ignore();
	cin.getline(exp,50);
	exp_size = strlen(exp);//length

	//Validation
	if(isValid()==1)
	{
		if(isValid1()==1)
		{
			cout<<"\n\tExpression Accepted Successfully\n";
			printExp();
		}
		else
		{
			cout<<"\n\tERROR : INVALID INFIX EXPRESSION\n";
		}
	}
	else
	{
		cout<<"\n\tERROR : INVALID INFIX EXPRESSION\n";
	}

	int i=0;
	int count = exp_size;
	while(i<exp_size)
	{
		if(exp[i]=='(' || exp[i]==')')//Taking the count of total operator and operand
		{
			count--;
		}
		i++;
	}

	//Dynamic allocation
	postFix_size = count;
	infix = new char[exp_size];
	preFix = new char[postFix_size];
	postFix = new char[postFix_size];
}


//Function to convert infix to postfix
void expression :: inToPostFix()
{
	/* Pre - infix expression stored in infix[]
	 *
	 * Post - infix expression converted to postfix expression using stack.
	 * 		  Stored into postfix[].
	 */

	//Step wise output
	cout<<"\n\t----------------------------------------------------------";
	cout<<"\n\tInfix               Stack               Postfix              ";
	cout<<"\n\t----------------------------------------------------------\n";

	//required Variable declaration
	stack<char> stack1;//stack object
	int counter = 0,i,j;
	int loop_pf = 0;
	char token;
	char topToken;
	char tokenOut;

	//Algorithm wise code
	while(counter<exp_size)
	{
		token = exp[counter];

		for(i=counter+1,j=0;i<exp_size;i++,j++)
		{
			infix[j] = exp[i];
		}
		infix[j] = '\0';
 		cout<<"\t"<<setw(20)<<left<<infix;
		if(token == '(')
		{
			stack1.push(token);
		}
		else if(token == ')')
		{
			token = stack1.pop();
			while(token != '(')
			{
				postFix[loop_pf] = token;
				token = stack1.pop();
				loop_pf++;
			}
		}
		else if(isOperator(token))
		{
			topToken = stack1.peep();
			while(stack1.isEmpty() == 0 && priority(token)<priority(topToken))
			{
				tokenOut = stack1.pop();
				postFix[loop_pf] = tokenOut;
				loop_pf++;
				topToken = stack1.peep();
			}
			if(priority(token)>priority(topToken))
			{
				stack1.push(token);
			}
			else if(priority(token) == priority(topToken))
			{
					if((associativity(token) == 1) && (associativity(topToken)==1))
					{
						tokenOut = stack1.pop();
						postFix[loop_pf] = tokenOut;
						loop_pf++;
						stack1.push(token);
					}
					if((associativity(token) == 2) && (associativity(topToken)==2))
					{
						stack1.push(token);
					}
			}
		}
		else
		{
			postFix[loop_pf] = token;
			loop_pf++;
		}

		if(stack1.isEmpty()==0)
		{
			stack1.display();
		}
		else
			cout<<setw(20)<<left<<"NONE";

		cout<<setw(20)<<left<<postFix<<endl;
		counter++;
	}

	while(stack1.isEmpty() != 1)
	{
		cout<<"\t"<<setw(20)<<left<<"NONE";
		token = stack1.pop();
		if(stack1.isEmpty()==0)
		{
			stack1.display();
		}
		else
			cout<<setw(20)<<left<<"NONE";
		postFix[loop_pf] = token;
		cout<<setw(20)<<left<<postFix<<endl;
		loop_pf++;
	}
}


//Function to convert infix to postfix
void expression :: inToPreFix()
{
	/* Pre - infix expression stored in infix[]
	 *
	 * Post - infix expression converted to prefix expression using stack.
	 * 		  Stored into prefix[].
	 */

	//required Variable declaration
	stack<char> stack1;//stack object
	int loop = exp_size-1;
	int loop_pf = postFix_size-1;
	char token;

	//Step wise output
	cout<<"\n\t--------------------------------------------------------";
	cout<<"\n\tInfix               Stack               Prefix              ";
	cout<<"\n\t--------------------------------------------------------\n";

	//Algorithm wise code
	while(loop>=0)
	{
		token = exp[loop];

		if(isOperand(token))
		{
			preFix[loop_pf] = token;
			loop_pf--;
		}
		else if(token == ')')
		{
			stack1.push(token);
		}
		else if(token == '(')
		{
			char tempToken;
			tempToken = stack1.pop();
			while(tempToken != ')')
			{
				preFix[loop_pf] = tempToken;
				loop_pf--;
				tempToken = stack1.pop();
			}
		}
		else if(isOperator(token))
		{
			char topToken = stack1.peep();
			if(priority(token)>priority(topToken))
			{
				stack1.push(token);
			}
			else if(priority(token)<priority(topToken))
			{
				while(priority(token)<priority(topToken) && stack1.isEmpty()==0)
				{
					char temp = stack1.pop();
					preFix[loop_pf] = temp;
					loop_pf--;
					topToken = stack1.peep();
				}
				stack1.push(token);
			}
			else if(priority(token) == priority(topToken))
			{
				if(associativity(token)==1 && associativity(topToken)==1)
				{
					stack1.push(token);
				}
				else if(associativity(token)==2 && associativity(topToken)==2)
				{
					char temp = stack1.pop();
					preFix[loop_pf] = temp;
					stack1.push(token);
					loop_pf--;
				}
			}
		}

		if(stack1.isEmpty()==0)
		{
				stack1.display();
		}
		else
			cout<<setw(20)<<left<<"NONE";

		cout<<setw(20)<<left<<preFix<<endl;
		loop--;
	}
	while(stack1.isEmpty()==0)
	{
		cout<<setw(20)<<left<<"NONE";
		cout<<setw(20)<<left<<stack1.peep();
		token = stack1.pop();
		preFix[loop_pf] = token;
		cout<<setw(20)<<left<<preFix<<endl;
		loop_pf--;
	}
}


//Evaluation of Postfix
float expression :: eval_postExp()
{
	/* Pre - Postfix expression in postfix[] and values are taken by user
	 *
	 * Post - Postfix expression evaluation is done, values are given by user, stack used
	 * 		  according algorithm, Value in float
	 */

	//required Variable declaration
	stack<float> stack1;//stack object
	int loop_pf = 0;
	float ans;
	float temp1=-1,temp2=-1;

	while(loop_pf<postFix_size)
	{
		char token = postFix[loop_pf];
		if(isOperand(token))
		{
			stack1.push(token);
		}
		else if(isOperator(token))
		{
			if(stack1.isEmpty()==0)
			{
				float o1,o2;
				float op1 = stack1.pop();
			    if((char)op1 == '$')
			    {
			    	op1 = stack1.pop();
			    	temp1 = op1;
			    }
				float op2 = stack1.pop();
			    if((char)op2 == '$')
			   	{
			    	op2 = stack1.pop();
			    	temp2 = op2;
			   	}
				if(isalpha((char)op1)!=0 && op1!=temp1)
				{
					cout<<"Enter the data of variable "<<(char)op1<<" : ";
					cin>>o1;
				}
				else
				{
					o1 = op1;
				}
				if(isalpha((char)op2)!=0 && op2!=temp2)
				{
					cout<<"Enter the data of variable "<<(char)op2<<" : ";
					cin>>o2;
				}
				else
				{
					o2 = op2;
				}

				ans = calculate(token,o2,o1);
				stack1.push(ans);
				stack1.push('$');
			}
			else
				cout<<"Stack is empty";
		}
		loop_pf++;
	}
	float temp3 = stack1.pop();
	return (stack1.pop());
}


//Evaluation of prefix
float expression :: eval_preExp()
{
	/* Pre - Prefix expression in prefix[] and values are taken by user
	 *
	 * Post - Prefix expression evaluation is done, values are given by user, stack used
	 * 		  according algorithm, Value in float
	 */

	//required Variable declaration
	stack<float> stack1;//Stack object
	int loop_pf = postFix_size-1;
	float ans;
	float temp1=-1,temp2=-1;

	while(loop_pf>=0)
	{
		char token = preFix[loop_pf];
		if(isOperand(token))
		{
			stack1.push(token);
		}
		else if(isOperator(token))
		{
			if(stack1.isEmpty()==0)
			{
				float o1,o2;
				float op1 = stack1.pop();
			    if((char)op1 == '$')
			    {
			    	op1 = stack1.pop();
			    	temp1 = op1;
			    }
				float op2 = stack1.pop();
				if((char)op2 == '$')
			   	{
			    	op2 = stack1.pop();
			    	temp2 = op2;
			   	}
				if(isalpha((char)op1)!=0 && op1!=temp1)
				{
					cout<<"Enter the data of variable "<<(char)op1<<" : ";
					cin>>o1;
				}
				else
				{
					o1 = op1;
				}
				if(isalpha((char)op2)!=0 && op2!=temp2)
				{
					cout<<"Enter the data of variable "<<(char)op2<<" : ";
					cin>>o2;
				}
				else
				{
					o2 = op2;
				}

				ans = calculate(token,o1,o2);
				stack1.push(ans);
				stack1.push('$');
			}
			else
				cout<<"Stack is empty";
		}
		loop_pf--;
	}
	float temp3 = stack1.pop();
	return (stack1.pop());
}

//Function to check priority of operator
int expression :: priority(char check)
{
	switch(check)
	{
		case '+' :
			return 1;
		case '-' :
			return 1;
		case '*' :
			return 2;
		case '/' :
			return 2;
		case '%' :
			return 2;
		case '^' :
			return 3;
		default :
			return 0;
			break;
	}
}


//Function to check is given char id operator or not
int expression :: isOperator(char temp)
{
	if(temp == '+' || temp == '-' || temp == '*' || temp == '/' || temp == '^' || temp == '%')
	{
		return 1;
	}
	else
		return 0;
}

//Function to check is given char id operand or not
int expression :: isOperand(char temp)
{
	if(((float)temp>=65 && (float)temp<=90) || ((float)temp>=97 && (float)temp<=122))
	{
		return 1;
	}
	else
		return 0;
}

//Function to check associativity of given operator
int expression :: associativity(char temp)
{
	switch(temp)
	{
	 	 case '+':
	 		 return 1;
	 	 case '-':
	 		 return 1;
	 	 case '*':
	 		 return 1;
	 	 case '/':
	 		 return 1;
	 	 case '%':
	 		 return 1;
	 	 case '^':
	 		 return 2;
	 	 default:
		 	 return 0;
	}
}

//Function to calculate using given operator and operand
float expression :: calculate(char temp,float o1,float o2)
{
	switch(temp)
	{
		case '+':
			return o1 + o2;
		case '-':
			return o1 - o2;
		case '*':
			return o1*o2;
		case '/':
			return o1/o2;
		case '^' :
			return pow(o1,o2);
		case '%' :
			return o1/o2;
		default :
			return 0;
	}
}

//Function to print postfix
void expression :: printPostFix()
{
	int count ;
	cout<<"\n\tPOSTFIX Expression is : ";
	for(count = 0;count<postFix_size;count++)
	{
		cout<<postFix[count];
	}
	cout<<endl;
}


//Function to print prefix
void expression :: printPreFix()
{
	int count ;
	cout<<"\n\tPREFIX Expression is  : ";
	for(count = 0;count<postFix_size;count++)
	{
		cout<<preFix[count];
	}
	cout<<endl;
}

//Function to print expresion
void expression :: printExp()
{
	int count ;
	cout<<"\tEntered Expression is : ";
	for(count = 0;count<exp_size;count++)
	{
		cout<<exp[count];
	}
	cout<<endl;
}

int expression :: isValid()
{
	int cnt_openb=0;
	int cnt_closeb=0;
	int cnt_operand=0;
	int cnt_operator =0;
	if(exp == NULL)
	{
		cout<<"\tExpression not entered\nPlease enter the expression first\n";
		return 0;
	}
	else
	{
		int loop_pf=0;
		while(loop_pf<exp_size)
		{
			if(exp[loop_pf]==')')
			{
				cnt_closeb++;
			}
			else if(exp[loop_pf] == '(')
			{
				cnt_openb++;
			}

			if(isOperand(exp[loop_pf])==1)
			{
				cnt_operand++;
			}
			else if(isOperator(exp[loop_pf])==1)
			{
				cnt_operator++;
			}

			if(isOperand(exp[loop_pf])||isOperator(exp[loop_pf]) || exp[loop_pf] == '(' || exp[loop_pf] == ')')
			{
				loop_pf++;
			}
			else
				break;
		}
		if((loop_pf == exp_size) && (cnt_openb == cnt_closeb) && (cnt_operand == (cnt_operator+1)))
		{
			return 1;
		}
		else
			return 0;
	}
}

int expression :: isValid1()
{
	int loop_pf = 1;
	while(loop_pf<exp_size)
	{
		if(isOperand(exp[loop_pf-1]) && isOperand(exp[loop_pf]))
		{
			return 0;
		}
		if(isOperator(exp[loop_pf-1]) && isOperator(exp[loop_pf]))
		{
			return 0;
		}
		loop_pf++;
	}
	return 1;
}

//destructor
expression :: ~expression()
{
	delete []postFix;
	delete []preFix;
}
