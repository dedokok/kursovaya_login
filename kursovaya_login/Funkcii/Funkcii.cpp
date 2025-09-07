#include "Funkcii.h"

//прототипы функций
std::string saultGen();
void isThereBD();
int checkLogin(std::string v_login, std::string v_password, std::vector<Account> &vectorAccounts);
std::vector<Account> getAccounts();
bool zapisAccount(std::string login, std::string password, int role, std::vector<Account> &vectorAccounts, bool isChange);

//функция вывода шапки
void printShapkaAccounts() {
	printf("----------------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |     Логин       |                              Хеш                                 |    Соль    | Роль |\n");
	printf("|  №  |                 |                                                                  |            |      |\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
}

//функция вывода аккаунтов
void printAccounts(std::vector<Account> &vectorAccounts, int startI, int kolvoPrint) {
	if (kolvoPrint == -1) { kolvoPrint = vectorAccounts.size(); }
	for (int i = startI; kolvoPrint-i>0; i++) {
		Account acc = vectorAccounts[i];
		std::cout <<
			"| "  << std::left << std::setw(3) << i <<
			" | " << std::left << std::setw(15) << acc.login <<
			" | " << std::left << std::setw(64) << acc.password <<
			" | " << std::left << std::setw(10) << acc.sault <<
			" | " << std::left << std::setw(4) << acc.role << " |\n";
		printf("----------------------------------------------------------------------------------------------------------------\n");
	}
}

//функция вывода повторяющихся в нескольких местах сообщений
void printMessage(int messageCode) {
	switch (messageCode) {
	case 1: { std::cout << "Ошибка\n"; break; }
	case 2: { std::cout << "Ошибка ввода\n"; break; }
	case 3: { std::cout << "Ошибка вывода\n"; break; }
	case 4: { std::cout << "Такой рейс уже есть!\n"; break; }
	case 5: { std::cout << "Успешно удалил\n"; break; }
	case 6: { std::cout << "Успешно добавил\n"; break; }
	case 7: { std::cout << "Успешно изменил\n"; break; }
	case 9: { std::cout << "Ничего не найдено\n"; break; }
	case 10: { std::cout << "\nСлишком длинный ник (максимум 15 букв)!\n\n"; break; }
	}
}


//функция ввода числа
int inputInt(std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> prompt;
	try {
		return std::stoi(prompt);
	}
	catch (...) {
		printMessage(1);
		return -1;
	}
}


//функция ввода числа по ссылке
bool inputIntSsilka(int &ticketField, std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> prompt;
	try {
		ticketField=std::stoi(prompt);
		return 1;
	}
	catch (...) {
		printMessage(1);
		return 0;
	}
	return 0;
}


//функция ввода строки
std::string inputStr(std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> prompt;
	return prompt;
}


//функция ввода строки по ссылке
void inputStrSsilka(std::string& ticketField, std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> ticketField;
}


//функция начала регистрации(ввод данных с клавиатуры и вызов функции добавления в файл)
std::vector<Account> inputNewAccountData(bool isAdministrator) {
	std::vector<Account>vectorAccounts;
	std::string new_login, new_password;
	int new_role=0;
	if (!isAdministrator) {
		vectorAccounts = getAccounts();
	}
	new_login = inputStr("Введите логин нового человека");
	if (checkIfInDB(new_login,vectorAccounts) != -1) {
		std::cout << "Такой аккаунт уже есть!\n";
		return vectorAccounts;
	}
	if (new_login.length() > 16) {
		printMessage(10);
		return vectorAccounts;
	}
	new_password = inputStr("\nВведите пароль нового человека");
	if (!isAdministrator) {
		new_role = inputInt("\nВведите роль нового человека");
		if (new_role != 1 && new_role != 2) {
			std::cout << "Неправильная роль\n";
			return vectorAccounts;

		}
	}
	else {
		new_role = 1;
	}
	if (zapisAccount(new_login, new_password, new_role, vectorAccounts, false)) {
		std::cout << "Успешно добавил нового человека\n";
	}
	return vectorAccounts;
}


//функция генерации соли
std::string saultGen() {
	std::string sault = "";
	int kolvoBukv = 10;
	for (int i = 0; i < kolvoBukv; i++) {
		if (rand() % 2 == 1) {
			sault += rand() % 26 + 'a';
		}
		else {
			sault += rand() % 26 + 'A';
		}
	}
	return sault;
}


//функция ввода пароля с заменой симолов на звёздочки
std::string vvodParol() {
	std::string pass;
	int ch = 0;
	while (true)
	{
		ch = _getch();
		if (ch == 13)
		{
			break;
		}
		if (ch == 27)
		{
			exit(0);
		}
		if (ch == 8)
		{
			if (!pass.empty()) {
				pass.erase(pass.length() - 1);
				std::cout << "\033[1D" << " " << "\033[1D";
			}
		}
		else
		{
			std::cout << '*';
			pass += (char)ch;
		}
	}
	return pass;
}


//функция чтения txt файла аккаунтов и сверки логинов и паролей
int checkLogin(std::string v_login, std::string v_password, std::vector<Account> &vectorAccounts) {
	SHA256 sha256;
	int accountIndex = checkIfInDB(v_login, vectorAccounts);
	if (accountIndex != -1 && vectorAccounts.size()>0) {
		std::string hashed_pass;
		hashed_pass = sha256(v_password + vectorAccounts[accountIndex].sault);
		if (hashed_pass == vectorAccounts[accountIndex].password) {
			return accountIndex;
		}
	}
	return -1;
}


//функция входа в аккант
int loginInAccount(std::vector<Account> &vectorAccounts) {
	bool isLogin = false;
	std::string login, password;
	int role = 0, accountIndex = -1;
	login = inputStr("Введите логин");
	std::cout << "\nВведите пароль\n";
	password = vvodParol();
	std::cout << std::endl;
	accountIndex= checkLogin(login, password, vectorAccounts);
	if (accountIndex!=-1) {
		std::cout << "Вошёл успешно!" << std::endl;
		return accountIndex;
	}
	else {
		std::cout << "Не удалось войти" << std::endl;
		return -1;
	}
}


//функция записи аккаунта в файл
bool zapisAccount(std::string login, std::string password, int role,std::vector<Account>&vectorAccounts,bool isChange) {
	if (!isChange) {
		std::string new_sault = saultGen();
		SHA256 sha256;
		Account account(login, sha256(password + new_sault), new_sault, role);
		vectorAccounts.push_back(account);
	}
	nlohmann::json j{};
	j["userList"] = vectorAccounts;
	std::ofstream out;
	out.open("database.json");
	if (out.is_open())
	{
		out << j.dump(4) << std::endl;
	}
	out.close();
	return true;
}


//функция чтения аккаунтов из файла
std::vector<Account> getAccounts() {
	std::ifstream in;
	in.open("database.json");
	std::string login, password, sault;
	std::vector<Account> vectorAccounts;
	try {
		auto j = nlohmann::json::parse(in);
		vectorAccounts = j["userList"];
		in.close();
		return vectorAccounts;
	}
	catch(...){
		in.close();
		std::cout << "Ошибка, файл пустой!\n";
		vectorAccounts = inputNewAccountData(true);
		return vectorAccounts;
	}
	return vectorAccounts;
}


//проврека, естьли база данных (если нет - создаю, принудительно регистрирую АДМИНИСТРАТОРА)
void isThereBD() {
	std::ifstream in;
	in.open("database.json");
	if (in.is_open()) {
		int checkIsEmpty;
		if (!(in >> checkIsEmpty)) {
			
		}
		in.close();
		return;
	}
	else {
		in.close();
		std::ofstream in("database.json");
		in.close();
		inputNewAccountData(true);
	}
}


//функция проверки, есть ли такой аккаунт в базе данных (при регистрации). Если есть - возвращаю номер в векторе, иначе -1
int checkIfInDB(std::string login,std::vector<Account>&vectorAccounts) {
	std::string chel_log;
	std::transform(login.begin(), login.end(), login.begin(), ::tolower); //превращаю логин в ловеркейс
	for (int i = 0; i < vectorAccounts.size(); i++) {
		chel_log = vectorAccounts[i].login;
		std::transform(chel_log.begin(), chel_log.end(), chel_log.begin(), ::tolower); 
		if (login == chel_log) {
			return i;
		}
	}
	return -1;
}