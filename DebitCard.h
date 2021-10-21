#pragma once
#include"Card.h"

class DebitCard : public Card
{
	std::string _cardType;
public:
	DebitCard(std::string nameHolder = std::string{}, double balance = 0.0, std::string nameBank = std::string{})
		: Card(nameHolder, balance, nameBank)
	{
		_cardType = "Debit card";
	}

	std::string cardType()const;
	virtual bool pay(double sum);
	virtual void payBalance(double sum);
	virtual bool transferMoney(double sum, Card* obj);
	virtual double withDrawMoney(double sum);
	virtual std::string info();
	virtual std::string ListCard();
	virtual ~DebitCard() {}
};