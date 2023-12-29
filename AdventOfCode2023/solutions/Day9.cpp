#include <Helpers.h>
#include <DayBase.h>

/**
* DayNine
*
* This is a the solution for Day Nine of Advent of Code 2023.
* https://adventofcode.com/2023/day/9
*
*/
class DayNine : public DayBase
{
public:
	DayNine()
		: DayBase(9)
	{}

private:
	int calculateNextValue(const vector<int>& values)
	{
		vector<int> newValues;
		for (int i = 0; i < values.size() - 1; ++i)
		{
			int result = values[i + 1] - values[i];
			newValues.push_back(result);
		}

		bool isZeroes = true;
		for (int i = 0; i < newValues.size(); ++i)
		{
			if (newValues[i] != 0)
			{
				isZeroes = false;
				break;
			}
		}

		if (isZeroes)
			return values[0];

		return values.back() + calculateNextValue(newValues);
	}

	int calculatePreviousValue(const vector<int>& values)
	{
		vector<int> newValues;
		for (int i = 0; i < values.size() - 1; ++i)
		{
			int result = values[i + 1] - values[i];
			newValues.push_back(result);
		}

		bool isZeroes = true;
		for (int i = 0; i < newValues.size(); ++i)
		{
			if (newValues[i] != 0)
			{
				isZeroes = false;
				break;
			}
		}

		if (isZeroes)
			return values[0];

		return values.front() - calculatePreviousValue(newValues);
	}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		int total = 0;
		string line;
		while (getline(input, line))
		{
			vector<string> valueStrings = splitString(line, " ");

			vector<int> values;
			for (string valueString : valueStrings)
			{
				values.push_back(atoi(valueString.c_str()));
			}
			int value = calculateNextValue(values);
			total += value;
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		int total = 0;
		string line;
		while (getline(input, line))
		{
			vector<string> valueStrings = splitString(line, " ");

			vector<int> values;
			for (string valueString : valueStrings)
			{
				values.push_back(atoi(valueString.c_str()));
			}
			int value = calculatePreviousValue(values);
			total += value;
		}

		output << total;
	}
};

DayNine g_dayNine = DayNine();
