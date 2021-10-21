#include<iostream>
#include<string>
#include<fstream>
#include"CreditCard.h"
#include"DebitCard.h"
#include"Wallet.h"


void otchet(Wallet& wall)
{
	int choise = 0, date = 0;
	std::cout << R"(|	Выберите отчет :
|	Формирование отчетов по затратам и категориям:
|	|1|- день
|	|2|- неделя
|	|3|- месяц
|	Формирование рейтингов по максимальным суммам:
|	|4|- ТОП-3 затраты
|	|5|- ТОП-3 категории
|	|6| - Выход в основное меню)" << std::endl;

	std::cout << "Ввод : ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
	{
		
		std::cout << "Введите число,за которое хотите просмотреть отчет : ";
		std::cin >> date;
		std::cout<< wall.report("day", date)<<"\n\n";
		std::cout << "Записать отчет в файл?(y/n) : ";
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
		std::cout << "Записать отчет в файл?(y/n) : ";
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
		std::cout << "Введите месяц ,за который хотите просмотреть отчет(1-12) : ";
		std::cin >> date;
		std::cout << wall.report("mounth", date) << "\n\n";
		std::cout << "Записать отчет в файл?(y/n) : ";
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
		std::cout << " \n |1| - Неделя \n |2| - Месяц" << std::endl;
		std::cin >> weekAndMounth;
		if (weekAndMounth == 1)
		{
			std::cout << wall.report("week", 0, 1) << "\n\n";
			std::cout << "Записать отчет в файл?(y/n) : ";
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

			std::cout << "Введите месяц,за который хотите получить статистику :";
			std::cin >> date;
			std::cout << wall.report("mounth", date, 1) << "\n\n";
			std::cout << "Записать отчет в файл?(y/n) : ";
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
		std::cout << " \n |1| - Неделя \n |2| - Месяц" << std::endl;
		std::cin >> weekAndMounth;
		if (weekAndMounth == 1)
		{
			std::cout << wall.report("week", 0, 2) << "\n\n";
			std::cout << "Записать отчет в файл?(y/n) : ";
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

			std::cout << "Введите месяц,за который хотите получить статистику :";
			std::cin >> date;
			std::cout << wall.report("mounth", date, 2) << "\n\n";
			std::cout << "Записать отчет в файл?(y/n) : ";
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
	std::cout << "Выберите категорию : ";
	std::cout << R"(
	|1|- Продукты.
	|2|- Бытовая техника.
	|3|- Одежда.
	|4|- Ресторан.
	|5|- Транспорт
	|6| -Аптека
)";
	std::cout << "Введите от 1 до 6 : ";
	std::cin >> cat;
	return  cat;
}
void pay(Wallet& wall)
{
	int choise = 0;
	std::cout << R"(	Выберите способ оплаты
	|1|-Оплатить наличными.
	|2|-Оплатить картой.)";
	std::cout << "\n\tВведите : ";
	std::cin >> choise;
	
	switch (choise) 
	{
	case 1: 
	{
		double cash = 0.0;
		std::cout << "Введите сумму оплаты : ";
		std::cin >> cash;
		if (cash > 0.0 && cash < wall.balance())
		{
			if (wall.pay(cash))
			{
				wall.addHistory(cat(), cash, "Наличные");
				std::cout << "Успех";
			}
		}
		else if (cash > wall.balance())
			std::cout << "Недостаточно наличных средств." << std::endl;
		else if (cash <= 0.0)
			 std::cout << "Некорректно веденна сумма оплаты." << std::endl;
		break;
	}
	case 2:
	{
		std::string strPay;
		double cash = 0.0;
		std::cout<< wall.ListCard();
		std::cout << "Введите последние 4 цифры карты : ";
		std::cin.ignore();
		std::getline(std::cin , strPay);
		std::cout << "Введите сумму покупки : ";
		std::cin >> cash;

		wall.payCard(cash, strPay);
		wall.addHistory(cat(), cash,"Карта :*"+strPay);
	}
	}
}
void transferMoneyCard(Wallet& wall)
{
	int choise = 0;
	std::cout << R"(	Выберите способ 
	|1|-Перевести себе на другую карту.
	|2|-Перевести другому человеку.)"; //реализовывать дополнительную карту??
	std::cout << "\n\tВведите : ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
	{
		std::string paymentCard;
		std::string receivCard;
		double cash = 0.0;
		std::cout << wall.ListCard();
		std::cout << "Введите последние 4 цифры карты c которой хотите перевести : ";
		std::cin.ignore();
		std::getline(std::cin, paymentCard);
		std::cout << "Введите последние 4 цифры карты на которую хотите перевести : ";
		std::cin.ignore();
		std::getline(std::cin, receivCard);
		std::cout << "Введите сумму покупки : ";
		std::cin >> cash;
		if (wall.payCard(cash, paymentCard))
		{
			wall.payBalanceCard(cash, receivCard);
			wall.addHistory(7, cash, "Карта *" + paymentCard);
		}
		else
			std::cout << "Проверьте правильность ввода карты и суммы перевода"<<std::endl;
		break;
	}
	case 2:
	{
		std::string paymentCard, receivCard;
		double cash = 0.0;
		std::cout << wall.ListCard();
		std::cout << "Введите последние 4 цифры карты c которой хотите перевести : ";
		std::cin.ignore();
		std::getline(std::cin, paymentCard);
		std::cout << "Введите номер карты на которую хотети совершить перевод : ";
		std::cin.ignore();
		std::getline(std::cin, receivCard);
		std::cout << "Введите сумму покупки : ";
		std::cin >> cash;
		if (wall.payCard(cash, paymentCard))
		{
			std::cout << "Операция выполнена успешно" << std::endl;
			wall.addHistory(7, cash, "Карта *" + paymentCard);
		}
		else
			std::cout << "Проверьте правильность ввода карты и суммы перевода" << std::endl;
	}
	}
}
int menu(Wallet& wall)
{
	int choise = 0;
	std::cout << "Добро пожаловать в программу управления финансами." << std::endl;
	while (choise != 8) {
		
		std::cout << R"(
	Выберите действие :
	|1|- Показать информацию о кошельке.
	|2|- Положить наличные в кошелек.
	|3|- Оплатить покупку.
	|4|- Пополнить баланс карты.
	|5|- Перевести деньги с карты.
	|6|- Отчет
	|7|- Показать историю
	|8|- Выход в основное меню
)";
		std::cout << "Введите от 1 до 8 : ";
		std::cin >> choise;
		system("cls");
		switch (choise)
		{
		case 1:
			{
				std::cout<< wall.info() << "\n\n";
				std::cout << "Записать отчет в файл?(y/n) : ";
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
			std::cout << "Введите сумму,которую хотете положить : ";
			std::cin >> cash;
			if (cash > 0.0)
			{
				wall.payBalance(cash);
				std::cout << wall.balance();
			}
			else
				std::cout << "Извините,произошла ошибка. Проверьте ввод.";
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
			std::cout << "Введите сумму,на которую хотете пополнить баланс карты : ";
			std::cin >> cash;
			std::cout << wall.ListCard();
			std::cout << "Введите последние 4 цифры карты : ";
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
			std::cout << "Записать отчет в файл?(y/n) : ";
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
	std::cout << "\t\tДобро пожаловать в программу управления финансами." << std::endl;
	while (choise != 4) {
		
		std::cout << R"(
	Выберите действие :
	|1|- Завести кошелек.
	|2|- Заказать карту и положить в кошелек(обязательно наличие действущего кошелька!).
	|3|- Началь работу с кошельком
	|4|- Выход
)";
		std::cout << "Введите от 1 до 4 : ";
		std::cin >> choise;
		system("cls");
		switch (choise)
		{
		case 1:
		{
			std::cout << "Введите полное имя имя пользователя кошелька : ";
			std::string fullName;
			std::cin.ignore();
			std::getline(std::cin, fullName);
			std::cout << "Введите сумму наличных средств : ";
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
				std::cout << "Нет действущего кошелька";
				break;
			}
			std::cout << R"(
	Выберите действие :
	|1|- Дебетовая карта.
	|2|- Кредитная карта.
)";
			int card = 0;
			std::cin >> card;
			switch (card)
			{
			case 1:
			{
				std::cout << "Введите названия банка : ";
				std::string nameBank;
				std::cin.ignore();
				std::getline(std::cin, nameBank);
				double cash;
				std::cout << "Выберите на какую сумму хотите попополнить карту : ";
				std::cin >> cash;
				Card* Dcard = new DebitCard(nameBank);
				Dcard->setBalance(cash);
				wal.addCard(Dcard);


				break;
			}
			case 2:
			{
				std::cout << "Введите названия банка : ";
				std::string nameBank;
				std::cin.ignore();
				std::getline(std::cin, nameBank);
				double cash;
				std::cout << R"(На какую сумму хотите получить кредитную карту : 
	|1|-25000
	|2|-50000 
	|3|-75000
	|4|-100000)"<<std::endl;
				std::cout << "Выберите : ";
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
				std::cout << "Нет действущего кошелька";
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
