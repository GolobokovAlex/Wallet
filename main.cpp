#include<iostream>
#include<string>
#include<fstream>
#include"CreditCard.h"
#include"DebitCard.h"
#include"Wallet.h"


void otchet(Wallet& wall)
{
	int choise = 0, date = 0;
	std::cout << R"(|	�������� ����� :
|	������������ ������� �� �������� � ����������:
|	|1|- ����
|	|2|- ������
|	|3|- �����
|	������������ ��������� �� ������������ ������:
|	|4|- ���-3 �������
|	|5|- ���-3 ���������
|	|6| - ����� � �������� ����)" << std::endl;

	std::cout << "���� : ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
	{
		
		std::cout << "������� �����,�� ������� ������ ����������� ����� : ";
		std::cin >> date;
		std::cout<< wall.report("day", date)<<"\n\n";
		std::cout << "�������� ����� � ����?(y/n) : ";
		char ch;
		std::cin >> ch;
		if (std::tolower(ch) == 'y')
		{
			std::fstream report("Day.txt" ,std::ios::out);
			if (report.is_open())
			{
				report << (wall.report("day", date));
			}
			report.close();
			
		}
		break;
	}
	case 2:
	{
		std::cout<< wall.report("week", 0)<< "\n\n";
		std::cout << "�������� ����� � ����?(y/n) : ";
		char ch;
		std::cin >> ch;
		if (std::tolower(ch) == 'y')
		{
			std::fstream report("Week.txt", std::ios::out);
			if (report.is_open())
			{
				report << wall.report("week", 0);
			}
			report.close();

		}
		break;
	}
	case 3:
	{
		std::cout << "������� ����� ,�� ������� ������ ����������� �����(1-12) : ";
		std::cin >> date;
		std::cout << wall.report("mounth", date) << "\n\n";
		std::cout << "�������� ����� � ����?(y/n) : ";
		char ch;
		std::cin >> ch;
		if (std::tolower(ch) == 'y')
		{
			std::fstream report("Mounth.txt", std::ios::out);
			if (report.is_open())
			{
				report << wall.report("mounth", date);
			}
			report.close();

		}
		break;
	}
	case 4:
	{
		int weekAndMounth;
		std::cout << " \n |1| - ������ \n |2| - �����" << std::endl;
		std::cin >> weekAndMounth;
		if (weekAndMounth == 1)
		{
			std::cout << wall.report("week", 0, 1) << "\n\n";
			std::cout << "�������� ����� � ����?(y/n) : ";
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y')
			{
				std::fstream report("Expenses per week by amount.txt", std::ios::out);
				if (report.is_open())
				{
					report << wall.report("week", 0, 1);
				}
				report.close();

			}
		}
		else if (weekAndMounth == 2)
		{

			std::cout << "������� �����,�� ������� ������ �������� ���������� :";
			std::cin >> date;
			std::cout << wall.report("mounth", date, 1) << "\n\n";
			std::cout << "�������� ����� � ����?(y/n) : ";
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y')
			{
				std::fstream report("Monthly expenses by amount.txt", std::ios::out);
				if (report.is_open())
				{
					report << wall.report("mounth", date, 1);
				}
				report.close();

			}
		}
		break;
	}
	case 5:
	{
		int weekAndMounth;
		std::cout << " \n |1| - ������ \n |2| - �����" << std::endl;
		std::cin >> weekAndMounth;
		if (weekAndMounth == 1)
		{
			std::cout << wall.report("week", 0, 2) << "\n\n";
			std::cout << "�������� ����� � ����?(y/n) : ";
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y')
			{
				std::fstream report("Weekly expenses by category.txt", std::ios::out);
				if (report.is_open())
				{
					report << wall.report("week", 0, 2);
				}
				report.close();

			}
		}
		else if (weekAndMounth == 2)
		{

			std::cout << "������� �����,�� ������� ������ �������� ���������� :";
			std::cin >> date;
			std::cout << wall.report("mounth", date, 2) << "\n\n";
			std::cout << "�������� ����� � ����?(y/n) : ";
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y')
			{
				std::fstream report("Monthly expenses by category.txt", std::ios::out);
				if (report.is_open())
				{
					report << wall.report("mounth", date, 2);
				}
				report.close();

			}
		}

		break;
	}
	case 6:
	{
		return;
	}
	}
}
int cat()
{
	system("cls");
	int cat;
	std::cout << "�������� ��������� : ";
	std::cout << R"(
	|1|- ��������.
	|2|- ������� �������.
	|3|- ������.
	|4|- ��������.
	|5|- ���������
	|6| -������
)";
	std::cout << "������� �� 1 �� 6 : ";
	std::cin >> cat;
	return  cat;
}
void pay(Wallet& wall)
{
	int choise = 0;
	std::cout << R"(	�������� ������ ������
	|1|-�������� ���������.
	|2|-�������� ������.)";
	std::cout << "\n\t������� : ";
	std::cin >> choise;
	
	switch (choise) 
	{
	case 1: 
	{
		double cash = 0.0;
		std::cout << "������� ����� ������ : ";
		std::cin >> cash;
		if (cash > 0.0 && cash < wall.balance())
		{
			if (wall.pay(cash))
			{
				wall.addHistory(cat(), cash, "��������");
				std::cout << "�����";
			}
		}
		else if (cash > wall.balance())
			std::cout << "������������ �������� �������." << std::endl;
		else if (cash <= 0.0)
			 std::cout << "����������� ������� ����� ������." << std::endl;
		break;
	}
	case 2:
	{
		std::string strPay;
		double cash = 0.0;
		std::cout<< wall.ListCard();
		std::cout << "������� ��������� 4 ����� ����� : ";
		std::cin.ignore();
		std::getline(std::cin , strPay);
		std::cout << "������� ����� ������� : ";
		std::cin >> cash;

		wall.payCard(cash, strPay);
		wall.addHistory(cat(), cash,"����� :*"+strPay);
	}
	}
}
void transferMoneyCard(Wallet& wall)
{
	int choise = 0;
	std::cout << R"(	�������� ������ 
	|1|-��������� ���� �� ������ �����.
	|2|-��������� ������� ��������.)"; //������������� �������������� �����??
	std::cout << "\n\t������� : ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
	{
		std::string paymentCard;
		std::string receivCard;
		double cash = 0.0;
		std::cout << wall.ListCard();
		std::cout << "������� ��������� 4 ����� ����� c ������� ������ ��������� : ";
		std::cin.ignore();
		std::getline(std::cin, paymentCard);
		std::cout << "������� ��������� 4 ����� ����� �� ������� ������ ��������� : ";
		std::cin.ignore();
		std::getline(std::cin, receivCard);
		std::cout << "������� ����� ������� : ";
		std::cin >> cash;
		if (wall.payCard(cash, paymentCard))
		{
			wall.payBalanceCard(cash, receivCard);
			wall.addHistory(7, cash, "����� *" + paymentCard);
		}
		else
			std::cout << "��������� ������������ ����� ����� � ����� ��������"<<std::endl;
		break;
	}
	case 2:
	{
		std::string paymentCard, receivCard;
		double cash = 0.0;
		std::cout << wall.ListCard();
		std::cout << "������� ��������� 4 ����� ����� c ������� ������ ��������� : ";
		std::cin.ignore();
		std::getline(std::cin, paymentCard);
		std::cout << "������� ����� ����� �� ������� ������ ��������� ������� : ";
		std::cin.ignore();
		std::getline(std::cin, receivCard);
		std::cout << "������� ����� ������� : ";
		std::cin >> cash;
		if (wall.payCard(cash, paymentCard))
		{
			std::cout << "�������� ��������� �������" << std::endl;
			wall.addHistory(7, cash, "����� *" + paymentCard);
		}
		else
			std::cout << "��������� ������������ ����� ����� � ����� ��������" << std::endl;
	}
	}
}
int menu(Wallet& wall)
{
	int choise = 0;
	std::cout << "����� ���������� � ��������� ���������� ���������." << std::endl;
	while (choise != 8) {
		
		std::cout << R"(
	�������� �������� :
	|1|- �������� ���������� � ��������.
	|2|- �������� �������� � �������.
	|3|- �������� �������.
	|4|- ��������� ������ �����.
	|5|- ��������� ������ � �����.
	|6|- �����
	|7|- �������� �������
	|8|- ����� � �������� ����
)";
		std::cout << "������� �� 1 �� 8 : ";
		std::cin >> choise;
		system("cls");
		switch (choise)
		{
		case 1:
			{
				std::cout<< wall.info() << "\n\n";
				std::cout << "�������� ����� � ����?(y/n) : ";
				char ch;
				std::cin >> ch;
				if (std::tolower(ch) == 'y')
				{
					std::fstream report("Wallet Information.txt", std::ios::out);
					if (report.is_open())
					{
						report << wall.info();
					}
					report.close();

				}
				break;
			}
		case 2:
		{
			double cash = 0.0;
			std::cout << "������� �����,������� ������ �������� : ";
			std::cin >> cash;
			if (cash > 0.0)
			{
				wall.payBalance(cash);
				std::cout << wall.balance();
			}
			else
				std::cout << "��������,��������� ������. ��������� ����.";
			break;
		}

		case 3:
		{
			pay(wall);
			break;
		}
		case 4:
		{
			double cash = 0.0;
			std::cout << "������� �����,�� ������� ������ ��������� ������ ����� : ";
			std::cin >> cash;
			std::cout << wall.ListCard();
			std::cout << "������� ��������� 4 ����� ����� : ";
			std::string strCardPayBalance;
			std::cin.ignore();
			std::getline(std::cin, strCardPayBalance);
			wall.payBalanceCard(cash, strCardPayBalance);
			break;
		}
		case 5:
		{
			transferMoneyCard(wall);
			break;
		}
		case 6:
		{
			otchet(wall);
			break;
		}
		case 7:
		{
			std::cout<<wall.printHistory() << "\n\n";
			std::cout << "�������� ����� � ����?(y/n) : ";
			char ch;
			std::cin >> ch;
			if (std::tolower(ch) == 'y')
			{
				std::fstream report("Transaction history.txt",std::ios::out);
				if (report.is_open())
				{
					report << wall.printHistory();
				}
				report.close();

			}
			break;
		}
		}

	}
	return 0;

}
void start()
{
	Wallet wal;
	int choise = 0;
	std::cout << "\t\t����� ���������� � ��������� ���������� ���������." << std::endl;
	while (choise != 4) {
		
		std::cout << R"(
	�������� �������� :
	|1|- ������� �������.
	|2|- �������� ����� � �������� � �������(����������� ������� ����������� ��������!).
	|3|- ������ ������ � ���������
	|4|- �����
)";
		std::cout << "������� �� 1 �� 4 : ";
		std::cin >> choise;
		system("cls");
		switch (choise)
		{
		case 1:
		{
			std::cout << "������� ������ ��� ��� ������������ �������� : ";
			std::string fullName;
			std::cin.ignore();
			std::getline(std::cin, fullName);
			std::cout << "������� ����� �������� ������� : ";
			double cash;
			std::cin >> cash;
			wal.setNameHolder(fullName);
			wal.setBalance(cash);

			break;
		}

		case 2:
		{
			if (wal.nameHolder() == "" && wal.balance() == 0.0)
			{
				std::cout << "��� ����������� ��������";
				break;
			}
			std::cout << R"(
	�������� �������� :
	|1|- ��������� �����.
	|2|- ��������� �����.
)";
			int card = 0;
			std::cin >> card;
			switch (card)
			{
			case 1:
			{
				std::cout << "������� �������� ����� : ";
				std::string nameBank;
				std::cin.ignore();
				std::getline(std::cin, nameBank);
				double cash;
				std::cout << "�������� �� ����� ����� ������ ����������� ����� : ";
				std::cin >> cash;
				Card* Dcard = new DebitCard(nameBank);
				Dcard->setBalance(cash);
				wal.addCard(Dcard);


				break;
			}
			case 2:
			{
				std::cout << "������� �������� ����� : ";
				std::string nameBank;
				std::cin.ignore();
				std::getline(std::cin, nameBank);
				double cash;
				std::cout << R"(�� ����� ����� ������ �������� ��������� ����� : 
	|1|-25000
	|2|-50000 
	|3|-75000
	|4|-100000)"<<std::endl;
				std::cout << "�������� : ";
				std::cin >> cash;
				cash *= 25000;
				Card* Ccard = new CreditCard(nameBank);
				Ccard->setBalance(cash);
				wal.addCard(Ccard);
				break;
			}
			}
			break;
		}
		case 3:
		{
			if (wal.nameHolder() == "" && wal.balance() == 0.0)
			{
				std::cout << "��� ����������� ��������";
				break;
			}
			menu(wal);
			break;
		}
		case 4:
			exit(0);
			break;
		}
	}
}



int main() {

	srand(time(nullptr));
	setlocale(LC_ALL, "rus");

	start();

	return 0;
}
