#include "../../IndividualZadanie/Individual.h";
#include "ModulAdministrator.h";



//функция вызова функции изменения учётной записи
void changeAccount(std::vector<Account>& vectorAccounts, int indexAccount) {
	int vibor = inputInt("Что хотите сделать с аккаунтом?\n1. Изменить пароль\n2. Изменить логин\n3. Изменить роль\n4. Изменить соль\n0.Назад");
	if (vibor == -1 || vibor==0)return;
	
	std::string new_data;
	switch (vibor) {//цель кейса
	case 1: {
		new_data = inputStr("Введите новый пароль:\n");
		if (new_data == "-") {
			printMessage(1);
			return;
		}
		SHA256 sha256;
		vectorAccounts[indexAccount].setParam(sha256(new_data + vectorAccounts[indexAccount].getStrParam(3)),2);
		break;
	}
	case 2: {
		new_data = inputStr("Введите новый логин:");
		if (new_data == "-") {
			printMessage(1);
			return;
		}
		if (checkIfInDB(new_data, vectorAccounts) == -1) {
			if (new_data.length() > 16) {
				printMessage(10);
				return;
			}
			vectorAccounts[indexAccount].setParam(new_data,1);
		}
		else {
			printMessage(11);
			return;
		}
		break;
	}
	case 3: {
		int new_role = inputInt("Введите роль");
		vectorAccounts[indexAccount].setParam(new_role,1);
		break;
	}
	case 4: {
		new_data = inputStr("новый пароль учётной записи(для соли)\n");
		if (new_data == "-") {
			printMessage(1);
			return;
		}
		SHA256 sha256;
		vectorAccounts[indexAccount].setParam(saultGen(), 3);
		vectorAccounts[indexAccount].setParam(sha256(new_data + vectorAccounts[indexAccount].getStrParam(3)),2);
		break;
	}
	}
	if (zapisAccount("-", "-", -1, vectorAccounts, true) && vibor > 0 && vibor < 5) {
		printMessage(7);
	}
}


//подтверждение действия
bool getAccept() {
	std::string accept;
	std::cout << "\nВы действительно хотите это сделать? (Y/n)\n";
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
			printMessage(5);
		}
	}
	else {
		printMessage(1);
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
			printShapkaAccounts();
			printAccounts(vectorAccounts, 0, -1);
			break;
		}
		case 2:
		{
			printShapka(12);
			vectorAccounts = inputNewAccountData(false);
			break;
		}
		case 3:
		{
			printShapka(6);
			changeAccount(vectorAccounts, printAccIndex());
			break;
		}
		case 4:
		{
			printShapka(7);
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
		printShapka(14);
		vibor = inputInt("Выберите один из вариантов:\n1.Покупка билета (инд.задание)\n2.Поиск\n3.Сортировка\n0.Назад");
		switch (vibor) {
		case 0: return;
		case 1: {
			printShapka(5);
			if (buyTicket(ticketList)) {
				zapisTickets(ticketList);
			}
			break;
		}
		case 2: {
			printShapka(4);
			poiskTicket(ticketList);
			break;
		}
		case 3: {
			printShapka(3);
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
		printShapka(10);
		vibor = inputInt("Выберите один из вариантов:\n1.Просмотр\n2.Добавление\n3.Редактирование\n4.Удаление\n0.Назад");
		switch (vibor) {
		case 0: return;
		case 1: {
			printShapkaProsmotr();
			printTickets(ticketList, 0, -1);
			break;
		}
		case 2: {
			printShapka(9);
			if (addZapis(ticketList))printMessage(6);
			break;
		}
		case 3: {
			printShapka(10);
			if(editZapis(ticketList))printMessage(7);
			break;
		}
		case 4: {
			printShapka(8);
			if (deleteZapis(ticketList))printMessage(5);
			break;
		}
		}
	}
}

void chooseMode() {
	int viborMode = 0;
	while (true) {
		printShapka(16);
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
	printShapka(1);
	while (true) {
		vibor = inputInt("Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n0.Выход");
		switch (vibor) {
		case 0:return 1;
		case 1:
		{
			printShapka(15);
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