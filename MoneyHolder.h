#pragma once

#include<string>

class MoneyHolder
{
protected:
	std::string _nameHolder;
	double _balance;

public:
	MoneyHolder(std::string nameHolder = std::string{}, double balance = 0.0) :
		_nameHolder{ nameHolder },
		_balance{ balance }
	{}

	std::string nameHolder() const
	{
		return _nameHolder;
	}
	double balance() const
	{
		return _balance;
	}
	void setNameHolder(std::string nameHolder)
	{
		_nameHolder = nameHolder;
	}
	void setBalance(double cash)
	{
		_balance = abs(cash);
	}

	//виртуальные функции для переопределения в дочерних классах
	// для стандартный взаимодействий с кошельком
	virtual bool pay(double sum) = 0;
	virtual void payBalance(double sum) = 0;
	virtual std::string info() = 0;
	virtual std::string ListCard() = 0;
	virtual ~MoneyHolder()
	{}
};