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
namespace {
	struct Range
	{
		uint64_t dest, source, size;
	};
	bool operator<(const Range& a, const Range& b) {
		return a.source < b.source;
	}
}
class DayFive : public DayBase
{
public:
	DayFive()
		: DayBase(5)
	{}

protected:

	uint64_t translate(uint64_t loc, vector<Range>& ranges)
	{
		for (const Range& r : ranges)
		{
			if (loc >= r.source && loc < r.source + r.size)
			{
				return r.dest + loc - r.source;
			}
		}
		return loc;
	}

	void translate_range(pair<uint64_t, uint64_t> loc, vector<Range>& ranges, vector<pair<uint64_t, uint64_t>>& out)
	{
		for(auto& range : ranges)
		{
			if (loc.first < range.source)
			{
				uint64_t start = loc.first;
				uint64_t end = min(loc.second, range.source);
				out.push_back(make_pair(start, end));
				loc.first = end;
				if  (loc.first >= loc.second) return;
			}
			if (loc.first < range.source + range.size)
			{
				uint64_t start = range.dest + loc.first - range.source;
				uint64_t end = range.dest + min(loc.second, range.source + range.size) - range.source;
				out.push_back(make_pair(start, end));
				loc.first = range.source + range.size;
				if (loc.first >= loc.second) return;
			}
		}
		out.push_back(loc);
	}

	virtual void questionOne(istream& input, ostream& output)
	{
		vector<uint64_t> seeds;
		vector<Range> seed_soil, soil_fert, fert_water, water_light, light_temp, temp_hum, hum_loc;

		{// parse
			string line;
			getline(input, line);
			stringstream ss(line);
			string dummy;
			ss >> dummy;
			uint64_t seed;
			while(ss >> seed) seeds.push_back(seed);

			auto read_ranges = [&](vector<Range>& target) {
				string title;
				input >> title;
				//output << title << endl;
				getline(input, title); // map:
				Range range;
				do {
					if(!getline(input, line)) return;
					ss = stringstream(line);
				} while (ss >> range.dest >> range.source >> range.size && (target.push_back(range), true));
			};
			read_ranges(seed_soil);
			read_ranges(soil_fert);
			read_ranges(fert_water);
			read_ranges(water_light);
			read_ranges(light_temp);
			read_ranges(temp_hum);
			read_ranges(hum_loc);
		}

		uint64_t out = (uint64_t)-1;
		for(auto seed : seeds)
		{
			uint64_t soil = translate(seed, seed_soil);
			uint64_t fert = translate(soil, soil_fert);
			uint64_t water = translate(fert, fert_water);
			uint64_t light = translate(water, water_light);
			uint64_t temp = translate(light, light_temp);
			uint64_t hum = translate(temp, temp_hum);
			uint64_t loc = translate(hum, hum_loc);
			out = min(out, loc);
		}
		output << out << endl;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		vector<uint64_t> seeds;
		vector<Range> seed_soil, soil_fert, fert_water, water_light, light_temp, temp_hum, hum_loc;

		{// parse
			string line;
			getline(input, line);
			stringstream ss(line);
			string dummy;
			ss >> dummy;
			uint64_t seed;
			while(ss >> seed) seeds.push_back(seed);

			auto read_ranges = [&](vector<Range>& target) {
				string title;
				input >> title;
				//output << title << endl;
				getline(input, title); // map:
				Range range;
				do {
					if(!getline(input, line)) { sort(target.begin(), target.end()); return; }
					ss = stringstream(line);
				} while (ss >> range.dest >> range.source >> range.size && (target.push_back(range), true));
				sort(target.begin(), target.end());
			};
			read_ranges(seed_soil);
			read_ranges(soil_fert);
			read_ranges(fert_water);
			read_ranges(water_light);
			read_ranges(light_temp);
			read_ranges(temp_hum);
			read_ranges(hum_loc);
		}

		vector<vector<Range>*> translations {&seed_soil, &soil_fert, &fert_water, &water_light, &light_temp, &temp_hum, &hum_loc};
		uint64_t out = (uint64_t)-1;
		vector<pair<uint64_t, uint64_t> > ranges;
		for (int i = 0; i < seeds.size(); i += 2)
		{
			ranges.push_back(make_pair(seeds[i], seeds[i] + seeds[i+1]));
		}
		for (auto& trans : translations)
		{
			for (int i = 1; i < trans->size(); ++i)
			{
				if (trans->at(i).source < (trans->at(i-1).source + trans->at(i-1).size))
				{
					output << "ERROR!" << endl;
				}
			}
			vector<pair<uint64_t, uint64_t> > next;
			for(auto& p : ranges)
			{
				translate_range(p, *trans, next);
			}
			swap(ranges, next);
		}
		for (auto& r : ranges)
		{
			out = min(out, r.first);
		}
		output << out << endl;
	}
};


DayFive g_dayFive = DayFive();

