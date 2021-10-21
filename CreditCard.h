#pragma once
#include"Card.h"
class CreditCard : public Card
{
	std::string _cardType;
public:
	CreditCard(std::string nameHolder = std::string{}, double balance = 0.0, std::string nameBank = std::string{})
		: Card(nameHolder, balance, nameBank)
	{
		_cardType = "Credit card";
	}

	std::string cardType()const;
	virtual bool pay(double sum);
	virtual void payBalance(double sum);
	virtual bool transferMoney(double sum, Card* obj);
	virtual double withDrawMoney(double sum);
	virtual std::string ListCard();
	virtual std::string info();
	virtual ~CreditCard() {}
};