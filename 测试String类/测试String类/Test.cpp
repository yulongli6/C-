#define _CRT_SECURE_NO_DEPRECATE 1

#include<iostream>
#include "crtdefs.h"
#include<vector>
using namespace std;

#if 0
string letterMap[10] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
class Solution {
public:
	void _letterCombinations(const string& digits, vector<string>& vRet, string str, size_t index)
	{
		if (index == digits.size())
		{
			vRet.push_back(str);
			return;
		}
		string letters = letterMap[digits[index] - '0'];
		for (size_t i = 0; i < letters.size(); ++i)
		{

			_letterCombinations(digits, vRet, str + letters[i], index + 1);

		}
	}
	vector<string> letterCombinations(string digits) {
		vector<string> vRet;
		if (digits.empty())
			return vRet;

		string str;
		size_t index = 0;
		_letterCombinations(digits, vRet, str, index);

		return vRet;
	}
};
int main()
{
	string s1("23");
	Solution s;
	vector<string> ret = s.letterCombinations(s1);
	return 0;
}

#endif





int main()
{

	return 0;
}