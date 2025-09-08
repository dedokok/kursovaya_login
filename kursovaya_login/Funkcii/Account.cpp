
#include<string>;

#include <nlohmann/json.hpp>
//#include "../libs/json/include/nlohmann/json.hpp"

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
		case 2: { password = strParam; break; }
		case 3: { sault = strParam; break; }
		}
	}
	//метод установки числовых параметров по индексу + перегрузка
	void setParam(int intParam, int indexParam) {
		switch (indexParam) {
		case 1: { role = intParam; break; }
		}
	}

	//метод получения строковых параметров по индексу
	std::string getStrParam(int indexParam) {
		switch (indexParam) {//выбор параметра для изменения
		case 1: { return login; }
		case 2: { return password; }
		case 3: { return sault; }
		}
		return "-";
	}

	//метод получения числовых параметров
	int getIntParam(int indexParam) {
		switch (indexParam) {//выбор параметра для изменения
		case 1: { return role; }
		}
		return -1;
	}


	//метод установки числовых параметров по индексу + перегрузка
	int setParam(int indexParam) {
		switch (indexParam) {
		case 1: { return role; }
		}
		return -1;
	}
	~Account(){}
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Account, login, password, sault, role) //чтобы можно было преобразовать json строки в объекты типа класса
};
