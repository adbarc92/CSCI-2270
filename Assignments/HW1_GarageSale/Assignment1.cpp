#include <iostream>
#include <fstream>
#include <sstream>

// Each struct represents an item, which consists of type, price, and buyer/seller
struct Item
{
	std::string type;
	bool BuySell; // Buyer=True, Seller=False
	std::string price;
};

int main()
{
	// Variable Declaration
	Item messageBoard[100]; // Creates array of Items; Remember: Arrays are also inherently pointers
	Item itemsSold[100];
	std::ifstream inFile;
	std::string currentLine;
	int itemCount = 0;
	
	inFile.open("garageSale.txt"); // Opens File
	
	if (inFile.fail()) // Check if file successfully opened; if not, display error message
	{
		std::cout << "File Failed to Open" << std::endl;
	}
	else
	{
		std::cout << "File Opened Successfully" << std::endl;
		while (getline(inFile,currentLine))
		{
			std::stringstream currentItem(currentLine);
			std::string currentItemType, currentItemPrice, currentItemBS = "";
			bool currentItemBuySell = true;
			getline(currentItem,currentItemType, ',');
			getline(currentItem,currentItemBS, ',');
			if (currentItemBS == " for sale") // Seller
			{
				currentItemBuySell = false;
			}
			else if (currentItemBS == " wanted") // Buyer
			{
				currentItemBuySell = true;
			}
			getline(currentItem,currentItemPrice, ',');		
			for (int i = 0; i < itemCount+1; ++i)
			{
				// If there is a match
				if (currentItemType == messageBoard[i].type)
				{
					// If the current item is being sold, and the matching item is not being sold
					if (currentItemBuySell == false && currentItemBuySell != messageBoard[i].BuySell)
					{
						// If the buyer's budget is greater than or equal to the seller's price
						if (stoi(currentItemPrice) >= stoi(messageBoard[i].price))
						{
							// Remove both items from the board and print them
							itemsSold[i].type = messageBoard[i].type;
							itemsSold[i].price = messageBoard[i].price;
							itemsSold[i].BuySell = messageBoard[i].BuySell;
							std::cout << messageBoard[i].type << " " << messageBoard[i].price << std::endl;
							(messageBoard[i].type).clear();
							(messageBoard[i].price).clear();
							break;
						}
					}
				}
				else
				{
					while((messageBoard[i].type).empty() == false && (messageBoard[i].price).empty() == false)
					{
						i = i + 1;
					}
					messageBoard[i].type = currentItemType;
					messageBoard[i].price = currentItemPrice;
					messageBoard[i].BuySell = currentItemBuySell;
					itemCount = itemCount + 1;
				}
			}
		}
		std::cout << "Items sold." << std::endl;
		std::cout << "Items remaining in the message board after reading all lines in the file." << std::endl;
		for (int i = 0; i < 100; ++i)
		{
			if (messageBoard[i].BuySell == false) // Seller Case
			{
				std::cout << messageBoard[i].type << ", " << "for sale" << ", " << messageBoard[i].price << std::endl;
			}
		}
		for (int i = 0; i < 100; ++i)
		{
			if (messageBoard[i].BuySell == true) // Buyer Case
			{
				std::cout << messageBoard[i].type << ", " << "wanted" << ", " << messageBoard[i].price << std::endl;
			}
		}
	}
	return 0;
}