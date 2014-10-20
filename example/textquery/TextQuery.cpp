#include "TextQuery.h"
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

TextQuery::TextQuery(const string &filename)
{
	readFile(filename);
}

void TextQuery::readFile(const string &filename)
{
	ifstream in;
	in.open(filename.c_str());
	if(!in)
		throw runtime_error("open file error!!\n");

	string line;
	while(getline(in, line))
		_lines.push_back(line);

	in.close();

	for(vector<string>::size_type i = 0; i != _lines.size(); ++ i)
	{
		istringstream is(_lines[i]);
		string word;
		while(is >> word)
			_wordMap[word].insert(i);
	}
}

string TextQuery::runQuery(const string &word) const
{
	map<string, set<Line> >::const_iterator it;
	it = _wordMap.find(word);

	if(it == _wordMap.end())
		return printResult(word, set<Line>());
	else
		return printResult(word, it->second);
}


string TextQuery::printResult(const string &word, const set<Line> &result) const
{
	string ret;
	size_t cnt = result.size();
	char buf[16];
	snprintf(buf, sizeof buf, "%u", cnt);

	ret = word + " occurs " + buf + " times\n";

	for(set<Line>::iterator it = result.begin();
	    it != result.end();
	    ++ it)
	{
		snprintf(buf, sizeof buf, "%u", *it + 1);
		ret += string("line ") + buf + " : ";
		ret += _lines[*it] + "\n";
	}

	return ret;
}
