#include"DebitCard.h"

std::string DebitCard::info()
{
	std::string result;
	result += "| Тип карты : " + _cardType + "\n"
		+ "| Название банка : " + bank() + "\n"
		+ "| Номер карты : " + numberCard() + "\n"
		+ "| Карта действительна до : " + dateValidalyCard() + "\n"
		+ "| CVV  : " + std::to_string(cvv()) + "\n"
		+ "| Баланс : " + std::to_string(_balance) + "\n";
	return result;
}
std::string DebitCard::ListCard()
{
	std::string result;
	for (auto i = 12; i < _numberCard.size(); i++)
	{
		result += std::to_string(_numberCard[i]);
	}
	return result;
}
std::string DebitCard::cardType()const
{
	return _cardType;
}
 bool DebitCard::pay(double sum)
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
void DebitCard::payBalance(double sum)
{
	_balance += abs(sum);
}
 bool DebitCard::transferMoney(double sum, Card* obj)
{
	if (_balance < sum || _balance == 0.0)
	{
		return false;
	}
	else if (this == obj)
	{
		return false;
	}
	else
	{
		_balance -= sum;
		obj->payBalance(sum);
		return true;
	}
}
double DebitCard::withDrawMoney(double sum)
{
	if (_balance < sum || _balance == 0.0)
	{
		return 0.0;
	}
	else
	{
		_balance -= sum;
		return sum;
	}
}