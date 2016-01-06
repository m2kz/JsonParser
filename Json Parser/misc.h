#include <vector>

struct InterpreterStats{
	int nBrackets;
	std::vector<std::string> KeywordsList;
};

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