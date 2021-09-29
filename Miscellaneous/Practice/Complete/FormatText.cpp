#include <iostream>
#include <fstream>
#include <sstream>

#define WORDCOUNT 100

struct wordItem
{
	std::string word;
	int count;	
};

std::string read_file_as_text( std::string url )
{
	std::ifstream ifs;
	ifs.open( url );
	if ( !ifs )
	{
		std::cout << "Unable to open file: " << url << std::endl;
		return "";
	}

	std::string ret = "";
	while ( !ifs.eof() )
	{
		std::string tmp;
		getline( ifs, tmp );
		ret += tmp;
	}
	ifs.close();
	return ret;
}

void to_lowercase( std::string& text )
{
	for ( int i = 0; i < ( int )text.size(); i++ )
	{
		if ( text[ i ] >= 'A' && text[ i ] <= 'Z' )
		{
			text[ i ] = text[ i ] - ( 'A' - 'a' );
		}
	}
}

void remove_punctuation( std::string& text )
{
	std::string punc = "?!.,'\";:-\n\r\t";
	for ( int i = 0; i < ( int )text.size(); i++ )
	{
		char c = text[ i ];
		if ( punc.find( c ) != std::string::npos )
		{
			text.erase( i, 1 );
			i--;
		}
		else if ( i < ( int )text.size() - 1 )
		{
			if ( c == ' ' && text[ i + 1 ] == ' ' )
			{
				text.erase( i, 1 );
				i--;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	// Arguments:
		// argv[ 1 ] = program name
		// argv[ 2 ] = input file
		// argv[ 3 ] = 
		// argv[ 4 ] = 


	std::ifstream inFile;
	std::string processedText;
	processedText = read_file_as_text(argv[ 1 ]);
	std::ofstream outFile;

	if ( processedText.size() )
	{
		to_lowercase(processedText);
		remove_punctuation(processedText);
		outFile.open("processedText.txt");
		outFile << processedText;
	}
}