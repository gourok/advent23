#include <Helpers.h>
#include <DayBase.h>

/**
* DayOne
*
* This is a the solution for Day Template of Advent of Code 2023.
* https://adventofcode.com/2023/day/1
*
*/
class DayTwo : public DayBase
{
public:
	DayTwo()
		: DayBase(2)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		const int kBlue = 14;
		const int kRed = 12;
		const int kGreen = 13;
		// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
		string line;
		int total = 0;
		while (getline(input, line))
		{
			stringstream ss(line);
			string color;
			int count;
			int game;
			ss >> color; // "Game"
			ss >> game >> color;
			bool valid = true;
			while (valid && ss >> count >> color)
			{
				switch(color[0])
				{
				case 'b':
					valid = count <= kBlue;
					break;
				case 'r':
					valid = count <= kRed;
					break;
				case 'g':
					valid = count <= kGreen;
					break;
				default:
					output << "unknown " << color << endl;
				}
			}
			if (valid)
			{
				total += game;
			}
		}
		output << total << endl;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
		string line;
		int total = 0;
		while (getline(input, line))
		{
			stringstream ss(line);
			string color;
			int count;
			int game;
			ss >> color; // "Game"
			ss >> game >> color;
			int blue = 0, red = 0, green = 0;
			while (ss >> count >> color)
			{
				switch(color[0])
				{
				case 'b':
					blue = max(blue, count);
					break;
				case 'r':
					red = max(red, count);
					break;
				case 'g':
					green = max(green, count);
					break;
				default:
					output << "unknown " << color << endl;
				}
			}
			total += red * blue * green;
		}
		output << total << endl;
	}
};

DayTwo g_dayTwo = DayTwo();
