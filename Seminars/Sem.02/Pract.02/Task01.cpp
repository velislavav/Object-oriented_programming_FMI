#include <iostream>
#include <fstream>

void enterSumAndProduct(const int& num1, const int& num2, const int& num3)
{
	std::ofstream myFile("result.txt");
	if (!myFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
	}
	myFile << num1+num2+num3 << std::endl;
	myFile << num1 * num2 * num3 << std::endl;
	myFile.close();
}

void readDifference()
{
	std::ifstream myFile("result.txt");
	if (!myFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
	}
	double sum, product;
	myFile >> sum >> product;
	std::cout << sum - product;
	myFile.close();
}

int main()
{
	double num1, num2, num3;
	std::cout << "Enter 3 numbers: ";
	std::cin >> num1 >> num2 >> num3;
	enterSumAndProduct(num1, num2, num3);
	readDifference();
}
