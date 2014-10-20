#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <string>
#include <map>
#include <set>
#include <vector>

class TextQuery
{
public:
	typedef std::vector<std::string>::size_type Line;

	TextQuery(const std::string &filename);
	void readFile(const std::string &filename);
	std::string runQuery(const std::string &word) const;
	std::string printResult(const std::string &word, const std::set<Line> &result) const ;

private:
	std::vector<std::string> _lines;
	std::map<std::string, std::set<Line> > _wordMap;
};

#endif  /*TEXT_QUERY_H*/
