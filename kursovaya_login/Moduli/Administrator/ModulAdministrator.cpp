#include "../../IndividualZadanie/Individual.h";
#include "ModulAdministrator.h";


//функция ввода индекса аккаунта
int inputAccIndex() {
	int indexAccount;
	indexAccount = inputInt(28, 1);
	return indexAccount;
}

//функция получения и отправки нового пароля
void getSendNewPassword(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data=inputStr(25, 1); 
	if (new_data == "-") {
		printErrorMessage(-1);
		return;
	}
	vectorAccounts[indexAccount].setParam(new_data, 2);
	return;
}


//функция получения и отправки нового логина
void getSendNewLogin(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data=inputStr(24, 1);
	if (new_data == "-") {
		return;
	}
	std::transform(new_data.begin(), new_data.end(), new_data.begin(), ::tolower);
	if (checkIfInDB(new_data, vectorAccounts) == -1) {
		if (new_data.length() > 16) {
			printErrorMessage(3);
			return;
		}
		vectorAccounts[indexAccount].setParam(new_data, 1);
	}
	else {
		printErrorMessage(4);
		return;
	}
}


//функция получения и отправки новой роли
void getSendNewRole(std::vector<Account>& vectorAccounts, int indexAccount) {
	int new_role = inputInt(26, 1);
	vectorAccounts[indexAccount].setParam(new_role, 1);
}


//функция получения и отправки новой соли и пароля(т.к. соль изменилась, а старый пароль не узнать)
void getSendNewSault(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data = inputStr(25, 1);
	if (new_data == "-") {
		return;
	}
	vectorAccounts[indexAccount].setParam(saultGen(), 3);
	vectorAccounts[indexAccount].setParam(new_data, 2);
}


//метод вывода информации об аккаунте (полиморфизм)
void printAccInfo(std::vector<Account>& vectorAccounts) {
	int accIndex = inputAccIndex();
	if (accIndex > 0 && accIndex < vectorAccounts.size()) {
		Account account = vectorAccounts[accIndex];
		printSomeInfo(account);
	}
	else {
		printErrorMessage(2);
	}
}




//функция вызова функции изменения учётной записи
void changeAccount(std::vector<Account>& vectorAccounts, int indexAccount) {
	if (indexAccount == -1) { return; }
	int vibor = inputInt(6,2);
	if (vibor == -1 || vibor == 0) { return; }
	std::string new_data;
	switch (vibor) {//цель кейса
	case 1: {
		getSendNewPassword(vectorAccounts, indexAccount);
		break;
	}
	case 2: {
		getSendNewLogin(vectorAccounts, indexAccount);
		break;
	}
	case 3: {
		getSendNewRole(vectorAccounts, indexAccount);
		break;
	}
	case 4: {
		getSendNewSault(vectorAccounts, indexAccount);
		break;
	}
	}
	if (zapisAccount("-", "-", -1, vectorAccounts, true) && vibor > 0 && vibor < 5) {
		printMessage(3);
	}
}


//подтверждение действия
bool getAccept() {
	std::string accept;
	accept = inputStr(27,1);
	if (accept == "Y") { return 1; }
	else if (accept == "n") { printMessage(29); return 0; }
	else { printErrorMessage(-1); return 0; }
}




//функция удаления учётной записи
void deleteAccount(std::vector<Account> &vectorAccounts,int indexDeleteAccount, int indexNowAccount){
	if (indexDeleteAccount > -1 && indexDeleteAccount < vectorAccounts.size() && indexDeleteAccount != indexNowAccount) {
		auto begin = vectorAccounts.cbegin();
		auto end = vectorAccounts.cend();
		vectorAccounts.erase(begin + indexDeleteAccount);
		if (getAccept() && zapisAccount("-", "-", -1, vectorAccounts, true)) {
			printMessage(1);
		}
	}
}


//режим работы с аккаунтами
void rabotaWithAccounts(std::vector<Account>& vectorAccounts, int accountIndex) {
	bool isRunUchZap = true;
	while (isRunUchZap) {
		int vibor;
		vibor = inputInt(7,2);
		switch (vibor) {
		case -1: return;
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
			vectorAccounts = inputNewAccountData(vectorAccounts,false);
			break;
		}
		case 3:
		{
			printShapka(6);
			changeAccount(vectorAccounts, inputAccIndex());
			break;
		}
		case 4:
		{
			printShapka(7);
			deleteAccount(vectorAccounts,inputAccIndex(), accountIndex);
		}
		case 5: {
			printAccInfo(vectorAccounts);
			break;
		}
		}
	}
}


//режим обработки данных
void processMode() {
	int vibor;
	
	std::vector<Ticket> ticketList = getTickets();
	bool isRunPM = true;
	while (isRunPM) {
		printShapka(14);
		vibor = inputInt(8,2);
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
		case 4: {
			printTicketInfo(ticketList);
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
		vibor = inputInt(9,2);
		switch (vibor) {
		case 0: return;
		case 1: {
			printShapkaProsmotr();
			printTickets(ticketList, 0, -1);
			break;
		}
		case 2: {
			printShapka(9);
			if (addNewZapis(ticketList))printMessage(2);
			break;
		}
		case 3: {
			printShapka(10);
			if(editZapis(ticketList))printMessage(3);
			break;
		}
		case 4: {
			printShapka(8);
			if (deleteZapis(ticketList))printMessage(1);
			break;
		}
		}
	}
}


//функция выбора режима
void chooseMode() {
	int viborMode = 0;
	while (true) {
		printShapka(16);
		viborMode = inputInt(10,2);
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




//реализую метод startAdminMenu
bool Administrator::startAdminMenu(std::vector<Account>&vectorAccounts, int accountIndex) {
	int vibor;
	printShapka(1);
	while (true) {
		vibor = inputInt(11, 2);
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


//запуск меню администратора
int startAdministrator(std::vector<Account> &vectorAccounts, int accountIndex) {
	Administrator admin;
	admin.startAdminMenu(vectorAccounts, accountIndex);
	return 1;
}