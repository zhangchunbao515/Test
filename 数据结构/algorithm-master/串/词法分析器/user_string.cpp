#include "user_string.h"
#include < stdlib.h >
User_String :: User_String(int size)
{
	string_size = size ;
	string = new char [ string_size ] ;
	if ( string == NULL )
	{
		cout << "´æ´¢·ÖÅä´íÎó" ;
		exit ( 1 ) ;
	}
}

User_String :: User_string()
{
	int size = 4;
	string_size = size ;
	string = new char [ string_size ] ;
	if ( string == NULL )
	{
		cout << "´æ´¢·ÖÅä´íÎó" ;
		exit ( 1 ) ;
	}
	string[0] = 'e';
	string[1] = 'n';
	string[2] = 'd';
	string[3] = '\0';
}
bool User_String :: operator==(User_String st)
{
	for(int count = 0 ; ; count ++)
	{
		if (string[ count ] == st.string[ count ] && string_size == st.string_size)  continue;
		else 
		{
			return false;
		}
	}
	return true ;
}
void User_String :: operator=(User_String st)
{
	string_size = st.string_size ;
	for(int count = 0;;count ++)
	{
		if ( st.string[count] == '\0')  break;
		string[count] = st.string[count] ;
	}
}



















