#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::bitset<25> bingo_win_patterns[10] = {
	std::bitset<25>(std::string("1111100000000000000000000")),
	std::bitset<25>(std::string("0000011111000000000000000")),
	std::bitset<25>(std::string("0000000000111110000000000")),
	std::bitset<25>(std::string("0000000000000001111100000")),
	std::bitset<25>(std::string("0000000000000000000011111")),
	std::bitset<25>(std::string("1000010000100001000010000")),
	std::bitset<25>(std::string("0100001000010000100001000")),
	std::bitset<25>(std::string("0010000100001000010000100")),
	std::bitset<25>(std::string("0001000010000100001000010")),
	std::bitset<25>(std::string("0000100001000010000100001"))
};

std::vector<std::vector<unsigned>> bingo_cards = { std::vector<unsigned>() };
std::vector<unsigned> bingo_calls;

int main()
{
	std::ifstream input; input.open("input.txt");

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
		//every other line will be used to build bingo cards
		else
		{
			if (line.empty())
			{
				continue;
			}

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

			//start next card
			if (card.size() == 25)
			{
				bingo_cards.emplace_back();
			}
		}
	}

	//create empty bitsets for each bingo card built
	std::vector<std::bitset<25>> card_bits(bingo_cards.size());

	for (unsigned num : bingo_calls)
	{
		for (unsigned i = 0; i < bingo_cards.size(); i++)
		{
			std::vector<unsigned>& bingo_card = bingo_cards[i];

			auto itr = std::find(bingo_card.begin(), bingo_card.end(), num);
			if (itr != bingo_card.cend())
			{
				std::bitset<25>& marked_numbers = card_bits[i];

				marked_numbers[std::distance(bingo_card.begin(), itr)] = true;

				//check if this makes the card a winner
				for (std::bitset<25> &mask : bingo_win_patterns)
				{
					std::bitset<25> pattern = mask & marked_numbers;

					if (mask == pattern)
					{
						unsigned total = 0;
						for (unsigned b = 0; b < mask.size(); b++)
						{
							if (!marked_numbers[b])
							{
								total += bingo_card[b];
							}
						}

						//sum all unmarked values in this card
						std::cout << "The total of unmarked numbers in the winning card is: " << total * num;

						return 1;
					}
				}
			}
		}
	}
}

