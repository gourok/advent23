#include <Helpers.h>
#include <DayBase.h>

/**
* DayOne
*
* This is a the solution for Day Template of Advent of Code 2023.
* https://adventofcode.com/2023/day/1
*
*/
class DayOne : public DayBase
{
public:
	DayOne()
		: DayBase(1)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		string line;
		int total = 0;

		while (getline(input, line))
		{
			int first = -1;
			int last = -1;
			for (int i = 0; i < line.length(); ++i)
			{
				int value = line[i] - '0';

				if (value > 0 && value < 10)
				{
					if (first == -1)
					{
						first = value;
					}

					last = value;
				}
			}
			
			total += first * 10 + last;
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{

	}
};

DayOne g_dayOne = DayOne();
