#ifndef _CRGHEADER_H
#define _CRGHEADER_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>


class ReferenceMap
{
	public:
		std::map<std::string, std::vector<int>> variables;
		std::set<std::string> notvariables;
		friend std::ostream& operator<<(std::ostream& os,std::map<std::string,std::vector<int>>::iterator& st);
		friend std::ostream& operator<<(std::ostream& os, std::set<std::string>::iterator& st);
		void addTypedefs();
		void createReservedWordsSet(std::string inputFile);


};

int detectLanguage(std::string inputFile);
std::string obtainFileExtension(std::string inputFile);



#endif