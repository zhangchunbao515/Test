#ifndef _arraylist_write_h_
#define _arraylist_write_h
#include "user_string.h"

class ArrayList_Write
{
protected:
	User_String *listhead ;
public :
	User_String EndTag ;
	int ArrayList_Write_size ;
	ArrayList_Write ( int size ) ;
	void create () ;
	friend User_String ;
};
#endif
