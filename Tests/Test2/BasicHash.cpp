#include <iostream>

int hashSum( std::string key, int tableSize )
{
	int sum = 0;
	for (  int i = 0; i < int(key.size()); ++i )
	{
		sum += key[ i ];
	}
	return sum % tableSize;
}

int hashMult( std::string key )
{
	int m = 256;
	float A = 13./32.;
	int sum = 0;

	for ( int i = 0; i < int( key.size() ); ++i )
	{
		sum += key[ i ];
	}
	
	float kA = sum * A;
	float kARem = kA - int( kA );

	return int( kARem * m );
}

int main()
{
	int a = hashMult( "apple" );
	std::cout << a << std::endl;
}