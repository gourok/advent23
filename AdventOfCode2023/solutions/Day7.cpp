#include <Helpers.h>
#include <DayBase.h>

/**
* DaySeven
*
* This is a the solution for Day Seven of Advent of Code 2023.
* https://adventofcode.com/2023/day/7
*
*/
class DaySeven : public DayBase
{
public:
	DaySeven()
		: DayBase(7)
	{}

private:
	enum HandType : int
	{
		HighCard = 1,
		Pair,
		TwoPairs,
		Three,
		FullHouse,
		Four,
		Five
	};

	struct Hand
	{
		Hand(string aHand, int aBid, bool isTwo = false)
			: hand(aHand), bid(aBid)
		{
			if (isTwo)
			{
				calculateTypeTwo();
			}
			else
			{
				calculateType();
			}
		}

		string hand;
		int bid;
		HandType type = HighCard;

		void calculateType()
		{
			type = HighCard;

			for (int x = 0; x < 5; x++)
			{
				int count = 1;
				for (int y = x + 1; y < 5; y++)
				{
					if (hand[x] == hand[y])
						count++;
				}

				if (count == 5)
				{
					type = Five;
					return;
				}
				else if (count == 4)
				{
					type = Four;
					return;
				}
				else if (count == 3)
				{
					// Check for Full House
					char other = 0;
					for (int y = x; y < 5; y++)
					{
						if (hand[x] != hand[y])
						{
							if (other == 0)
							{
								other = hand[y];
							}
							else
							{
								if (other == hand[y])
								{
									type = FullHouse;
									return;
								}
							}
						}
					}

					type = Three;
					return;
				}
				else if (count == 2)
				{
					// Check for Full House or Two Pair
					char other1 = 0;
					int other1count = 1;
					char other2 = 0;
					int other2count = 1;
					for (int y = x; y < 5; y++)
					{
						if (hand[x] != hand[y])
						{
							if (other1 == 0)
							{
								other1 = hand[y];
							}
							else if (other1 == hand[y])
							{
								other1count++;
							}
							else if (other2 == 0)
							{
								other2 = hand[y];
							}
							else if (other2 == hand[y])
							{
								other2count++;
							}
						}
					}

					if (other1count == 3)
					{
						type = FullHouse;
						return;
					}
					else if (other1count == 2 || other2count == 2)
					{
						type = TwoPairs;
						return;
					}
					else
					{
						type = Pair;
						return;
					}
				}
			}
		}

		void calculateTypeTwo()
		{
			type = HighCard;

			int jokerCount = 0;
			for (int x = 0; x < 5; x++)
			{
				if (hand[x] == 'J')
					jokerCount++;
			}

			for (int x = 0; x < 5; x++)
			{
				if (hand[x] == 'J')
					continue;

				int count = 1;
				for (int y = x + 1; y < 5; y++)
				{
					if (hand[x] == hand[y])
						count++;
				}

				if (count == 5)
				{
					type = Five;
					return;
				}
				else if (count == 4)
				{
					if (jokerCount > 0)
					{
						type = Five;
					}
					else
					{
						type = Four;
					}
					return;
				}
				else if (count == 3)
				{
					// Check for Full House
					char other = 0;
					for (int y = x + 1; y < 5; y++)
					{
						if (hand[y] == 'J')
							continue;

						if (hand[x] != hand[y])
						{
							if (other == 0)
							{
								other = hand[y];
							}
							else
							{
								if (other == hand[y])
								{
									type = FullHouse;
									return;
								}
							}
						}
					}

					if (jokerCount == 2)
					{
						type = Five;
					}
					else if (jokerCount == 1)
					{
						type = Four;
					}
					else
					{
						type = Three;
					}
					return;
				}
				else if (count == 2)
				{
					// Check for Full House or Two Pair
					char other1 = 0;
					int other1count = 1;
					char other2 = 0;
					int other2count = 1;
					for (int y = x + 1; y < 5; y++)
					{
						if (hand[y] == 'J')
							continue;

						if (hand[x] != hand[y])
						{
							if (other1 == 0)
							{
								other1 = hand[y];
							}
							else if (other1 == hand[y])
							{
								other1count++;
							}
							else if (other2 == 0)
							{
								other2 = hand[y];
							}
							else if (other2 == hand[y])
							{
								other2count++;
							}
						}
					}

					if (other1count == 3)
					{
						type = FullHouse;
						return;
					}
					else if (other1count == 2 || other2count == 2)
					{
						if (jokerCount == 1)
						{
							type = FullHouse;
						}
						else
						{
							type = TwoPairs;
						}
						return;
					}
					else
					{
						if (jokerCount == 3)
						{
							type = Five;
						}
						else if (jokerCount == 2)
						{
							type = Four;
						}
						else if (jokerCount == 1)
						{
							type = Three;
						}
						else
						{
							type = Pair;
						}
						return;
					}
				}
			}

			// High Card Checks
			switch (jokerCount)
			{
			case 5:
				type = Five;
				break;
			case 4:
				type = Five;
				break;
			case 3:
				type = Four;
				break;
			case 2:
				type = Three;
				break;
			case 1:
				type = Pair;
				break;
			}
		}
	};

protected:
	virtual void questionOne(istream& input, ostream& output)
	{
		vector<Hand> hands;

		string line;
		while (getline(input, line))
		{
			vector<string> values = splitString(line, " ");

			hands.emplace_back(values[0], atoi(values[1].c_str()));
		}

		sort(hands.begin(), hands.end(), DaySeven::compareHands);

		int total = 0;

		int rank = 1;
		for (Hand hand : hands)
		{
			total += hand.bid * rank;
			rank++;
		}

		output << total;
	}

