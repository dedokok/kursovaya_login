#include "ModulAdministrator.h";
#include "../../IndividualZadanie/Individual.h";


//функция вызова функции изменения учётной записи
void changeAccount(std::vector<Account>& vectorAccounts, int indexAccount) {
	int vibor = inputInt("Что хотите сделать с аккаунтом?\n1. Изменить пароль\n2. Изменить логин\n3. Изменить роль\n4. Изменить соль\n0.Назад");
	if (vibor == -1)return;
	std::string new_data;
	std::cout << "Введите новые данные:\n";
	switch (vibor) {
	case 0: return;
	case 1: {
		std::cin >> new_data;
		SHA256 sha256;
		vectorAccounts[indexAccount].password = sha256(new_data + vectorAccounts[indexAccount].sault);
		break;
	}
	case 2: {
		new_data = inputStr("Введите логин");
		if (checkIfInDB(new_data, vectorAccounts) == -1) {
			if (new_data.length() > 16) {
				printMessage(10);
				return;
			}
			vectorAccounts[indexAccount].login = new_data;
		}
		else {
			std::cout << "Такой аккаунт уже есть!\n";
			return;
		}
		break;
	}
	case 3: {
		int new_role = inputInt("Введите роль");
		vectorAccounts[indexAccount].role = new_role;
		break;
	}
	case 4: {
		std::cout << "новый пароль учётной записи(для соли)\n";
		std::cin >> new_data;
		SHA256 sha256;
		vectorAccounts[indexAccount].sault = saultGen();
		vectorAccounts[indexAccount].password = sha256(new_data + vectorAccounts[indexAccount].sault);
		break;
	}
	}
	if (zapisAccount("-", "-", -1, vectorAccounts, true) && vibor > 0 && vibor < 5) {
		std::cout << "\nУспешно изменил данные\n\n";
	}
}


//подтверждение действия
bool getAccept() {
	std::string accept;
	std::cout << "Вы действительно хотите это сделать? (Y/n)\n";
	std::cin >> accept;
	if (accept == "Y") { return 1; }
	else if (accept == "n") { std::cout << "Успешная отмена действия\n"; return 0; }
	else { printMessage(1); return 0; }
}


//функция ввода индекса аккаунта
int printAccIndex() {
	int indexAccount;
	std::cout << "Введите индекс нужной учётной записи\n";
	std::cin >> indexAccount;
	return indexAccount;
}


//функция удаления учётной записи
void deleteAccount(std::vector<Account> &vectorAccounts,int indexDeleteAccount, int indexNowAccount){
	if (indexDeleteAccount > -1 && indexDeleteAccount < vectorAccounts.size() && indexDeleteAccount != indexNowAccount) {
		auto begin = vectorAccounts.cbegin();
		auto end = vectorAccounts.cend();
		vectorAccounts.erase(begin + indexDeleteAccount);
		if (getAccept() && zapisAccount("-", "-", -1, vectorAccounts, true)) {
			std::cout << "\nУспешно удалил\n\n";
		}
	}
	else {
		std::cout << "Ошибка\n";
	}
}



void rabotaWithAccounts(std::vector<Account>& vectorAccounts, int accountIndex) {
	bool isRunUchZap = true;
	while (isRunUchZap) {
		int vibor;
		std::cout << "Выберите пункт меню:\n1.Просмотр всех учётных записей\n2.Добавление учётной записи\n3.Редактирование учётной записи\n4.Удаление учётной записи\n0.Назад\n";
		std::cin >> vibor;
		switch (vibor) {
		case 0: return;
		case 1:
		{
			//printUserList(vectorAccounts);
			printShapkaAccounts();
			printAccounts(vectorAccounts, 0, -1);
			break;
		}
		case 2:
		{
			vectorAccounts = inputNewAccountData(false);
			
			break;
		}
		case 3:
		{
			changeAccount(vectorAccounts, printAccIndex());
			break;
		}
		case 4:
		{

			deleteAccount(vectorAccounts, printAccIndex(), accountIndex);
		}
		}
	}
}



void processMode() {
	int vibor;
	std::vector<Ticket> ticketList = getTickets();
	bool isRunPM = true;
	while (isRunPM) {
		vibor = inputInt("Выберите один из вариантов:\n1.Покупка билета (инд.задание)\n2.Поиск\n3.Сортировка\n0.Назад");
		switch (vibor) {
		case 0: return;
		case 1: {
			if (buyTicket(ticketList)) {
				zapisTickets(ticketList);
			}
			break;
		}
		case 2: {
			poiskTicket(ticketList);
			break;
		}
		case 3: {
			sortTicket(ticketList);
			break;
		}
		}
	}
}


//основная функция режима редактирования в "Работа с данными"
void editMode() {
	int vibor;
	std::vector<Ticket> ticketList = getTickets();
	while (true) {
		vibor = inputInt("Выберите один из вариантов:\n1.Просмотр\n2.Добавление\n3.Редактирование\n4.Удаление\n0.Назад");
		switch (vibor) {
		case 0: return;
		case 1: {
			printShapka();
			printTickets(ticketList, 0, -1);
			break;
		}
		case 2: {
			if (addZapis(ticketList))printMessage(6);
			break;
		}
		case 3: {
			if(editZapis(ticketList))printMessage(7);
			break;
		}
		case 4: {
			if (deleteZapis(ticketList))printMessage(5);
			break;
		}
		}
	}
}

void chooseMode() {
	int viborMode = 0;
	while (true) {
		viborMode = inputInt("Выберите режим:\n1.Режим редактирования\n2.Режим обработки\n0.Назад");
		switch (viborMode) {
		case 0: return;
		case 1: {
			editMode();
			break;
		}
		case 2: {
			processMode();
			break;
		}
		}
	}
}


//запуск меню администратора
int startAdministrator(std::vector<Account> &vectorAccounts, int accountIndex) {
	int vibor;
	while (true) {
		vibor = inputInt("Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n0.Выход");
		switch (vibor) {
		case 0:return 1;
		case 1:
		{
			rabotaWithAccounts(vectorAccounts, accountIndex);
			break;
		}
		case 2: {
			chooseMode();
			break;
		}
		}
	}
	return 0;
}