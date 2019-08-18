#include "arraylist_write.h"
#include <stdlib.h>
#include <fstream.h>
ArrayList_Write :: ArrayList_Write ( int size ) 
{
	ArrayList_Write_size = size ;
	listhead = new User_String [ ArrayList_Write_size ] ;
	if ( listhead == NULL )
	{
		cout << "存储分配错误" ;
		exit (1) ;
	}
}

void ArrayList_Write :: create ()
{
	ifstream in ;
	in . open ("d:\\C++关键字.txt" , ios :: in , 0);
    char ch ;
    
	for ( int arraylist_count = 0 ; ; arraylist_count ++ )
	{
		int user_string_size ;
		cin >> user_string_size ; 
		User_String str(user_string_size) ;
		for ( int string_count = 0 ; ; string_count ++ )
		{
			in.get(ch) ;
			if (ch == ' 'ch == '\n')  break;
			else 
			{
				cout<<"请用户输入字符串的预计最大长度:" ;
				
				str [ string_count ] = ch;
			}
		}
		if (str == EndTag)  break;
		else 
		{
			listhead [ arraylist_count ]  = str;
		}
	}
	in.close();
}







