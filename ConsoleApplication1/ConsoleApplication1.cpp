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

			throw std::runtime_error("������������ ������� �� �����.");
		}
		catch (const std::exception& e) 
		{
			std::cout << "������: " << e.what() << std::endl;
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

	std::cout << "����� ����� 1: " << firstAccount.GetAccountNumber() << std::endl;
	std::cout << "����� ����� 2: " << secondAccount.GetAccountNumber() << std::endl;

	std::cout << "������ ����� 1: " << firstAccount.GetBalance() << std::endl;
	std::cout << "������ ����� 2: " << secondAccount.GetBalance() << std::endl;

	if (Transfer(firstAccount, secondAccount, 200.0))
		std::cout << "������� �������� �������!" << std::endl;
	else
		std::cout << "������ ��������." << std::endl;

	std::cout << "������ ����� 1 ����� ��������: " << firstAccount.GetBalance() << std::endl;
	std::cout << "������ ����� 2 ����� ��������: " << secondAccount.GetBalance() << std::endl;

	std::cout << "���������� ������ ��� ����� 1: " << firstAccount.GetInterest() << std::endl;
	std::cout << "���������� ������ ��� ����� 2: " << secondAccount.GetInterest() << std::endl;

	firstAccount.Deposit(500.0);
	secondAccount.Deposit(1000.0);

	std::cout << "������ ����� 1 ����� ��������: " << firstAccount.GetBalance() << std::endl;
	std::cout << "������ ����� 2 ����� ��������: " << secondAccount.GetBalance() << std::endl;

	firstAccount.Withdraw(500.0);
	secondAccount.Withdraw(500.0);

	std::cout << "������ ����� 1 ����� ������: " << firstAccount.GetBalance() << std::endl;
	std::cout << "������ ����� 2 ����� ������: " << secondAccount.GetBalance() << std::endl;

	firstAccount.SetInterestRate(10.0);
	secondAccount.SetInterestRate(15.0);

	std::cout << "���������� ������ ��� ����� 1 ����� ���������: " << firstAccount.GetInterest() << std::endl;
	std::cout << "���������� ������ ��� ����� 2 ����� ���������: " << secondAccount.GetInterest() << std::endl;

	return 0;
}
