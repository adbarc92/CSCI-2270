// Give it a file, return text as string

// Ben's Original ReadFileAsText

// std::string readFileAsText( std::string url )
// {
//  	std::ifstream ifs;
//  	ifs.open( url );
//  	if ( !ifs )
//  	{
//   		std::cout << "Unable to open file: " << url << std::endl;
//   		return "";
//  	}

//  	std::string ret = "";
//  	while ( !ifs.eof() )
//  	{
//   		std::string tmp;
//   		getline( ifs, tmp );
//   		ret += tmp;
//  	}
//  	ifs.close();
//  	return ret;
// }

// Ben's Modified ReadFileAsText

// void readFileAsText( std::string url, std::stringstream &ss)
// {
//  	std::ifstream inFile;
//  	inFile.open( url );
//  	if ( !inFile )
//  	{
//   		std::cout << "Unable to open file: " << url << std::endl;
//   		return;
//  	}

//  	std::string tmp;
//  	while ( getline(inFile,tmp) )
//  	{
//   		clearPunc(tmp); // Remove if problem
//   		lowerCase(tmp);
//   		ss << " " << tmp;
//  	}
//  	inFile.close();
// }