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
		string line;
		int total = 0;

		while (getline(input, line))
		{
			int first = -1;
			int firstIndex = -1;
			int last = -1;
			int lastIndex = -1;
			for (int i = 0; i < line.length(); ++i)
			{
				int value = line[i] - '0';

				if (value > 0 && value < 10)
				{
					if (first == -1)
					{
						first = value;
						firstIndex = i;
					}

					last = value;
					lastIndex = i;
				}
			}

			// Check for Strings from first
			size_t index = line.find("one");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 1;
					firstIndex = index;
				}
			}

			index = line.find("two");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 2;
					firstIndex = index;
				}
			}

			index = line.find("three");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 3;
					firstIndex = index;
				}
			}

			index = line.find("four");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 4;
					firstIndex = index;
				}
			}

			index = line.find("five");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 5;
					firstIndex = index;
				}
			}

			index = line.find("six");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 6;
					firstIndex = index;
				}
			}

			index = line.find("seven");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 7;
					firstIndex = index;
				}
			}

			index = line.find("eight");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 8;
					firstIndex = index;
				}
			}

			index = line.find("nine");
			if (index != string::npos)
			{
				if (firstIndex == -1 || index < firstIndex)
				{
					first = 9;
					firstIndex = index;
				}
			}

			// Check for Strings from last
			index = line.rfind("one");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 1;
					lastIndex = index;
				}
			}

			index = line.rfind("two");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 2;
					lastIndex = index;
				}
			}

			index = line.rfind("three");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 3;
					lastIndex = index;
				}
			}

			index = line.rfind("four");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 4;
					lastIndex = index;
				}
			}

			index = line.rfind("five");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 5;
					lastIndex = index;
				}
			}

			index = line.rfind("six");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 6;
					lastIndex = index;
				}
			}

			index = line.rfind("seven");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 7;
					lastIndex = index;
				}
			}

			index = line.rfind("eight");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 8;
					lastIndex = index;
				}
			}

			index = line.rfind("nine");
			if (index != string::npos)
			{
				if (lastIndex == -1 || index > lastIndex)
				{
					last = 9;
					lastIndex = index;
				}
			}

			total += first * 10 + last;
		}

		output << total;
	}
};

DayOne g_dayOne = DayOne();