	virtual void questionTwo(istream& input, ostream& output)
	{
		vector<Hand> hands;

		string line;
		while (getline(input, line))
		{
			vector<string> values = splitString(line, " ");

			hands.emplace_back(values[0], atoi(values[1].c_str()), true);
		}

		sort(hands.begin(), hands.end(), DaySeven::compareHandsTwo);

		int total = 0;

		int rank = 1;
		for (Hand hand : hands)
		{
			total += hand.bid * rank;
			rank++;
		}

		output << total;
	}

private:

	static int getCardValue(char card)
	{
		switch (card)
		{
		case 'T':
			return 10;
		case 'J':
			return 11;
		case 'Q':
			return 12;
		case 'K':
			return 13;
		case 'A':
			return 14;
		default:
			return card - '0';
		}
	}

	static int getCardValueTwo(char card)
	{
		switch (card)
		{
		case 'T':
			return 10;
		case 'J':
			return 1;
		case 'Q':
			return 12;
		case 'K':
			return 13;
		case 'A':
			return 14;
		default:
			return card - '0';
		}
	}

	static bool compareHands(const Hand& left, const Hand& right)
	{
		HandType leftType = left.type;
		HandType rightType = right.type;

		if (leftType < rightType)
		{
			return true;
		}
		else if (leftType > rightType)
		{
			return false;
		}

		string leftString = left.hand;
		string rightString = right.hand;

		for (int i = 0; i < 5; ++i)
		{
			int leftValue = getCardValue(leftString[i]);
			int rightValue = getCardValue(rightString[i]);

			if (leftValue < rightValue)
			{
				return true;

			}
			else if (leftValue > rightValue)
			{
				return false;
			}
		}

		// Should Never Get Here
		return true;
	}

	static bool compareHandsTwo(const Hand& left, const Hand& right)
	{
		HandType leftType = left.type;
		HandType rightType = right.type;

		if (leftType < rightType)
		{
			return true;
		}
		else if (leftType > rightType)
		{
			return false;
		}

		string leftString = left.hand;
		string rightString = right.hand;

		for (int i = 0; i < 5; ++i)
		{
			int leftValue = getCardValueTwo(leftString[i]);
			int rightValue = getCardValueTwo(rightString[i]);

			if (leftValue < rightValue)
			{
				return true;

			}
			else if (leftValue > rightValue)
			{
				return false;
			}
		}

		// Should Never Get Here
		return true;
	}
};

DaySeven g_daySeven = DaySeven();
