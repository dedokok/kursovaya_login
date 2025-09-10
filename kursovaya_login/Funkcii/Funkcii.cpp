#include "Funkcii.h"

//прототипы функций
std::string saultGen();
void isThereBD();
int checkLogin(std::string v_login, std::string v_password, std::vector<Account>& vectorAccounts);
std::vector<Account> getAccounts();
bool zapisAccount(std::string login, std::string password, int role, std::vector<Account>& vectorAccounts, bool isChange);

//функция вывода шапки
void printShapkaAccounts() {
	printf("----------------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |     Логин       |                              Хеш                                 |    Соль    | Роль |\n");
	printf("|  №  |                 |                                                                  |            |      |\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
}

//функция вывода аккаунтов
void printAccounts(std::vector<Account>& vectorAccounts, int startI, int kolvoPrint) {
	if (kolvoPrint == -1) { kolvoPrint = vectorAccounts.size(); }
	for (int i = startI; kolvoPrint - i > 0; i++) {
		Account acc = vectorAccounts[i];
		acc.printTable(i);
		printf("----------------------------------------------------------------------------------------------------------------\n");
	}
}


void printErrorMessage(int messageCode) {
	std::string message = "Ошибка!\n";
	switch (messageCode) {
	case 1: { message = "Такой рейс уже есть!\n\n"; break; }
	case 2: { message = "Ничего не найдено\n\n"; break; }
	case 3: { message = "\nСлишком длинный ник (максимум 15 букв)!\n\n"; break; }
	case 4: { message = "\nТакой аккаунт уже существует!\n\n"; break; }
	case 5: { message = "На данный рейс нет такого количества билетов, но есть билеты бизнес класса в количестве"; break; }
	case 6: { message = "На данный рейс нет такого количества билетов, но есть билеты эконом класса в количестве "; break; }
	case 7: { message = "Не удалось войти\n"; break; }
	case 8: { message = "Неправильная роль!\n"; break; }
	case 9: { message = "Ошибка! Файл пустой!\n"; break; }
	case 10: { message = "Неправильное значение рейса (минимум 0, максимум 999)\n"; break; }
	case 11: { message = "Неправильный тип самолёта(максимум 15, латиница)\n"; break; }
	case 12: { message = "Неправильный пункт назначения(максимум 15, латиница)\n"; break; }
	case 13: { message = "Неправильный формат даты (надо dd.mm.yyyy)\n"; break; }
	case 14: { message = "Неправильный формат времени вылета(надо HH:MM:SS)\n"; break; }
	case 15: { message = "Неправильный формат времени прилёта(надо HH:MM:SS)\n"; break; }
	case 16: { message = "Неправильная вместимость(мин.0, макс. 999)\n"; break; }
	case 17: { message = "Неправильное количество билетов бизнес класса(мин. 0, макс. 999)\n"; break; }
	case 18: { message = "Неправильное количество билетов эконом класса(мин. 0, макс. 999)\n"; break; }
	case 19: { message = "Неправильная цена билета бизнес класса(мин. 0, макс. 9999)\n"; break; }
	case 20: { message = "Неправильная цена билета эконом класса(мин. 0, макс. 9999)\n"; break; }
	}
	std::cout << message;
}


//функция вывода повторяющихся в нескольких местах сообщений
void printMessage(int messageCode) {
	std::string message = "Ошибка\n";
	switch (messageCode) {
	case 1: { message = "Успешно удалил\n\n"; break; }
	case 2: { message = "Успешно добавил\n\n"; break; }
	case 3: { message = "Успешно изменил\n\n"; break; }
	case 4: { message = "Успешная покупка!\n"; break; }
	case 5: { message = "Вошёл успешно!\n"; break; }
	case 6: { message = "Введите пароль\n"; break; }
	case 7: { message = "Введите пункт назначения (латиницей)\n"; break; }
	case 8: { message = "Введите роль\n"; break; }
	case 9: { message = "Введите номер рейса\n"; break; }
	case 10: { message = "Введите тип самолёта\n"; break; }
	case 11: { message = "Введите пункт назначения (латиницей)\n"; break; }
	case 12: { message = "Введите день вылета\n"; break; }
	case 13: { message = "Введите время вылета\n"; break; }
	case 14: { message = "Введите время прилёта\n"; break; }
	case 15: { message = "Введите вместимость самолёта\n"; break; }
	case 16: { message = "Введите количество билетов бизнес класса\n"; break; }
	case 17: { message = "Введите стоимость билета бизнес класса\n"; break; }
	case 18: { message = "Введите количество билетов эконом класса\n"; break; }
	case 19: { message = "Введите стоимость билета эконом класса\n"; break; }
	case 21: { message = "Введите количество билетов\n"; break; }
	case 22: { message = "Введите класс билета : \n1.Бизнес\n2.Эконом\n"; break; }
	case 23: { message = "Введите стоимость\n"; }
	case 24: { message = "Введите новый логин\n"; break; }
	case 25: { message = "Введите новый пароль\n"; break; }
	case 26: { message = "Введите новую роль\n"; break; }
	case 27: { message = "\nВы действительно хотите это сделать? (Y/n)\n"; break; }
	case 28: { message = "Введите индекс нужной учётной записи\n"; break; }
	case 29: { message = "Успешная отмена действия!\n"; break; }
	case 30: { message = "Введите логин\n"; break; }
	case 31: { message = "Введите стоимость билета бизнес класса\n"; break; }
	}
	std::cout << message;
}

//функция получения какой-либо информации (полиморфизм)
//template <class T>
//void printSomeInfo(T const& p) {
//	std::cout << p.printSomeInfo();
//}

//функция вывода сообщений при выборе из нескольких вариантов
void printViborMessage(int messageCode) {
	std::string message = "Ошибка";
	switch (messageCode) {
	case 1: { message = "Введите класс билета : \n1.Бизнес\n2.Эконом\n"; break; }
	case 2: { message = "Введите, по какому полю будете искать : \n1. Тип самолёта\n2. Пункт назначения\n3. Стоимость билета\n0. Назад\n"; break; }
	case 3: { message = "Введите, в каком классе искать\n1.Бизнес\n 2.Эконом\n3.Во всех\n0.Назад\n"; break; }
	case 4: { message = "Введите, больше или меньше какой-то цены\n1.Больше\n2.Меньше\n0.Назад\n"; break; }
	case 5: { message = "Выберите, по чём сортировать:\n1.Цене билетов бизнес класса\n2.Цене билетов эконом класса\n3.Количеству билетов бизнес класса\n4.Количеству билетов эконом класса\n0.Назад\n"; break;}
	case 6: { message = "Что хотите сделать с аккаунтом?\n1. Изменить пароль\n2. Изменить логин\n3. Изменить роль\n4. Изменить соль\n0.Назад\n"; break; }
	case 7: { message = "\nВыберите пункт меню:\n1.Просмотр всех учётных записей\n2.Добавление учётной записи\n3.Редактирование учётной записи\n4.Удаление учётной записи\n5.Получить информацию об учётной записи\n0.Назад\n"; break; }
	case 8: { message = "Выберите один из вариантов:\n1.Покупка билета (инд.задание)\n2.Поиск\n3.Сортировка\n4.Получить информацию о билете\n0.Назад\n"; break; }
	case 9: { message = "Выберите один из вариантов:\n1.Просмотр\n2.Добавление\n3.Редактирование\n4.Удаление\n0.Назад\n"; break; }
	case 10: { message = "Выберите режим:\n1.Режим редактирования\n2.Режим обработки\n0.Назад\n"; break; }
	case 11: { message = "Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n0.Выход\n"; break; }
	case 12: { message = "Выберите пункт меню:\n1.Просмотр\n2.Покупка билета (инд. задание)\n3.Поиск\n4.Сортировка\n5.Получить информацию о билете\n0.Выход\n"; break; }
	case 13: { message = "Выберите, что изменить:\n1.Номер рейса\n2.Тип самолёта\n3.Пункт назначения\n4.Дата вылета\n5.Время вылета\n6.Время прилёта\n7.Вместимость самолёта\n8.Количество билетов бизнес класса\n9.Стоимость билета бизнес класса\n11.Количество билетов эконом класса\n12.Стоимость билета эконом класса\n0.Назад\n"; break; }
	}
	std::cout << message;
}



//функция вывода шапок
void printShapka(int shapkaIndex) {
	switch (shapkaIndex) {
	case 1: { std::cout << "\n\n-------------Меню администратора-------------\n\n"; break; }
	case 2: { std::cout << "\n\n--------------Меню пользователя--------------\n\n"; break; }
	case 3: { std::cout << "\n\n---------------Меню сортировки---------------\n\n"; break; }
	case 4: { std::cout << "\n\n-----------------Меню поиска-----------------\n\n"; break; }
	case 5: { std::cout << "\n\n----------------Покупка билета---------------\n\n"; break; }
	case 6: { std::cout << "\n\n-----Меню редактирования учётной записи------\n\n"; break; }
	case 7: { std::cout << "\n\n--------Меню удаления учётной записи---------\n\n"; break; }
	case 8: { std::cout << "\n\n-------------Меню удаления рейса-------------\n\n"; break; }
	case 9: { std::cout << "\n\n------------Меню добавления рейса------------\n\n"; break; }
	case 10: { std::cout << "\n\n---------Меню редактирования рейса-----------\n\n"; break; }
	case 11: { std::cout << "----------------Авторизация-----------------\n\n"; break; }
	case 12: { std::cout << "\n\n------Добавление нового пользователя---------\n\n"; break; }
	case 13: { std::cout << "\n\n-----------Режим редактирования--------------\n\n"; break; }
	case 14: { std::cout << "\n\n----------Режим обработки данных-------------\n\n"; break; }
	case 15: { std::cout << "\n\n--------Работа с учётными записями-----------\n\n"; break; }
	case 16: { std::cout << "\n\n-------------Работа с данными----------------\n\n"; break; }
	}
}

//функция вывода
void coutFunc(std::string message) {
	std::cout << message;
}


//функция ввода числа (1 - просто сообщения, 2 - сообщения при выборе)
int inputInt(int messCode, int messType) {
	if (messType == 1) {
		printMessage(messCode);
	}
	else if (messType == 2) {
		printViborMessage(messCode);
	}
	else if (messType == 3) {
		printErrorMessage(messCode);
	}
	else { return -1; }
	std::string inputedInt;
	std::cin >> inputedInt;
	try {
		return std::stoi(inputedInt);
	}
	catch (...) {
		printErrorMessage(-1);
		return -1;
	}
}


//функция проверки, правильно ли введена строка (нет ли плохих символов)
bool checkCorrStr(std::string strokaForCheck) {
	if (strokaForCheck.length() > 15 || strokaForCheck.length()<=0) { return 0; }
	for (int i = 0; i < strokaForCheck.length(); i++) {
		if (strokaForCheck[i] < 0) {
			return 0;
		}
	}
	return 1;
}

//функция ввода числа по ссылке
bool inputIntSsilka(int messCode, int &parametr, int messType) {
	if (messType == 1) {
		printMessage(messCode);
	}
	else if (messType == 2) {
		printViborMessage(messCode);
	}
	std::string inputtedInt;
	std::cin >> inputtedInt;
	try {
		parametr = std::stoi(inputtedInt);
		return 1;
	}
	catch (...) {
		printErrorMessage(-1);
		return 0;
	}
	return 0;
}


//функция ввода строки
std::string inputStr(int messCode, int messType) {
	std::string prompt;
	if (messType == 1) {
		printMessage(messCode);
	}
	else if (messType == 2) {
		printViborMessage(messCode);
	}
	std::cin >> prompt;
	if (checkCorrStr(prompt)) {
		return prompt;
	}
	else { return "-"; }
}


//функция ввода строки по ссылке
bool inputStrSsilka(int messCode, std::string &stroka, int messType) {
	if (messType == 1) {
		printMessage(messCode);
	}
	else if (messType == 2) {
		printViborMessage(messCode);
	}
	std::cin >> stroka;
	if (checkCorrStr(stroka)){
		return true;
	}
	else { stroka = "-"; }
	return false;
}


//функция начала регистрации(ввод данных с клавиатуры и вызов функции добавления в файл)
std::vector<Account> inputNewAccountData(std::vector<Account>vectorAccounts, bool isAdministrator) {
	std::string new_login, new_password;
	int new_role=0;
	//if (!isAdministrator) {
	//	vectorAccounts = getAccounts();
	//}
	new_login = inputStr(24,1);
	std::transform(new_login.begin(), new_login.end(), new_login.begin(), ::tolower);
	if (new_login == "-") { 
		printErrorMessage(-1);
		return vectorAccounts; 
	}
	else if (checkIfInDB(new_login,vectorAccounts) != -1) {
		printErrorMessage(4);
		return vectorAccounts;
	}
	else if (new_login.length() > 16) {
		printErrorMessage(3);
		return vectorAccounts;
	}
	new_password = inputStr(25,1);
	if (new_password == "-") {
		return vectorAccounts;
	}
	if (!isAdministrator) {
		new_role = inputInt(26,1);
		if (new_role != 1 && new_role != 2) {
			printErrorMessage(8);
			return vectorAccounts;
		}
	}
	else {
		new_role = 1;
	}
	if (zapisAccount(new_login, new_password, new_role, vectorAccounts, false)) {
		printMessage(2);
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
	int accountIndex = checkIfInDB(v_login, vectorAccounts);
	if (accountIndex != -1 && vectorAccounts.size()>0) {
		if (vectorAccounts[accountIndex].isSimilarPass(v_password)) {
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
	printShapka(11);
	login = inputStr(30,1);
	printMessage(6);
	password = vvodParol();
	std::cout << std::endl;
	accountIndex= checkLogin(login, password, vectorAccounts);
	if (accountIndex!=-1) {
		//printMessage(16);
		return accountIndex;
	}
	else {
		printErrorMessage(7);
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
		printErrorMessage(9);

		vectorAccounts = inputNewAccountData(vectorAccounts,true);
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
		std::vector<Account> vectorAccounts;
		inputNewAccountData(vectorAccounts,true);
	}
}


//функция проверки, есть ли такой аккаунт в базе данных (при регистрации). Если есть - возвращаю номер в векторе, иначе -1
int checkIfInDB(std::string login,std::vector<Account>&vectorAccounts) {
	std::transform(login.begin(), login.end(), login.begin(), ::tolower); //превращаю логин в ловеркейс
	for (int i = 0; i < vectorAccounts.size(); i++) {
		if (vectorAccounts[i].isSimilarLogin(login)) {
			return i;
		}
	}
	return -1;
}