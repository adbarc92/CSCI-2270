#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#define NUMSTOPWORDS 50

struct wordItem
{
	std::string word;
	int wordCount;
};

void swap (wordItem* smallItem, wordItem* bigItem) // Move from right to left
{
	wordItem temp;
	temp.wordCount = smallItem->wordCount;
	temp.word = smallItem->word;
	smallItem->wordCount = bigItem->wordCount;
	smallItem->word = bigItem->word;
	bigItem->wordCount = temp.wordCount;
	bigItem->word = temp.word;
}

std::string lowerCase(std::string str) // Helper; Removes capitalization
{
	int length = str.length();
	for (int i = 0; i < length; ++i)
	{
		if ( (int) str[i] >= 'A' && (int) str[i] < 'a')
		{
			int num = str[i]+32;
			str[i] = num;
		}
	}
	return str;
}

std::string clearPunc( std::string str ) // Helper; Removes punctuation
{
    int length = str.length();
    for ( int i = 0; i < length; ++i )
    {
        int c = str[ i ];
        if ( (c < 'A' && c!= 32) || c > 'z' )
        {
            str.erase( i, 1 );
            length = str.length();
        }
    }
    return str;
}

int getTotalNumberWords (wordItem list[], int length)
{
	int totalUniqueWords = 0;
	for (int i = 0; i < length; ++i)
	{
		std::string currentWord = list[i].word;
		if (currentWord != "")
		{
			totalUniqueWords = totalUniqueWords + list[i].wordCount;
		}
		else
			break;
	}
	return totalUniqueWords;
}

int getMaxValue (wordItem list[], int length, int start)
{
	int max_value = -1;
	int max_index = 0;
	for (int i = start; i < length; ++i)
	{
		int current_value = list[i].wordCount;
		if (max_value < current_value)
		{
			max_value = current_value;
			max_index = i;
		}
	}
	return max_index;
}

void readFileAsText( std::string url, std::stringstream &ss)
{
 	std::ifstream inFile;
 	inFile.open( url );
 	if ( !inFile )
 	{
  		std::cout << "Unable to open file: " << url << std::endl;
  		return;
 	}

 	std::string tmp;
 	while ( getline(inFile,tmp) )
 	{
  		clearPunc(tmp); // Remove if problem
  		lowerCase(tmp);
  		ss << " " << tmp;
 	}
 	inFile.close();
}

int getWordItem (std::string word, wordItem wordList[], int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (word == wordList[i].word)
		{
			return i;
		}
	}
	return -1;
}

// Required
void getStopWords (char* ignoreWordFileName, std::string IgnoreWords[])
{
 	std::ifstream inFile;
 	inFile.open( ignoreWordFileName );
 	if ( !inFile )
 	{
  		std::cout << "Unable to open file: " << ignoreWordFileName << std::endl;
  		return;
 	}

 	std::string tmp;
 	int counter = 0;
 	while ( getline(inFile,tmp) )
 	{
  		if (tmp.size() && tmp[tmp.size()- 1 ] == '\r' )
  		{
  			tmp.resize(tmp.size()- 1 );
  		}
  		IgnoreWords[counter] = tmp;
  		counter++;
 	}
 	inFile.close();
}

bool isStopWord (std::string word, std::string ignoreWords[])
{
	for (int i = 0; i < NUMSTOPWORDS; ++i)
	{
		if (word == ignoreWords[i])
		{
			return true;
		}
	}
	return false;
}

int getTotalNumberStopWords(wordItem list[], int length)
{
	int numWords = 0;
	for (int i = 0; i < length; ++i)
	{
		std::string current_word = list[i].word;
		if (current_word != "" )
		{
			++numWords;
		}
		else
			break;
	}
	return numWords;
}

void arraySort (wordItem list[], int length)
{
	// Start at blank index - use for storage
	// Iterate through array, comparing wordItem.wordCount
		// If wordItem.wordCount for current item is greater than stored, replace it
	for (int i = 0; i < length; ++i)
	{
		int maxIndex = getMaxValue(list,length,i);
		swap(&list[i],&list[maxIndex]);
	}
}

void printTopN (wordItem wordItemList[], int topN)
{
	for (int i = 0; i < topN; ++i)
	{
		std::cout << wordItemList[i].wordCount << " - " << wordItemList[i].word << std::endl;
	}
}

wordItem* doubleArraySize (wordItem oldArray[], int length)
{
	wordItem* newArray = new wordItem[length*2];
	for (int i = 0; i < length; ++i)
	{
		newArray[i].word = oldArray[i].word;
		newArray[i].wordCount = oldArray[i].wordCount;
	}
	delete [] oldArray;
	return newArray;
}

// Main Function
	// argv[0] = name of program
	// argv[1] = N words
	// argv[2] = HungerGames_edit.txt
	// argv[3] = ignoreWords.txt;

int main (int argc, char* argv[])
{
	// Variable Declaration
	int word_limit = atoi(argv [ 1 ]);
	std::ifstream inFile;
	std::stringstream textfile_stream;
	std::stringstream ignorefile_stream;
	std::string stopWords[NUMSTOPWORDS];
	std::string word;
	int wordListCount = 100;
	int arrayDoubleCount = 0;

	// Check
	if ( argc != 4 )
	{
		std::cout << "An insufficient number of parameters has been provided. Terminating program." << std::endl;
		return 1;
	}
	if ( ! argv [ 2 ] || ! argv[ 3 ] )
	{
		std::cout << "Input file is currently inaccessible. Terminating program." << std::endl;
		return 1;
	}

	readFileAsText(argv[ 2 ],textfile_stream);
	readFileAsText(argv [ 3 ],ignorefile_stream);
	getStopWords(argv [ 3 ], stopWords);

	wordItem* wordList = new wordItem[wordListCount];
	
	while(getline(textfile_stream,word,' '))
	{
		if (isStopWord(word,stopWords) || word == "")
		{
			continue;
		}
		else
		{
			int duplicateIndex = getWordItem(word, wordList, wordListCount);
			if (duplicateIndex == -1)
			{
				int i2 = getTotalNumberStopWords(wordList, wordListCount);
				if (i2 >= wordListCount)
				{
					wordList = doubleArraySize(wordList,wordListCount);
					wordListCount = wordListCount*2;
					arrayDoubleCount = arrayDoubleCount + 1;
				}
				wordList[i2].word = word;
				wordList[i2].wordCount = 1;
			}
			else
			{
				++wordList[duplicateIndex].wordCount;
			}
		}
	}
	
	arraySort(wordList,wordListCount);

	printTopN(wordList,word_limit);

	std::cout << "#" << std::endl;
	std::cout << "Array doubled: " << arrayDoubleCount << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Unique non-common words: " << getTotalNumberStopWords(wordList, wordListCount) << std::endl;
	std::cout << "#" << std::endl;
	std::cout << "Total non-common words: " << getTotalNumberWords(wordList,wordListCount) << std::endl;
}

// Output
	// Top N words
	// Quantity of each word
	// Total number of unique words in the file
	// Number of Array Doublings

// Algorithm Process
	// Create ignoreWords from file
	// Create a vector of ignoredWords
	// Open HungerGames file
	// Read one word from the file
		// Compare word to ignoredWords
			// If there is a match, continue
			// If there is no match, compare to wordItemList[]
				// 
				// create new Word Item where word = currentWord and wordCount = 1;