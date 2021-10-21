#include"Wallet.h"
virtual bool Wallet::pay(double sum)
{
	if (_balance == 0.0 || _balance < sum)
	{
		return false;
	}
	else
	{
		_balance -= sum;
		return true;
	}
}
//пополнение наличных
void Wallet::payBalance(double sum)
{
	_balance += abs(sum);
}
//добавить 1 карту
void Wallet::addCard(Card* obj)
{
	if (cards.empty()) {
		cards.push_front(obj);
	}
	else
		cards.push_back(obj);
}
//добавить список карт
void Wallet::addCard(Card** obj, int size)
{
	for (int i = 0; i < 2; i++)
	{
		cards.push_back(obj[i]);
	}

}
//удаление карты из кошелька
void Wallet::popCard(std::string key = std::string{})
{
	if (key != std::string{})
	{
		for (auto iter = cards.begin(); iter != cards.end(); iter++)
		{
			if (iter.operator*()->key() == key)
			{
				cards.erase(iter);
				return;
			}
		}
	}
	else if (key == "all")
		cards.clear();
	else
		cards.pop_back();
}
//gлучить список карт
std::string Wallet::ListCard()
{
	std::string res;
	for (Card* n : cards)
	{
		res += "*" + n->ListCard() + "\n";
	}
	return res;
}
std::string Wallet::info()
{
	std::string res;
	res += "| Владелец кошелька : " + _nameHolder + "\n"
		+ "| Баланс кошелька : " + std::to_string(_balance)
		+ "\n\n";

	for (Card* n : cards)
	{

		res += n->info() + "\n";
	}
	return res;
};
//пополнение баланса карты
void Wallet::payBalanceCard(double sum, std::string numCard)
{
	for (Card* n : cards)
	{
		if (n->key() == numCard)
		{
			n->payBalance(sum);
			return;
		}
	}
}
bool Wallet::payCard(double sum, std::string numCard)
{
	for (Card* n : cards)
	{
		if (n->key() == numCard)
		{
			return n->pay(sum);
		}
	}
}
void Wallet::addHistory(int categories, double sum, std::string source)
{
	struct tm tim;
	time_t rawtime = time(NULL);
	localtime_s(&tim, &rawtime);
	if (history.empty())
	{
		history.push_back(Transaction{ categories,sum,source,tim });
	}
	else {
		/*history.resize(history.size() + 1);*/
		history.push_back(Transaction{ categories,sum,source,tim });
	}
}
std::string Wallet::report(std::string key, int data, int top3 = 0)
{

	std::map<std::string, double> rating{
		{"Аптека",0.0},
		{"Бытовая техника",0.0},
		{"Одежда",0.0},
		{"Продукты",0.0},
		{"Ресторан",0.0}
	};
	std::map<std::string, int> ratingCategory{
		{"Аптека",0},
		{"Бытовая техника",0},
		{"Одежда",0},
		{"Продукты",0},
		{"Ресторан",0}
	};


	if (key == "day")
	{
		for (int i = 0; i < history.size(); i++)
		{
			if (history[i].tim.tm_mday == data)
			{
				switch (history[i].category)
				{
				case Categories::GROCERYSTORE:
				{
					rating["Продукты"] += history[i].sum;
					break;
				}
				case Categories::HOMEAPPLIANCESTORE:
				{
					rating["Бытовая техника"] += history[i].sum;
					break;
				}
				case Categories::CLOTHINGSTORE:
				{
					rating["Одежда"] += history[i].sum;
					break;
				}
				case Categories::RESTAURANT:
				{
					rating["Ресторан"] += history[i].sum;
					break;
				}
				case Categories::TRANSPORT:
				{
					rating["Траспорт"] += history[i].sum;
					break;
				}
				case Categories::PHARMACIES:
				{
					rating["Аптека"] += history[i].sum;
					break;
				}
				}
			}
		}
		std::string res = "Отчет за день :\n";
		for (auto it = rating.begin(); it != rating.end(); it++)
		{
			res += it.operator*().first + " :  " + std::to_string(it.operator*().second) + "\n";
		}
		return res;
	}
	else if (key == "week")
	{
		for (int i = 0; i < history.size(); i++)
		{
			if (history[i].tim.tm_mday - 7 || history[i].tim.tm_mday - 6 || history[i].tim.tm_mday - 5 || history[i].tim.tm_mday - 4
				|| history[i].tim.tm_mday - 3 || history[i].tim.tm_mday - 2 || history[i].tim.tm_mday - 1)
			{
				switch (history[i].category)
				{
				case Categories::GROCERYSTORE:
				{
					rating["Продукты"] += history[i].sum;
					ratingCategory["Продукты"]++;
					break;
				}
				case Categories::HOMEAPPLIANCESTORE:
				{
					rating["Бытовая техника"] += history[i].sum;
					ratingCategory["Бытовая техника"] ++;
					break;
				}
				case Categories::CLOTHINGSTORE:
				{
					rating["Одежда"] += history[i].sum;
					ratingCategory["Одежда"]  ++;
					break;
				}
				case Categories::RESTAURANT:
				{
					rating["Ресторан"] += history[i].sum;
					ratingCategory["Ресторан"]  ++;
					break;
				}
				case Categories::TRANSPORT:
				{
					rating["Траспорт"] += history[i].sum;
					ratingCategory["Траспорт"] ++;
					break;
				}
				case Categories::PHARMACIES:
				{
					rating["Аптека"] += history[i].sum;
					ratingCategory["Аптека"] ++;
					break;
				}
				}
			}
		}
		if (top3 == 1) //топ 3 по затратам
		{
			std::map<std::string, double> ::iterator category;
			std::string topThrree = "Топ 3 трат за неделю по сумме\n";
			std::string key;
			for (int i = 0; i < 3; i++)
			{

				topThrree += "|" + std::to_string(i + 1) + "| - ";
				key = std::max_element(rating.begin(), rating.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->first;
				category = rating.find(key);
				topThrree += key + "  сумма : " + std::to_string(std::max_element(rating.begin(), rating.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->second) + "\n";
				rating.erase(category);

			}
			return topThrree;
		}
		else if (top3 == 2) // топ 3 по категориям
		{
			std::map<std::string, int> ::iterator category;
			std::string topThrree = "Топ 3 трат за неделю по категориям :\m";
			std::string key;
			for (int i = 0; i < 3; i++)
			{

				topThrree += "|" + std::to_string(i) + "| - ";
				key = std::max_element(ratingCategory.begin(), ratingCategory.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->first;
				category = ratingCategory.find(key);
				topThrree += key + "  сумма : " + std::to_string(std::max_element(ratingCategory.begin(), ratingCategory.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->second) + "\n";
				ratingCategory.erase(category);


			}
			return topThrree;
		}
		else {
			std::string res = "Отчет за неделю : \n";
			for (auto it = rating.begin(); it != rating.end(); it++)
			{
				res += it.operator*().first + " :  " + std::to_string(it.operator*().second) + "\n";
			}
			return res;
		}
	}
	else if (key == "mounth")
	{
		for (int i = 0; i < history.size(); i++)
		{
			if (history[i].tim.tm_mon == data - 1)
			{
				switch (history[i].category)
				{
				case Categories::GROCERYSTORE:
				{
					rating["Продукты"] += history[i].sum;
					ratingCategory["Продукты"]++;
					break;
				}
				case Categories::HOMEAPPLIANCESTORE:
				{
					rating["Бытовая техника"] += history[i].sum;
					ratingCategory["Бытовая техника"] ++;
					break;
				}
				case Categories::CLOTHINGSTORE:
				{
					rating["Одежда"] += history[i].sum;
					ratingCategory["Одежда"]  ++;
					break;
				}
				case Categories::RESTAURANT:
				{
					rating["Ресторан"] += history[i].sum;
					ratingCategory["Ресторан"]  ++;
					break;
				}
				case Categories::TRANSPORT:
				{
					rating["Траспорт"] += history[i].sum;
					ratingCategory["Траспорт"] ++;
					break;
				}
				case Categories::PHARMACIES:
				{
					rating["Аптека"] += history[i].sum;
					ratingCategory["Аптека"] ++;
					break;
				}
				}
			}
		}
		if (top3 == 1) //топ 3 по затратам
		{
			std::string topThrree = "Топ 3 затрат за месяц по сумме :\n";
			std::map<std::string, double> ::iterator category;
			std::string key;
			for (int i = 0; i < 3; i++)
			{


				topThrree += "|" + std::to_string(i) + "| - ";
				key = std::max_element(rating.begin(), rating.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->first;
				category = rating.find(key);
				topThrree += key + "  сумма : " + std::to_string(std::max_element(rating.begin(), rating.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->second) + "\n";
				rating.erase(category);

			}
			return topThrree;
		}
		else if (top3 == 2) // топ 3 по категориям
		{
			std::map<std::string, int> ::iterator category;
			std::string topThrree = "Топ 3 затрат за месяц по категориям :\n";
			std::string key;
			for (int i = 0; i < 3; i++)
			{

				topThrree += "|" + std::to_string(i) + "| - ";
				key = std::max_element(ratingCategory.begin(), ratingCategory.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->first;
				category = ratingCategory.find(key);
				topThrree += key + "  сумма : " + std::to_string(std::max_element(ratingCategory.begin(), ratingCategory.end(),
					[](const std::pair<std::string, int> A, const std::pair<std::string, int> B)
					{
						return A.second < B.second;
					}
				)->second) + "\n";
				ratingCategory.erase(category);

			}
			return topThrree;
		}
		else {
			std::string res = "Отчет за месяц  : \n";
			for (auto it = rating.begin(); it != rating.end(); it++)
			{
				res += it.operator*().first + " :  " + std::to_string(it.operator*().second) + "\n";
			}
			return res;
		}
	}
}
std::string Wallet::printHistory()
{
	std::string result;
	result += "Категория   Источник   Сумма\t Время \n";
	for (auto it = history.begin(); it != history.end(); it++) {  // выводим их

		switch (it.operator*().category)
		{
		case Categories::GROCERYSTORE:
		{
			result += "Продукты";
			break;
		}
		case Categories::HOMEAPPLIANCESTORE:
		{
			result += "Бытовая техника";
			break;
		}
		case Categories::CLOTHINGSTORE:
		{
			result += "Одежда";
			break;
		}
		case Categories::RESTAURANT:
		{
			result += "Ресторан";
			break;
		}
		case Categories::TRANSPORT:
		{
			result += "Траспорт";
			break;
		}
		case Categories::PHARMACIES:
		{
			result += "Аптека";
			break;
		}
		}
		result += " | " + it.operator*().source + " |  " + std::to_string(it.operator*().sum) + "\t" + std::to_string(it.operator*().tim.tm_hour) + " : " + std::to_string(it.operator*().tim.tm_min)
			+ " / " + std::to_string(it.operator*().tim.tm_mday) + " / " + std::to_string(it.operator*().tim.tm_mon + 1) + " / " + std::to_string(it.operator*().tim.tm_year - 100) + "\n";

	}
	return result;
}