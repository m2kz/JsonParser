#include <regex>
#include <iostream>
#include "GUI.h"
#include "jsonparser.h"


class CodeDepth;
class KeywordsList;

InterpreterStats statistics = { 0 };
JsonInterpreter interpreter;


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



void KeywordsList::interpret(std::string strString, InterpreterStats* statistics)
{
	std::vector<std::string> collection;
	std::regex keywordPattern("(\"\\S*\":)+\\s*(\"\\S*\")?");
	std::smatch result;
	std::string temp;

	for (std::sregex_iterator i = std::sregex_iterator(strString.begin(), strString.end(), keywordPattern);
		i != std::sregex_iterator();
		++i)
	{
		std::smatch m = *i;
		temp = m.str();
		temp = temp.substr(1, temp.size() - 2);
		temp.erase(std::remove(temp.begin(), temp.end(), '\"'), temp.end());
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
	//std::string strString;
	//strString = "\"derp\": \"herp\": \"durp\":";

	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	JsonParser::GUI	form;
	System::Windows::Forms::Application::Run(%form);

}
