#pragma once
#include"MoneyHolder.h"
#include"Card.h"
#include<list>
#include<vector>
#include<map>
#include<algorithm>

enum Categories
{
	GROCERYSTORE = 1,	//��������
	HOMEAPPLIANCESTORE, //������� �������
	CLOTHINGSTORE,		//������
	RESTAURANT,			//���������
	TRANSPORT,			//���������
	PHARMACIES			//������
};
struct Transaction {

	int category;
	double sum;
	std::string source;
	struct tm tim;
};

class Wallet : public MoneyHolder
{
	std::list<Card*> cards;
	std::vector<Transaction> history;

public:

	Wallet(std::string nameHolder = std::string{}, double balance = 0.0) :
		MoneyHolder(nameHolder, balance) {}


	//������� �� ��������
	virtual bool pay(double sum);
	//���������� ��������
	virtual void payBalance(double sum);
	//�������� 1 �����
	void addCard(Card* obj);
	//�������� ������ ����
	void addCard(Card** obj, int size);
	//�������� ����� �� ��������
	void popCard(std::string key = std::string{});
	virtual std::string ListCard();
	virtual std::string info();
	void payBalanceCard(double sum, std::string numCard);
	bool payCard(double sum, std::string numCard);
	void addHistory(int categories, double sum, std::string source);
	std::string report(std::string key, int data, int top3 = 0);
	std::string printHistory();
	virtual ~Wallet() {}
};