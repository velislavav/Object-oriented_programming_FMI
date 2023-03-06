#include <iostream>
#include <fstream>

int lengthOfFile(const char* filename)
{
	std::ifstream myFile(filename);
	char currentSymbol;
	
	if (!myFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
	}
	int counter = 0;
	while (myFile >> currentSymbol)
	{
		counter++;
	}
	return counter;
	myFile.close();
	
}

int main()
{
	char arr[] = "Test.txt";
	std::cout<<lengthOfFile(arr);
}