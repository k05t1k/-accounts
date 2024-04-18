#include <iostream>

class BankAccount
{
private:
	int m_AccountNumber = { };
	double m_Balance = { };
	double m_InterestRate = { };

public:
	BankAccount(int accountNumber, double balance, double interestRate)
	{
		this->m_AccountNumber = accountNumber;
		this->m_Balance = balance;
		this->m_InterestRate = interestRate;
	}

	double Deposit(double amount)
	{
		return this->m_Balance += amount;
	}

	double Withdraw(double amount)
	{
		try 
		{
			if (amount <= this->m_Balance)
				return this->m_Balance -= amount;

			throw std::runtime_error("Недостаточно средств на счете.");
		}
		catch (const std::exception& e) 
		{
			std::cout << "Ошибка: " << e.what() << std::endl;
			return 0.0;
		}
	}

	double GetBalance()
	{
		return this->m_Balance;
	}

	double GetInterest()
	{
		return this->m_Balance * this->m_InterestRate * (1.0 / 12);
	}

	double SetInterestRate(double newRate)
	{
		return this->m_InterestRate = newRate;
	}

	int GetAccountNumber()
	{
		return this->m_AccountNumber;
	}

	friend bool Transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount);
};

bool Transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) 
{
	if (fromAccount.Withdraw(amount) != NULL) 
	{
		toAccount.Deposit(amount);
		return true;
	}
		
	return false;
}

int main()
{
	std::setlocale(LC_ALL, "rus");

	BankAccount firstAccount(12345, 1000.0, 2.5);
	BankAccount secondAccount(67890, 500.0, 5.0);

	std::cout << "Номер счёта 1: " << firstAccount.GetAccountNumber() << std::endl;
	std::cout << "Номер счёта 2: " << secondAccount.GetAccountNumber() << std::endl;

	std::cout << "Баланс счёта 1: " << firstAccount.GetBalance() << std::endl;
	std::cout << "Баланс счёта 2: " << secondAccount.GetBalance() << std::endl;

	if (Transfer(firstAccount, secondAccount, 200.0))
		std::cout << "Перевод выполнен успешно!" << std::endl;
	else
		std::cout << "Ошибка перевода." << std::endl;

	std::cout << "Баланс счёта 1 после перевода: " << firstAccount.GetBalance() << std::endl;
	std::cout << "Баланс счёта 2 после перевода: " << secondAccount.GetBalance() << std::endl;

	std::cout << "Процентная ставка для счёта 1: " << firstAccount.GetInterest() << std::endl;
	std::cout << "Процентная ставка для счёта 2: " << secondAccount.GetInterest() << std::endl;

	firstAccount.Deposit(500.0);
	secondAccount.Deposit(1000.0);

	std::cout << "Баланс счёта 1 после внесения: " << firstAccount.GetBalance() << std::endl;
	std::cout << "Баланс счёта 2 после внесения: " << secondAccount.GetBalance() << std::endl;

	firstAccount.Withdraw(500.0);
	secondAccount.Withdraw(500.0);

	std::cout << "Баланс счёта 1 после снятия: " << firstAccount.GetBalance() << std::endl;
	std::cout << "Баланс счёта 2 после снятия: " << secondAccount.GetBalance() << std::endl;

	firstAccount.SetInterestRate(10.0);
	secondAccount.SetInterestRate(15.0);

	std::cout << "Процентная ставка для счёта 1 после установки: " << firstAccount.GetInterest() << std::endl;
	std::cout << "Процентная ставка для счёта 2 после установки: " << secondAccount.GetInterest() << std::endl;

	return 0;
}
