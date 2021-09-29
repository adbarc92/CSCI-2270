#include <iostream>
#include <vector>

//----------------------------------------------------------------------------------------
// Prototypes go here (you may add more if you need)
//----------------------------------------------------------------------------------------
class Entry 
{
public:
	Entry( std::string name, std::string address, unsigned int phone );
	void print();
	std::string search( std::string filter, std::string variable );
};

void filter( std::string filter, std::string variable, std::vector< Entry* >& entries );
std::string to_upper_case( std::string s );

//----------------------------------------------------------------------------------------
// Class definitions go here (you may add more if you need)
//----------------------------------------------------------------------------------------
Entry::Entry( std::string name, std::string address, unsigned int phone )
{

}

void Entry::print()
{

}

std::string Entry::search( std::string filter, std::string variable )
{
	return "";
}

//----------------------------------------------------------------------------------------
// Function definitions go here (you may add more if you need)
//----------------------------------------------------------------------------------------
void filter( std::string filter, std::string variable, std::vector< Entry* >& entries )
{

}

std::string to_upper_case( std::string s )
{
	return s;
}

int main()
{
	std::cout << "Welcome to a simple [name, address, phone] database." << std::endl << std::endl;

	std::vector< Entry* > entries;
	entries.push_back( new Entry( "Sharen I. Lee", "2364 James Avenue", ( unsigned int ) 3162677883 ) );
	entries.push_back( new Entry( "Albert M. Mull", "1050 Reel Avenue", ( unsigned int ) 5053720732 ) );
	entries.push_back( new Entry( "Virighania F. King", "1709 Park Boulevard", ( unsigned int ) 3169353788 ) );
	entries.push_back( new Entry( "Annette A. Sapienza", "2231 Gandy Street", ( unsigned int ) 5052627863 ) );
	entries.push_back( new Entry( "Sabrina D. Robilee", "3499 Daffodil Lane", ( unsigned int ) 3162077800 ) );
	entries.push_back( new Entry( "Ying S. Kocz", "1986 Cardinal Lane", ( unsigned int ) 5052077800 ) );
	entries.push_back( new Entry( "Rodney K. Edwin", "2364 James Avenue", ( unsigned int ) 2172295977 ) );
	entries.push_back( new Entry( "Stella O. Lee", "2164 James Avenue", ( unsigned int ) 5055082428 ) );
	entries.push_back( new Entry( "Brenda P. Livingston", "1788 Cimmaron Road", ( unsigned int ) 7145845562 ) );
	entries.push_back( new Entry( "Sharon O. Lee", "3783 Shingleton Road", ( unsigned int ) 2693856633 ) );

	// This will print the contents of each entry with this template:
	// <i>.) <name> | <address> | <phone>
	// There are also these additional rules:
	// * If the name is less than 15 characters long, then pad the end with spaces to make it
	// 15 characters long.
	// * If the name exceeds 15 characters, then then add an ellipsis such that the name is
	// only 15 characters long, including the ellipsis.
	// An example:
	// ...
	// 2.) Albert M. Mull  | 1050 Reel Avenue | 5053720732
	// 3.) Virighania F... | 1709 Park Boulevard | 3169353788
	// 4.) Annette A. S... | 2231 Gandy Street | 5052627863
	// ...
	std::cout << "## ENTRIES ##" << std::endl;
	for( unsigned int i = 0; i < entries.size(); i++ )
	{
		Entry* e = entries[ i ];
		std::cout << ( i + 1 ) << ".) ";
		e->print();
		std::cout << std::endl;
	}

	// This should output:
	// 1.) Sharen I. Lee
	// 2.) Sabrina D. Robilee
	// 3.) Stella O. Lee
	// 4.) Sharon O. Lee
	std::cout << std::endl << "## Filter 1 ##" << std::endl;
	filter( "Lee", "name", entries );

	// This should output:
	// 1.) 2364 James Avenue
	// 2.) 1050 Reel Avenue
	// 3.) 2364 James Avenue
	// 4.) 2164 James Avenue
	std::cout << std::endl << "## Filter 2 ##" << std::endl;
	filter( "ave", "address", entries );

	// This should output:
	// 1.) 3162677883
	// 2.) 3169353788
	// 3.) 3162077800
	std::cout << std::endl << "## Filter 3 ##" << std::endl;
	filter( "316", "phone", entries );

	// This should output:
	// 1.) Annette A. Sapienza
	// 2.) Ying S. Kocz
	std::cout << std::endl << "## Filter 4 ##" << std::endl;
	filter( "z", "name", entries );

	// This should output:
	// 1.) 3162677883
	// 2.) 5053720732
	// 3.) 3169353788
	// 4.) 5052627863
	// 5.) 3162077800
	// 6.) 2693856633
	std::cout << std::endl << "## Filter 5 ##" << std::endl;
	filter( "3", "phone", entries );

	// Free memory
	for( Entry* e: entries )
	{
		delete e;
	}

	std::cout << std::endl;
	std::cout << "Program over." << std::endl;

	return 0;
}