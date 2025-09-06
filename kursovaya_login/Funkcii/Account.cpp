
#include<string>;

#include <nlohmann/json.hpp>
//#include "../libs/json/include/nlohmann/json.hpp"

class Account {
public:
	std::string login;
	std::string password;
	std::string sault;
	int role;
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
	~Account(){}
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Account, login, password, sault, role) //чтобы можно было преобразовать json строки в объекты типа класса
};
