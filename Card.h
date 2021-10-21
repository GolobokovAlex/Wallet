#pragma once
#include<string>
#include<vector>
#include <time.h>
#include <stdio.h>
#include"MoneyHolder.h"

class Card : public virtual MoneyHolder
{
protected:
	std::string _nameBank;
	std::vector<int> _numberCard;
	std::string _dateCardValid;
	uint16_t _cvvCode;
	std::string _numCard;//ключ для поиска в списке

public:
	Card(std::string nameHolder = std::string{}, double balance = 0.0, std::string nameBank = std::string{}) :
		MoneyHolder(nameHolder, balance),
		_nameBank{ nameBank }
	{
		_numberCard.resize(16);
		for (auto iter = _numberCard.begin(); iter != _numberCard.end(); iter++)
		{
			*iter = rand() % 9;
		}

		tm tim;
		time_t rawtime = time(NULL);
		localtime_s(&tim, &rawtime);
		_dateCardValid += std::to_string(tim.tm_mon + 1) + "/" + std::to_string((tim.tm_year + (rand() % 4 + 1) - 100));
		_cvvCode = rand() % 899 + 100;

		for (auto i = 12; i < _numberCard.size(); i++)
		{
			_numCard += std::to_string(_numberCard[i]);
		}
	}

	std::string bank() const
	{
		return _nameBank;
	}
	void setBank(std::string nameBank)
	{
		_nameBank = nameBank;
	}
	std::string dateValidalyCard() const
	{
		return _dateCardValid;
	}
	int cvv()const
	{
		return _cvvCode;
	}
	std::string numberCard() const
	{
		std::string result;
		for (auto iter = 0; iter < _numberCard.size(); iter++)
		{
			if (iter == 4 || iter == 8 || iter == 12)
				result += " ";
			result += std::to_string(_numberCard[iter]);
		}
		return result;
	}

	virtual bool pay(double sum)
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
	virtual void payBalance(double sum)
	{
		_balance += abs(sum);
	}
	virtual std::string key()const
	{
		return _numCard;
	}
	//+ add virtual methods Card
	virtual bool transferMoney(double sum, Card* obj) = 0;
	virtual double withDrawMoney(double sum) = 0;
	virtual std::string ListCard() = 0;

	virtual std::string info() = 0;
	virtual ~Card() {}
};