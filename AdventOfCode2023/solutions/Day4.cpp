#include <Helpers.h>
#include <DayBase.h>

/**
* DayFour
*
* This is a the solution for Day Four of Advent of Code 2023.
* https://adventofcode.com/2023/day/4
*
*/
class DayFour : public DayBase
{
public:
	DayFour()
		: DayBase(4)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		string line;

		int total = 0;

		while (getline(input, line))
		{
			int value = 0;
			int winningStart = line.find_first_of(':') + 2;
			int winningEnd = line.find_first_of('|');
			vector<string> winning = splitString(line.substr(winningStart, winningEnd - winningStart), " ");

			int playingStart = winningEnd + 2;
			vector<string> playing = splitString(line.substr(playingStart), " ");

			for (string number : playing)
			{
				if (number.length() == 0)
					continue;

				for (string winNumber : winning)
				{
					if (winNumber.length() == 0)
						continue;

					if (number.compare(winNumber) == 0)
					{
						if (value == 0)
						{
							value = 1;
						}
						else
						{
							value *= 2;
						}
					}
				}
			}

			total += value;
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		string inputLine;

		int total = 0;

		vector<string> lines;
		vector<int> count;

		while (getline(input, inputLine))
		{
			lines.emplace_back(inputLine);
			count.emplace_back(1);
		}

		for (int i = 0; i < lines.size(); ++i)
		{
			string line = lines[i];
			int value = 0;
			int winningStart = line.find_first_of(':') + 2;
			int winningEnd = line.find_first_of('|');
			vector<string> winning = splitString(line.substr(winningStart, winningEnd - winningStart), " ");

			int playingStart = winningEnd + 2;
			vector<string> playing = splitString(line.substr(playingStart), " ");

			for (string number : playing)
			{
				if (number.length() == 0)
					continue;

				for (string winNumber : winning)
				{
					if (winNumber.length() == 0)
						continue;

					if (number.compare(winNumber) == 0)
					{
						value++;
					}
				}
			}

			total += count[i];

			for (int c = i + 1; c < i + value + 1; c++)
			{
				if (c >= count.size())
					break;

				count[c] += count[i];
			}
		}

		output << total;
	}
};

DayFour g_dayFour = DayFour();
