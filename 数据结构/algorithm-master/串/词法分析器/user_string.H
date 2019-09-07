#ifndef _user_string_h_
#define _user_string_h_
#include <iostream>
using namespace std;
class User_String
{
protected :
	char *string ;
public :
	int string_size ;
	User_String(int size) ;	
	User_String() ;
	bool operator==(User_String st) ;
	void operator=(User_String st) ;
};
#endif
