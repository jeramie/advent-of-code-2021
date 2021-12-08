#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::bitset<25> bingo_win_masks[10] = {
	std::bitset<25>(0x1F00000)		, //1111100000000000000000000
	std::bitset<25>(0x1F00000 >> 5)	, //0000011111000000000000000
	std::bitset<25>(0x1F00000 >> 10), //0000000000111110000000000
	std::bitset<25>(0x1F00000 >> 15), //0000000000000001111100000
	std::bitset<25>(0x1F00000 >> 20), //0000000000000000000011111
	std::bitset<25>(0x108421)		, //1000010000100001000010000
	std::bitset<25>(0x108421 >> 1)	, //0100001000010000100001000
	std::bitset<25>(0x108421 >> 2)	, //0010000100001000010000100
	std::bitset<25>(0x108421 >> 3)	, //0001000010000100001000010
	std::bitset<25>(0x108421 >> 4)	  //0000100001000010000100001
};

std::vector<std::vector<unsigned>> bingo_cards;
std::vector<unsigned> bingo_calls;
std::vector<unsigned> winning_cards;
std::map<unsigned, unsigned> winning_values;

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line;
	bool header = true;
	while (std::getline(input, line))
	{
		std::istringstream iss(line);

		//build called bingo numbers from header line input
		if (header)
		{
			std::string token;
			while (std::getline(iss, token, ','))
			{
				bingo_calls.push_back(std::stoi(token));
			}

			header = false;
		}
		//start new card
		else if (line.empty())
		{
			bingo_cards.emplace_back();
		}
		//insert bingo card numbers row at a time
		else
		{
			std::vector<unsigned>& card = bingo_cards.back();

			unsigned b1, b2, b3, b4, b5;
			while (iss >> b1 >> b2 >> b3 >> b4 >> b5)
			{
				card.push_back(b1);
				card.push_back(b2);
				card.push_back(b3);
				card.push_back(b4);
				card.push_back(b5);
			}
		}
	}

	//create empty bitsets for each bingo card built for the numbers to be marked on
	std::vector<std::bitset<25>> bingo_card_marked_numbers(bingo_cards.size());

	for (unsigned num : bingo_calls)
	{
		for (unsigned i = 0; i < bingo_cards.size(); i++)
		{
			if (winning_values[i] > 0) continue;

			std::vector<unsigned>& bingo_card = bingo_cards[i];

			auto itr = std::find(bingo_card.begin(), bingo_card.end(), num);
			if (itr != bingo_card.cend())
			{
				std::bitset<25>& marked_numbers = bingo_card_marked_numbers[i];

				marked_numbers[std::distance(bingo_card.begin(), itr)] = true;

				//check if this makes the card a winner
				for (std::bitset<25> &mask : bingo_win_masks)
				{
					if (mask == (mask & marked_numbers))
					{
						unsigned total = 0;
						//sum up any numbers not marked on the bingo card
						for (unsigned b = 0; b < marked_numbers.size(); b++)
						{
							if (!marked_numbers[b])
							{
								total += bingo_card[b];
							}
						}

						winning_cards.push_back(i);
						winning_values[i] = total * num;
					}
				}
			}
		}
	}

	//part 1
	std::cout << "The first winning board value is: " << winning_values[winning_cards.front()] << "\n";

	//part 2
	std::cout << "The last winning board value is: " << winning_values[winning_cards.back()] << "\n";
}


