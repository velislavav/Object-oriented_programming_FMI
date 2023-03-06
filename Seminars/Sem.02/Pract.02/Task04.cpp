#include <iostream>
#include <fstream>

const int MAX_PAIRS = 25;
struct pair {
	int x;
	int y;
};

struct Relation {
	pair relation[MAX_PAIRS];
	int sizerelation = 0;
};

pair CreatePair() 
{
	pair newPair;
	std::cout << "Enter x: ";
	std::cin >> newPair.x;
	std::cout << "Enter y: ";
	std::cin >> newPair.y;
	return newPair;
}

void addPairToRelation(pair& newPair, Relation& relation)
{
	if (relation.sizerelation < MAX_PAIRS)
	{
		relation.relation[relation.sizerelation] = newPair;
		relation.sizerelation++;
	}
	else
	{
		std::cout << "Relation is full!" << std::endl;
	}
}

void writePairToFile(std::ofstream &myFile, pair* relation)
{
	if (!myFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
		return;
	}
	myFile << relation;
	myFile.close();
}



void writeRelationToFile(std::ofstream& myFile, const Relation& relation)
{
	if (!myFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
		return;
	}

	for (int i = 0; i < relation.sizerelation; i++)
	{
		myFile << relation.relation[i].x << " " << relation.relation[i].y << std::endl;
	}

	myFile.close();
}

void readPairFromFile(std::ifstream& sourceFile, const Relation& relation, unsigned int indexOfX)
{
	if (!sourceFile.is_open())
	{
		std::cout << "File is not open!" << std::endl;
		return;
	}

	int x, y;
	sourceFile.seekg(indexOfX) >> x >> y;
	std::cout << x << " " << y << std::endl;
	sourceFile.close();
}
int main()
{
	pair newPair = CreatePair();
	Relation relation;
	addPairToRelation(newPair, relation);
	std::ofstream myFile;
	myFile.open("relation.txt", std::ios::app);
	writeRelationToFile(myFile, relation);
	std::ifstream sourceFile;
	sourceFile.open("relation.txt");
	readPairFromFile(sourceFile, relation, 3);
	return 0;

}
