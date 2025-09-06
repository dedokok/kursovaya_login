
#include "ModulAdministrator.h";
#include "../../IndividualZadanie/Individual.h";

//функиця вывода всех пользователей
void printUserList(std::vector<Account> &vectorAccounts) {
	for (int i = 0; i < vectorAccounts.size(); i++) {
		std::cout << i << ". " << vectorAccounts[i].login << " " << vectorAccounts[i].role << std::endl;
	 }
	std::cout << std::endl;
}




//функция вызова функции изменения учётной записи
void changeAccount(std::vector<Account>& vectorAccounts, int indexAccount) {
	int vibor;
	std::cout << "Что хотите сделать с аккаунтом?\n1. Изменить пароль\n2. Изменить логин\n3. Изменить роль\n4. Изменить соль\n0.Назад\n";
	std::cin >> vibor;
	std::string new_data;
	std::cout << "Введите новые данные:\n";
	switch (vibor) {
	case -1:break;
	case 0: return;
	case 1: {
		std::cin >> new_data;
		SHA256 sha256;
		vectorAccounts[indexAccount].password = sha256(new_data + vectorAccounts[indexAccount].sault);
		break;
	}
	case 2: {
		std::cin >> new_data;
		vectorAccounts[indexAccount].login = new_data;
		break;
	}
	case 3: {
		int new_role;
		std::cin >> new_role;
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
		if (zapisAccount("-", "-", -1, vectorAccounts, true)) {
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
		std::cout << "Выберите пункт меню:\n1.Просмотр всех учётных записей\n2. Добавление учётной записи\n3. Редактирование учётной записи\n4.Удаление учётной записи\n0.Назад\n";
		std::cin >> vibor;
		switch (vibor) {
		case 0: return;
		case 1:
		{
			printUserList(vectorAccounts);
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
		std::cout << "Выберите один из вариантов:\n1.Покупка билета (инд.задание)\n2.Поиск\n3.Сортировка\n0.Назад\n";
		std::cin >> vibor;
		switch (vibor) {
		case 0: return;
		case 1: {
			buyTicket(ticketList);
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
	bool isRunEM = true;
	while (isRunEM) {
		std::cout << "Выберите один из вариантов:\n1.Просмотр\n2.Добавление\n3.Редактирование\n4.Удаление\n0.Назад\n";
		std::cin >> vibor;
		switch (vibor) {
		case 0: return;
		case 1: {
			printShapka();
			printTickets(ticketList, 0, -1);
			break;
		}
		case 2: {
			addZapis(ticketList) == true ? printMessage(6) : printMessage(1);
			break;
		}
		case 3: {
			editZapis(ticketList) == true ? printMessage(7) : printMessage(1);
			break;
		}
		case 4: {
			deleteZapis(ticketList) == true ? printMessage(5) : printMessage(1);
			break;
		}
		}
	}
}

void chooseMode() {
	int viborMode = 0;
	std::cout << "Выберите режим:\n1.Режим редактирования\n2.Режим обработки\n0.Назад\n";
	std::cin >> viborMode;
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





//запуск меню администратора
int startAdministrator(std::vector<Account> &vectorAccounts, int accountIndex) {
	int vibor;
	while (true) {
		std::cout << "Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n0.Выход\n";
		std::cin >> vibor;
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