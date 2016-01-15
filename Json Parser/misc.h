#ifndef MISC_H
#define MISC_H
#include <vector>

typedef struct {
	int nBrackets;
	std::vector<std::string> KeywordsList;
} InterpreterStats;

class JsonInterpreter
{
public:
	JsonInterpreter();
	JsonInterpreter(int){}
	InterpreterStats interpret(std::string strString);
	virtual void interpret(std::string strString, InterpreterStats* statistics){};
private:
	JsonInterpreter *codeDepth;
	JsonInterpreter *keywordsList;
};

extern InterpreterStats statistics;
extern JsonInterpreter interpreter;
#endif