#include <iostream>
#include <string>;
#include "sha256.h" //взял библиотеку https://create.stephan-brumme.com/hash-library/ для хеширования
#include <nlohmann/json.hpp>

class Account {
private:
	std::string login;
	std::string password;
	std::string sault;
	int role;
public:
	Account() : login(""), password(""), sault(""), role(0) {} //конструктор для json
	Account(std::string v_login, std::string v_password, std::string v_sault,int v_role) {
		login = v_login;
		password = v_password;
		role = v_role;
		sault = v_sault;
	}
	void set(std::string v_login, std::string v_password, std::string v_sault,int v_role) {
		login = v_login;
		password = v_password;
		role = v_role;
		sault = v_sault;
	}


	//метод установки строковых параметров по индексу
	void setParam(std::string strParam, int indexParam) {
		switch (indexParam) {//выбор параметра для изменения
		case 1: { login = strParam; break; }
		case 2: { SHA256 sha256; password = sha256(strParam+sault); break; }
		case 3: { sault = strParam; break; }
		}
	}


	//метод установки числовых параметров по индексу + перегрузка верхнего метода
	void setParam(int intParam, int indexParam) {
		switch (indexParam) {
		case 1: { role = intParam; break; }
		}
	}


	//метод вывода строки таблицы пользователей
	void printTable(int i) {
		std::cout <<
			"| " << std::left << std::setw(3) << i <<
			" | " << std::left << std::setw(15) << login <<
			" | " << std::left << std::setw(64) << password <<
			" | " << std::left << std::setw(10) << sault <<
			" | " << std::left << std::setw(4) << role << " |\n";
		printf("----------------------------------------------------------------------------------------------------------------\n");
	}


	//метод проверки, совпадает ли введённый пароль с настоящим
	bool isSimilarPass(std::string password) {
		SHA256 sha256;
		if (sha256(password+sault) == this->password) {
			return true;
		}
		return false;
	}


	//метод проверки, совпадает ли введённый логин с логином записи
	bool isSimilarLogin(std::string login) {
		if (login == this->login) {
			return true;
		}
		return false;
	}


	//метод сравнения ролей
	bool getRole() {
		return role;
	}


	//метод вывода информации об аккаунте
	void printSomeInfo() {
		std::cout << "\nЛогин: " << login << "\nПароль: " << password << "\nРоль: " << role << "\nСоль: " << sault <<std::endl;
	}


	~Account(){}
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Account, login, password, sault, role) //чтобы можно было преобразовать json строки в объекты типа класса
};



//просто создаю классы для примера наследования с пустыми методами, которые потом реализую
class User : Account {
private:
	std::string login;
	std::string password;
public:
	bool startUserMenu();
};

class Administrator : Account {
private:
	std::string login;
	std::string password;
public:
	bool startAdminMenu(std::vector<Account>& vectorAccounts, int accountIndex);
};