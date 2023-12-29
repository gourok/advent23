#include <Helpers.h>
#include <DayBase.h>

/**
* DayEight
*
* This is a the solution for Day Eight of Advent of Code 2023.
* https://adventofcode.com/2023/day/0
*
*/
class DayEight : public DayBase
{
public:
	DayEight()
		: DayBase(8)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		const char LEFT = 'L';
		map<string, pair<string, string>> locations;
		string start = "AAA";
		string dest = "ZZZ";
		string dir;
		input >> dir;

		{
			string source, eq, left, right;
			while (input >> source >> eq >> left >> right)
			{
				left = left.substr(1, left.length() - 2); // (LEFT,
				right = right.substr(0, right.length() - 1); // RIGHT)
				locations[source] = make_pair(left, right);
			}
		}

		int length = 0;
		for(; start != dest; ++length)
		{
			start = (dir[length % dir.length()] == LEFT ? locations[start].first : locations[start].second);
		}
		output << length << endl;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		const char LEFT = 'L';
		//map<string, pair<string, string>> locations;
		//vector<string> current;
		map<string, int> lookup;
		vector<int> current;
		map<int, pair<int, int>> locations;
		string dir;
		input >> dir;
		int nextid = 1;

		auto getid = [&](string s) {
			if (0 == lookup.count(s)) {
				lookup[s] = (++nextid << 1) | (*s.rbegin() == 'Z' ? 0 : 1);
			}
			return lookup[s];
		};
		{
			string source, eq, left, right;
			while (input >> source >> eq >> left >> right)
			{
				left = left.substr(1, left.length() - 2); // (LEFT,
				right = right.substr(0, right.length() - 1); // RIGHT)
				auto leftid = getid(left);
				auto rightid = getid(right);
				auto sourceid = getid(source);
				locations[sourceid] = make_pair(leftid, rightid);
				if (*source.rbegin() == 'A') current.push_back(sourceid);
			}
		}

		/*auto solved = [&]() {
			for(auto& loc : current)
			{
				if (loc & 1) return false;
			}
			return true;
		};

		int length = 0;
		for(; !solved(); ++length)
		{
			for (auto& start : current)
			{
				start = (dir[length % dir.length()] == LEFT ? locations[start].first : locations[start].second);
			}
		}*/
		vector<vector<int>> cycles;
		vector<int> rep_starts;
		vector<int> endp_counts;
		cycles.resize(current.size());
		for(int i = 0; i < current.size(); ++i)
		{
			cycles[i].push_back(current[i]);
			do {
				auto& nl = locations[*cycles[i].rbegin()];
				auto next = (dir[(cycles[i].size() - 1) % dir.length()] == LEFT ? nl.first : nl.second);
				if (auto iter = find(cycles[i].begin(), cycles[i].end(), next); iter != cycles[i].end())
				{
					rep_starts.push_back(iter - cycles[i].begin());
				}
				else
				{
					cycles[i].push_back(next);
				}
			} while (rep_starts.size() == i);
			endp_counts.push_back(count_if(cycles[i].begin() + rep_starts[i] - 1, cycles[i].end(), [](int v) { return (v & 1) == 0;}));
		}
		cout << cycles[0].size();
		//output << length << endl;
	}
};

DayEight g_dayEight = DayEight();
