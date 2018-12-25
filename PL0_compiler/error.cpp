#include "stdafx.h"
#include "base.h"
#include "error.h"
#include <iostream>
#include <string>
using namespace std;
string err_str[35] = {
	"",
	"should be \':=\'",
	"should be number after \'=\'",
	"shoule be \'=\'",
	"should be identifier after const,var,procedure",
	"\';\'or\'.\' is missing",
	"wrong symbol after procedure delaration",
	"should be statement starter",
	"wrong symbol after the statement",
	"\'.\' is missing",
	"\';\' is missing",
	"undeclared identifer",
	"should be a variable",
	"should be \':=\'",
	"should be a identifer name after \"call\"",
	"should be a procedure name after \"call\"",
	"\"then\" is missing",
	"\"end\" or \';\' is missing",
	"\"do\" is missing",
	"wrong symbol after \'.\'",
	"should be relation operator",
	"cannot be a procedure kind",
	"\')\' is missing",
	"wrong symbol after factors",
	"it cannot be an expression starter",
	"the number is too big",
	"too many levels",
	"should be \')\'",
	"",
	"",
	"",
	"",
	"",
	"",
	""
};
void error(int n)
{
	if (err < ERRMAX)
	{
		err_msg[err].type = n;
		err_msg[err].info = err_str[n];
		err_msg[err].lineNum = linecnt;
		err_msg[err++].charNum = cc - 1;
	}
}
