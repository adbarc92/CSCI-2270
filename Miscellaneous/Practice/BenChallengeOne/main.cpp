// Prompt:
	// Read in a time series (csv of double, delineated by \n)
	// 1. Be able to calculate a simple moving average
		// For each in time series, output vector of same size
		// Calculate moving average; 0
	// 2. Find the median, sum
	// 3. Go through each point in moving average, set equal to sum divided by median times the percent change of the simple moving average
	// 4. Write output to disc as new file

#include <iostream>
#include <vector>
#include <fstream>

double findSum( std::vector< double >& timeSeries )
{
	double sum = 0;

	for ( unsigned int i = 0; i < timeSeries.size(); ++i )
	{
		sum += timeSeries[ i ];
	}

	return sum;
}

double findMedian( std::vector< double >& timeSeries )
{
		int size = timeSeries.size();
		double median;

		if ( size%2 != 0 )
		{
			median = timeSeries[ size/2 + 1 ];
		}
		else
		{
			median = ( ( timeSeries[ size/2 ] + timeSeries[ size/2 + 1 ]) / 2 );
		}

		return median;
}

double percentChange( int first, int second )
{
	double percentChange = 0;
	int change = 0;

	if ( first > second ) // Decrease
	{
		change = first - second;
		percentChange = change/first;
	}
	else // Increase
	{
		change = second - first;
		percentChange = change/first;
	}

	return percentChange;

}

std::vector< double> findMovingMean( std::vector< double >& timeSeries, int split)
{
	std::vector< double > movingMean;
	double curMean = 0;
	double sum = 0;
	int size = timeSeries.size();

	for ( int i = 0; i < size; ++i )
	{
		if ( i < split )
		{
			movingMean.push_back( 0 );
			continue;
		}

		for ( int j = i - split; j < i; ++j )
		{
			sum += timeSeries[ j ];
		}

		curMean = sum / split;
		std::cout << "Current Mean: " << curMean << std::endl;
		movingMean.push_back( curMean );
		sum = 0;
	}

	return movingMean;

}

void generateVector( int len, std::vector< double >& out )
{
	for( int i = 0; i < len; i++ )
	{
		out.push_back( i );
	}
}

void readVector( std::vector< double >& out )
{
	std::fstream inFile;
	std::string tmpStr;
	std::vector< double > timeSeries;
	std::vector< double > movingMean;

	inFile.open( "doubles.csv" );

	if ( !inFile )
	{
		std::cout << "File cannot be found" << std::endl;
		throw std::runtime_error( "File cannot be found." ); 
	}

	while ( getline( inFile, tmpStr ) )
	{
		std::cout << "Adding: " << tmpStr << std::endl;
		timeSeries.push_back( std::stod( tmpStr ) );
	}

	inFile.close();
}

int main()
{
	int split = 5;
	std::vector< double > timeSeries;
	//readVector( timeSeries );
	generateVector( 10, timeSeries );

	std::vector< double > sma = findMovingMean( timeSeries, split );

	std::cout << "SIMPLE MOVING AVG:" << std::endl;
	for( unsigned int i = 0; i < sma.size(); i++ )
	{
		double v = sma[ i ];
		std::cout << i << ": " << v << std::endl;
	}

	// std::ofstream outFile;
	// outFile.open( "output.txt" );

	// std::vector< double > adjustedData;

	// for ( unsigned int i = 0; i < movingMean.size(); ++i )
	// {
	// 	if ( i == 0 )
	// 	{
	// 		percentChange = 1;
	// 		curNum = sum/median * percentChange;
	// 		adjustedData.push_back( curNum );
	// 	}

	// 	else
	// 	{
	// 		percentChange = (movingMean[ i ] / movingMean[ i - 1 ]) - 1;
	// 		curNum = sum/median * movingMean[ i ];
	// 		adjustedData.push_back( curNum );
	// 	}
	// }

	// for ( unsigned int i = 0; i < adjustedData.size(); ++i )
	// {
	// 	outFile << adjustedData[ i ] << "\n";
	// }

	return 0;
}