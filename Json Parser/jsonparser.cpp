#include <iostream>
#include <string.h>
#include <regex>
#include <vector>
#include "GUI.h"

class CodeDepth;
class KeywordsList;

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

class CodeDepth : public JsonInterpreter
{
public:
	CodeDepth(int) : JsonInterpreter(1){}
protected:
	void interpret(std::string strString, InterpreterStats* statistics);

};

void CodeDepth::interpret(std::string strString, InterpreterStats* statistics)
{
	unsigned int i = 0;
	int nOpenBrackets = 0;
	int nCloseBrackets = 0;
	int codeDepth = 0;
	bool depthControl = true;
	for (; i < strString.length(); i++)
	{
		if (strString.at(i) == '{')
		{
			nOpenBrackets++;
			depthControl = true;
		}
		if (strString.at(i) == '}')
		{
			nCloseBrackets++;
			if (depthControl == true)
			{
				depthControl = false;
			}
			else
				codeDepth++;
		}

	}
	if (depthControl == false)
		codeDepth++;
	if (nOpenBrackets == nCloseBrackets)
		statistics->nBrackets = codeDepth;
	else
		statistics->nBrackets = 0xFFFFFFFF;
}

class KeywordsList : public JsonInterpreter
{
public:
	KeywordsList(int) : JsonInterpreter(1){}
protected:
	void interpret(std::string strString, InterpreterStats* statistics);

};

void KeywordsList::interpret(std::string strString, InterpreterStats* statistics)
{
	std::vector<std::string> collection;
	std::regex keywordPattern("\"\\s*([^\"]*)\\s*\":");
	std::smatch result;
	std::string temp;
	//std::regex_search(strString, result, keywordPattern);
	for (std::sregex_iterator i = std::sregex_iterator(strString.begin(), strString.end(), keywordPattern);
		i != std::sregex_iterator();
		++i)
	{
		std::smatch m = *i;
		temp = m.str();
		temp = temp.substr(1, temp.size() - 3);
		collection.push_back(temp);
	}
	statistics->KeywordsList = collection;
}

JsonInterpreter::JsonInterpreter()
{
	codeDepth = new CodeDepth(1);
	keywordsList = new KeywordsList(1);
}

InterpreterStats JsonInterpreter::interpret(std::string strString)
{
	InterpreterStats statistics = { 0 };
	codeDepth->interpret(strString, &statistics);
	keywordsList->interpret(strString, &statistics);
	return statistics;
}

void main()
{
	JsonInterpreter interpreter;
	std::string strString;
	InterpreterStats statistics = { 0 };
	strString = "\"derp\": \"herp\": \"durp\":";
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	JsonParser::GUI	form;
	System::Windows::Forms::Application::Run(%form);

	statistics = interpreter.interpret(strString);

}
