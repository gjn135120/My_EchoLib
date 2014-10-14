#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

class Exception : public std::exception
{
public:
	explicit Exception(const char *);
	explicit Exception(const std::string &);
	virtual ~Exception() throw();
	virtual const char *what() const throw();
	const char *stackTrace() const throw();

private:
	void fillStackTrace();
	std::string demangle(const char *symbol);

	std::string _message;
	std::string _stack;
};
#endif  /*EXCEPTION_H*/
