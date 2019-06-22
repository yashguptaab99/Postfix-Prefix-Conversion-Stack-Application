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

using namespace std;

int main()
{
	expression e;//object of expression class
	int ch;
	float ans;
	do
	{
		//Menu
		cout<<"\n\n\t*********************\n";
		cout<<"\tWELCOME TO THE MENU ! \n";
		cout<<"\t*********************\n";

		cout<<"\t1)Input Infix Expression\n\n\t2)Infix to Postfix Conversion\n\n\t3)Infix to Prefix Conversion\n\n\t4)Evaluate PostFix\n\n\t5)Evaluate PreFix\n\n\t6)Exit\n\n";
		cout<<"Enter the Choice :: ";
		cin>>ch;
		switch(ch)
		{
			case 1 :
				cout<<"\n\t<<<<<<<< INPUT INFIX EXPRESSION >>>>>>>>\n";
				e.setExp();
				cout<<"\n\t----------------------------------------\n";
				break;
			case 2 :
				cout<<"\n\t<<<<<<<< INFIX TO POSTFIX EXPRESSION >>>>>>>>\n";
				e.inToPostFix();
				e.printPostFix();
				cout<<"\n\t--------------------------------------------\n";
				break;
			case 3 :
				cout<<"\n\t<<<<<<<< INFIX TO PREFIX EXPRESSION >>>>>>>>\n";
				e.inToPreFix();
				e.printPreFix();
				cout<<"\n\t--------------------------------------------\n";
				break;
			case 4 :
				cout<<"\n\t<<<<<<<< EVALUATE EXPRESSION >>>>>>>>\n\n";
				ans = e.eval_postExp();
				cout<<"\tAnswer : "<<ans;
				cout<<"\n\n\t-------------------------------------\n";
				break;
			case 5 :
				cout<<"\n\t<<<<<<<< EVALUATE EXPRESSION >>>>>>>>\n\n";
				ans = e.eval_preExp();
				cout<<"\tAnswer : "<<ans;
				cout<<"\n\n\t-------------------------------------\n";
				break;
			case 6://Exit
				cout<<"\n\n\t\t\tEXITING...";
				break;
			default :
				cout<<"\tInvalid Input\n";
				break;
		}
	}while(ch!=6);
	return 0;

}
