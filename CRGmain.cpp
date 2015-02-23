#include "CRGHeader.h"

int main(void)
{
	ReferenceMap h;


	std::ifstream textFile;
	textFile.open("CRGfunct.cpp");
	h.createReservedWordsSet("CRGfunct.cpp");
	std::string line;
	int lineNum = 1;
	if (textFile.is_open())
	{
		//cycle through file line by line
		while (getline(textFile, line))
		{
			//if the line is a library include, skip to the next line
			if (line.find("#include") != std::string::npos)
			{
				lineNum++;
				continue;
			}
			//set line position placeholder after line numbers
			int position = 0;
			while (isdigit(line[position]) || line[position] == '\t')
			{
				position++;
			}

			//cycle through line to the end
			while (position != line.length())
			{
				//move to the beginning of a "word"
				while (!isalnum(line[position]) && line[position] != '_' && position != line.length())
				{
					position++;

					//skip characters in a string ("")
					if (line[position] == '\"'){
						position++;
						while (line[position] != '\"')
						{
							position++;
						}
					}

					//skip to the next line if line comment is reached
					if (line[position - 1] == '/' && line[position] == '/'){
						position = line.length();
						continue;
					}
				}

				//load the "word" into a variable
				std::string word;
				while (isalnum(line[position]) || line[position] == '_' && position != line.length())
				{
					word.push_back(line[position]);
					position++;
				}
				
				//limitations, check if word is a function name, a number, or just an empty string
				if (line[position] != '(' && !isdigit(word[0]) && word != "")
				{
					//check if word is in the non-variable
					std::set<std::string>::iterator it = h.notvariables.find(word);
					std::vector<int> lineNumber;
					lineNumber.push_back(lineNum);
					//if the word is not a reserved word than place it in the map with line number 
					if (it == h.notvariables.end())
					{
						std::map<std::string,std::vector<int> >::iterator varIt = h.variables.find(word);
						if (varIt != h.variables.end())
						{
							varIt->second.push_back(lineNum);
						}
						else
							h.variables.insert(std::pair<std::string, std::vector<int>>(word, lineNumber));
					}
				}
			}
			lineNum++;
		}
		//creates an iterator to move through the map
		std::map<std::string, std::vector<int>>::iterator it = h.variables.begin();
		for (; it != h.variables.end(); ++it)
		{
			std::cout << it << std::endl;
		}

		//creates an iterator to move through the multi-map
		std::set<std::string>::iterator setIT = h.notvariables.begin();
		for (; setIT != h.notvariables.end(); ++setIT)
		{
			std::cout << setIT << std::endl;
		}
	}
	//close the file stream
	textFile.close();

	system("pause");
	return 0;
	
}
