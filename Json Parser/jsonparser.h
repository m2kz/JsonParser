#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string.h>
#include "misc.h"


class CodeDepth : public JsonInterpreter
{
public:
	CodeDepth(int) : JsonInterpreter(1){}
protected:
	void interpret(std::string strString, InterpreterStats* statistics);

};


class KeywordsList : public JsonInterpreter
{
public:
	KeywordsList(int) : JsonInterpreter(1){}
protected:
	void interpret(std::string strString, InterpreterStats* statistics);

};

#endif