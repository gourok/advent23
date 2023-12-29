#include <Helpers.h>
#include <DayBase.h>

/**
* DaySix
*
* This is a the solution for Day Six of Advent of Code 2023.
* https://adventofcode.com/2023/day/6
*
*/
class DaySix : public DayBase
{
public:
	DaySix()
		: DayBase(6)
	{}

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		string line;
		int totalTime = 1;
		
		// Times
		getline(input, line);

		vector<string> timeStrings = splitString(line, " ");
		vector<int> times;
		for (size_t i = 1; i < timeStrings.size(); i++)
		{
			if (timeStrings[i].length() == 0)
				continue;

			times.emplace_back(atoi(timeStrings[i].c_str()));
		}

		// Distances
		getline(input, line);

		vector<string> distanceStrings = splitString(line, " ");
		vector<int> distances;
		for (size_t i = 1; i < distanceStrings.size(); i++)
		{
			if (distanceStrings[i].length() == 0)
				continue;

			distances.emplace_back(atoi(distanceStrings[i].c_str()));
		}

		for (size_t x = 0; x < times.size(); ++x)
		{
			float time = (float)times[x];
			float distance = (float)distances[x];


			float root = sqrtf(time*time - 4.0f * distance) / 2.0f;
			float middle = time / 2.0f;

			int low = ceil(middle - root);
			int high = floor(middle + root);

			int total = high - low + 1;

			if (low * ((int)time - low) == (int)distance)
				total -= 2;

			totalTime *= total;
		}

		output << totalTime;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		string line;

		// Times
		getline(input, line);

		vector<string> timeStrings = splitString(line, " ");
		string timeString;
		for (size_t i = 1; i < timeStrings.size(); i++)
		{
			if (timeStrings[i].length() == 0)
				continue;

			timeString.append(timeStrings[i]);
		}

		int64_t time = atoi(timeString.c_str());

		// Distances
		getline(input, line);

		vector<string> distanceStrings = splitString(line, " ");
		string distanceString;
		for (size_t i = 1; i < distanceStrings.size(); i++)
		{
			if (distanceStrings[i].length() == 0)
				continue;

			distanceString.append(distanceStrings[i]);
		}

		int64_t distance = atoll(distanceString.c_str());

		double timeFloat = (double)time;
		double distanceFloat = (double)distance;

		double root = sqrt(timeFloat * timeFloat - 4.0f * distanceFloat) / 2.0f;
		double middle = timeFloat / 2.0f;

		int64_t low = ceil(middle - root);
		int64_t high = floor(middle + root);

		int64_t total = high - low + 1;

		if (low * ((int64_t)timeFloat - low) == (int64_t)distanceFloat)
			total -= 2;

		output << total;
	}
};

DaySix g_daySix = DaySix();
