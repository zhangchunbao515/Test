
#include <fstream.h>
#include <stdlib.h>
class ArrayList_Operator;
class User_String
{
protected :
	char *string ;
public :
	int string_size ;
	User_String(int size) ;	
	User_String() ;
	friend bool operator==(const User_String &st1, const User_String &st2) ;
	User_String& operator=( const User_String &st) ;
	User_String& operator[](const int size);
	const User_String& operator[](const int size)const;
	friend istream& operator>>(istream &in , User_String &st);
	friend ArrayList_Operator;
	
};

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

istream& operator>>(istream &in , User_String &st)
{	
	int size = 0;
	char ch ;
	for(int count = 0 ; ; count++)
	{
	
		in.get(ch);
		if (ch == ' ' || ch == '\n') 
		{
			st.string[count] = '\0';
			size ++;
			st.string_size = size ;
			break;
		}
		else
		{
			st.string[count] = ch;
			size ++ ;
			st.string_size = size;
		}
	}
	return in;
}



User_String :: User_String()
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
bool operator==( const User_String &st1 , const User_String &st2)
{
	if ( st1.string_size != st2.string_size)
	{
		return false;
	}
	else
	{
		int count = 0;
		while(st1.string[count] !='\0' && st2.string[count] !='\0')
		{
			if (st1.string[count] == st2.string[count]) 
			{
				count++;
			}
			else
				return false;
		}
		return true;
	}
}

User_String& User_String :: operator=( const User_String &st)
{
	string_size = st.string_size ;
	for(int count = 0;;count ++)
	{
		if ( st.string[count] == '\0')  break;
		string[count] = st.string[count] ;
	}
	return *this;
}
User_String& User_String :: operator[](const int size)
{
	return this[size];
}
const User_String& User_String :: operator[](const int size)const
{
	return this[size];
}


class ArrayList_Operator
{
protected:
	User_String *listhead ;
public :
	User_String EndTag ;
	int ArrayList_Operator_size ;
	ArrayList_Operator ( int size ) ;
	void create () ;
	friend User_String ;

};



ArrayList_Operator :: ArrayList_Operator ( int size ) 
{
	ArrayList_Operator_size = size ;
	listhead = new User_String [ ArrayList_Operator_size ] ;
	if ( listhead == NULL )
	{
		cout << "´æ´¢·ÖÅä´íÎó" ;
		exit (1) ;
	}
}

void ArrayList_Operator :: create ()
{
	ifstream in ;
	in . open ("d:\\C++ÔËËã·û.txt");
	for (int count = 0 ; ; count ++)
	{
		in >> listhead[count];
		if (listhead[count] == EndTag)
			break;
	}
	in.close();
}

int main ()
{
	ArrayList_Operator arrlist(100) ;
	arrlist.create();
	return 0;
}


























