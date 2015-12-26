#include <iostream>
#include <string.h>
#include "GUI.h"

class CodeDepth;

struct InterpreterStats{ //struktura przechowująca statystyki wejściowego strumienia danych
	int nBrackets;
};

class JsonInterpreter //główna klasa w programie, odpowiedzialna za parsowanie tekstu
{
public:
	JsonInterpreter();
	JsonInterpreter(int){}
	InterpreterStats interpret(std::string strString);
	virtual void interpret(std::string strString, InterpreterStats* statistics){};
private:
	JsonInterpreter *codeDepth;
};

class CodeDepth : public JsonInterpreter //klasa odpowiedzialna za sprawdzenie głębokości zagnieżdżenia kodu
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
	for (; i < strString.length(); i++)
	{
		if (strString.at(i) == '{')
			nOpenBrackets++;
		if (strString.at(i) == '}')
			nCloseBrackets++;
	}
	if (nOpenBrackets == nCloseBrackets)
		statistics->nBrackets = nOpenBrackets + 1;
	else
		statistics->nBrackets = 0xFFFFFFFF;
}

JsonInterpreter::JsonInterpreter() //inicjalizacja klas parsujących
{
	codeDepth = new CodeDepth(1);
}

InterpreterStats JsonInterpreter::interpret(std::string strString)
{
	InterpreterStats statistics = { 0 };
	codeDepth->interpret(strString, &statistics);
	return statistics;
}

void main()
{
	JsonInterpreter interpreter;
	std::string strString;
	InterpreterStats statistics = { 0 };
	strString = "{{{{{}}}}}";
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	JsonParser::GUI	form;
	System::Windows::Forms::Application::Run(%form);

	statistics = interpreter.interpret(strString);

}
