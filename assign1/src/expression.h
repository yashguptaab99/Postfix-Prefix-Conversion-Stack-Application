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
#ifndef IMPLEMENT_H_
#define IMPLEMENT_H_

class expression
{
	private:
		char exp[50];
		int exp_size;
		int postFix_size;
		char *infix;
		char *postFix;
		char *preFix;
	public:
		expression();//constructor

		void setExp();//input infix expression
		void inToPostFix();//infix to postfix conversion
		void inToPreFix();//infix to prefix conversion

		float eval_postExp();//function to evaluate postfix expression
		float eval_preExp();//function to evaluate prefix expression

		int isOperator(char temp);//function to check if the entered character is an operator
		int isOperand(char temp);

		int isValid();//validations
		int isValid1();

		int priority(char check);//function to check priority of operators
		int associativity(char temp);//function to check associativity of operators

		float calculate(char temp,float o1,float o2);

		void printExp();
		void printPostFix();
		void printPreFix();

		~expression();
};

#endif /* IMPLEMENT_H_ */
