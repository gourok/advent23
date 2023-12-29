#include <Helpers.h>
#include <DayBase.h>

#include <vector>
/**
* DayOne
*
* This is a the solution for Day Template of Advent of Code 2023.
* https://adventofcode.com/2023/day/1
*
*/
class DayThree : public DayBase
{
public:
	DayThree()
		: DayBase(3)
	{}

protected:
	bool is_num(const vector<string>& grid, int x, int y){
		if (y < 0 || y >= grid.size()) return false;
		if (x < 0 || x >= grid[0].length()) return false;
		return (grid[y][x] >= '0' && grid[y][x] <= '9');
	}

	bool is_part(const vector<string>& grid, int x, int y){
		if (y < 0 || y >= grid.size()) return false;
		if (x < 0 || x >= grid[0].length()) return false;
		if (grid[y][x] >= '0' && grid[y][x] <= '9') return false;
		return grid[y][x] != '.';
	}

	virtual void questionOne(istream& input, ostream& output)
	{
		vector<string> grid;
		string line;
		while (getline(input, line))
		{
			grid.push_back(line);
		}
		int total = 0;
		for (int y = 0; y < grid.size(); ++y)
		{
			for(int x = 0; x < grid[y].length(); ++x)
			{
				int value = 0;
				int has_part = false;
				while(is_num(grid, x, y))
				{
					for (int dx = -1; dx <=1; ++dx)
					{
						for (int dy = -1; dy <= 1; ++dy)
						{
							has_part |= is_part(grid, x + dx, y + dy);
						}
					}
					value *= 10;
					value += grid[y][x] - '0';
					++x;
				}
				if (has_part) {
					// if (value) output << value << endl;
					total += value;
				}
			}
		}
		output << total << endl;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		int total = 0;
		vector<string> grid;
		string line;
		while (getline(input, line))
		{
			grid.push_back(line);
		}
		vector<int> numbers;
		vector<vector<int>> adjusted_grid;
		const int kOther = -1;
		const int kStar = -2;
		adjusted_grid.resize(grid.size());
		for (int y = 0; y < grid.size(); ++y)
		{
			adjusted_grid[y].resize(grid[y].length(), 0);
			for (int x = 0; x < grid[y].length(); ++x)
			{
				int value = 0;
				int dx = 0;
				if (is_num(grid, x, y))
				{
					while(is_num(grid, x + dx, y))
					{
						value *= 10;
						value += grid[y][x+dx] - '0';
						++dx;
					}
					numbers.push_back(value);
					while(dx--)
					{
						adjusted_grid[y][x++] = numbers.size() - 1;
					}
					--x;
				}
				else
				{
					adjusted_grid[y][x] = (grid[y][x] == '*' ? kStar : kOther);
				}
				//output << adjusted_grid[y][x] << ' ';
			}
			//output << endl;
		}
		for (int y = 0; y < adjusted_grid.size(); ++y)
		{
			for (int x = 0; x < adjusted_grid[y].size(); ++x)
			{
				if (adjusted_grid[y][x] == kStar)
				{
					set<int> found_numbers;
					for (int dx = -1; dx <= 1; ++dx)
					{
						for (int dy = -1; dy <= 1; ++dy)
						{
							int cx = x + dx;
							int cy = y + dy;
							if (cy >= 0 && cy < adjusted_grid.size()
									&& cx >= 0 && cx < adjusted_grid[cy].size()
									&& adjusted_grid[cy][cx] >= 0) {
								found_numbers.insert(adjusted_grid[cy][cx]);
							}
						}
					}
					if (found_numbers.size() > 2) {
						output << "Error!!" << endl;
					}
					if (found_numbers.size() == 2)
					{
						total += numbers[*found_numbers.begin()] * numbers[*found_numbers.rbegin()];
					}
				}
			}
		}
		output << total;
	}
};

DayThree g_dayThree = DayThree();
