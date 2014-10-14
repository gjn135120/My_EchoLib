#include "Exception.h"
#include <cxxabi.h>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
using namespace std;

Exception::Exception(const char *s)
	:_message(s)
{
	fillStackTrace();
}

Exception::Exception(const std::string &s)
	:_message(s)
{
	fillStackTrace();
}

Exception::~Exception() throw()
{

}

const char *Exception::what() const throw()
{
	return _message.c_str();
}
const char *Exception::stackTrace() const throw()
{
	return _stack.c_str();
}

void Exception::fillStackTrace()
{
	const int len = 200;
	void *buf[len];
	int n = ::backtrace(buf, len);
	char **strings = ::backtrace_symbols(buf, len);
	if(strings)
	{
		for(int i = 0; i < n; ++ i)
		{
			_stack.append(demangle(strings[i]));
			_stack.push_back('\n');
		}
		free(strings);
	}
}

string Exception::demangle(const char *symbol)
{
	size_t size;
	int status;
	char tmp[128];
	char *demangled;
	if(1 == sscanf(symbol, "%*[^(]%*[^_]%127[^)+]", tmp))
	{
		if(NULL != (demangled = abi::__cxa_demangle(tmp, NULL, &size, &status)))
		{
			string result(demangled);
			free(demangled);
			return result;
		}
	}

	if(1 == sscanf(symbol, "%127s", tmp))
		return tmp;

	return symbol;
}
