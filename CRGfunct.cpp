#include "CRGHeader.h"

using namespace std;

enum typeStr{ C, CPP, JAVA };




int detectLanguage(string inputFile)
{
	string fileExtension = obtainFileExtension(inputFile);

	//find which language is used by checking file extension
	if (fileExtension == "c" || fileExtension == "h")
	{
		return C;
	}
	else if (fileExtension == "cpp" || fileExtension == "hpp")
	{
		return CPP;
	}
	else if (fileExtension == "java" || fileExtension == "class")
	{
		return JAVA;
	}
	else
	{
		return -1;
	}
}

//overload the "<<" to print a ReferenceMap object iterator
ostream& operator<<(ostream& os, map<string,std::vector<int> >::iterator& st)
{
	
	os << st->first.data() << " ";
	for (std::vector<int>::iterator it = st->second.begin(); it != st->second.end(); it++)
		os << *it << " ";
	os << std::endl;
	return os;
}


ostream& operator<<(ostream& os, set<string >::iterator& st)
{
	os << *st << std::endl;
	return os;
}


//obtains the file extension of the input file
string obtainFileExtension(string inputFile)
{
	//set iterator to beginning of file extension
	int stringIterator = inputFile.find(".") + 1;
	string fileExtension;

	//add file extension of input file to independant variable fileExtension
	while (stringIterator < inputFile.length())
	{
		fileExtension.push_back(inputFile[stringIterator]);
		stringIterator++;
	}
	return fileExtension;
}

void ReferenceMap::createReservedWordsSet(string inputFile)
{
	

	//reserved words in the C language, and in header files
	vector<string> reservedWords_C = { "_Packed", "auto", "break", "case", "char", "const", "continue", "default",
		"do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
		"register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
		"typedef", "union", "unsigned", "void", "volatile", "while", "NULL" };

	//reserved words in the C++ language
	vector<string> reservedWords_CPP = { "auto", "bool", "break", "case", "catch", "char", "class", "const", "endl",
		"const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else",
		"enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline",
		"int", "long", "mutable", "namespace", "new", "nullptr", "operator", "private", "protected", "void",
		"public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "using",
		"static_assert", "static_cast", "struct", "switch", "template", "this", "throw", "true", "try", "NULL",
		"typedef", "typeid", "typename", "union", "unsigned", "virtual", "volatile", "wchar_t", "while", "cin",
		"cout", "std", "string", "list", "set", "vector", "ifstream", "ostream" };

	//reserved words in the Java language
	vector<string> reservedWords_JAVA = { "abstract", "assert", "boolean", "break", "byte", "case", "catch",
		"const*", "continue", "default", "double", "do", "else", "enum", "extends", "false", "class",
		"final", "finally", "float", "for", "goto*", "if", "implements", "import", "instanceof",
		"int", "interface", "long", "native", "new", "null", "package", "private", "protected", "throw",
		"public", "return", "short", "static", "strictfp", "super", "switch", "synchronized", "this",
		"throws", "transient", "true", "try", "void", "volatile", "char", "while", "NULL" };

	//word count holds the number of words each reserved words banks
	int wordCount = 0;

	//loads the proper word bank for the input file
	switch (detectLanguage(inputFile))
	{
	case C:
		wordCount = 34;
		if (notvariables.empty())
		{
			for (int i = 0; i < wordCount; i++)
			{
				notvariables.insert(reservedWords_C[i]);
			}
		}
		break;
	case CPP:
		wordCount = 76;
		if (notvariables.empty())
		{
			for (int i = 0; i < wordCount; i++)
			{
				notvariables.insert(reservedWords_CPP[i]);
			}
		}
		break;
	case JAVA:
		wordCount = 53;
		if (notvariables.empty())
		{
			for (int i = 0; i < wordCount; i++)
			{
				notvariables.insert(reservedWords_JAVA[i]);
			}
		}
		break;
	default:
		break;
	}
	//find and load typedefs into the map
	addTypedefs();
}

//adds typedefs to the non-variable set
void ReferenceMap::addTypedefs()
{
	//open numbered output file
	ifstream file;
	file.open("output.txt");
	if (file.is_open()){
		//cycle through all lines, searching for keyword typedef
		string line;
		while (getline(file, line))
		{
			if (line.find("typedef") != string::npos)
			{
				//if/when found, read from the last ' ' on the line to the ';'
				string typedefDataType;
				int linePosition = line.rfind(' ') + 1;
				while (isalnum(line[linePosition]) || line[linePosition] == '_')
				{
					typedefDataType.push_back(line[linePosition]);
					linePosition++;
				}
				std::vector<int> lineNumber; 
				lineNumber.push_back(linePosition);
				//insert the typedef into the map
				variables.insert(std::pair<std::string, std::vector<int>>(typedefDataType, lineNumber));
			}
		}
		file.close();
	}
}

