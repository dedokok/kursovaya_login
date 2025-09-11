#include "../../IndividualZadanie/Individual.h";
#include "ModulAdministrator.h";


//функция получения и отправки нового пароля
bool getSendNewPassword(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data = inputStr(25, 1);
	if (new_data != "-") {
		vectorAccounts[indexAccount].setParam(new_data, 2);
		return 1;
	}
	printErrorMessage(-1);
	return 0;
}


//функция получения и отправки нового логина
bool getSendNewLogin(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data = inputStr(24, 1);
	if (new_data == "-") {
		return 0;
	}
	std::transform(new_data.begin(), new_data.end(), new_data.begin(), ::tolower);
	if (checkIfInDB(new_data, vectorAccounts) == -1) {
		vectorAccounts[indexAccount].setParam(new_data, 1);
		return 1;
	}
	else {
		printErrorMessage(4);
	}
	return 0;
}


//функция получения и отправки новой роли
bool getSendNewRole(std::vector<Account>& vectorAccounts, int indexAccount) {
	int new_role = inputInt(26, 1);
	vectorAccounts[indexAccount].setParam(new_role, 1);
	return 1;
}


//функция получения и отправки новой соли и пароля(т.к. соль изменилась, а старый пароль не узнать)
bool getSendNewSault(std::vector<Account>& vectorAccounts, int indexAccount) {
	std::string new_data = inputStr(25, 1);
	if (new_data == "-") {
		return 0;
	}
	vectorAccounts[indexAccount].setParam(saultGen(), 3);
	vectorAccounts[indexAccount].setParam(new_data, 2);
	return 1;
}


//метод вывода информации об аккаунте (полиморфизм)
void printAccInfo(std::vector<Account>& vectorAccounts) {
	int accIndex = inputInt(28, 1);
	if (accIndex > 0 && accIndex < vectorAccounts.size()) {
		printSomeInfo(vectorAccounts[accIndex]);
	}
	else {
		printErrorMessage(2);
	}
}


//функция вызова функции изменения учётной записи
void changeAccount(std::vector<Account>& vectorAccounts,int indexAdmAccount, int indexChangeAccount) {
	if (indexChangeAccount == -1 || indexChangeAccount >= vectorAccounts.size()) {
		printErrorMessage(26);
		return; 
	}
	int vibor = inputInt(6,2);
	if (vibor == -1 || vibor == 0) { return; }
	std::string new_data;
	bool succesChange = false;
	switch (vibor) {//цель кейсаdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
	case 1: {
		succesChange = getSendNewPassword(vectorAccounts, indexChangeAccount);
		break;
	}
	case 2: {
		succesChange = getSendNewLogin(vectorAccounts, indexChangeAccount);
		break;
	}
	case 3: {
		if (indexChangeAccount != indexAdmAccount) {
			succesChange = getSendNewRole(vectorAccounts, indexChangeAccount);
		}
		else {
			printErrorMessage(25);
		}
		break;
	}
	case 4: {
		succesChange = getSendNewSault(vectorAccounts, indexChangeAccount);
		break;
	}
	default: {
		printErrorMessage(27);
	}
	}
	if (zapisAccount("-", "-", -1, vectorAccounts, true) && succesChange) {
		printMessage(3);
	}
}


//подтверждение действия
bool getAccept() {
	std::string accept;
	accept = inputStr(27,1);
	if (accept == "Y") { return 1; }
	else if (accept == "n") { printMessage(29); return 0; }
	else { printErrorMessage(27); return 0; }
}


//функция удаления учётной записи
void deleteAccount(std::vector<Account> &vectorAccounts,int indexDeleteAccount, int indexAdmAccount){
	if (indexDeleteAccount == -1&& indexDeleteAccount >= vectorAccounts.size()) { printErrorMessage(26); return; }
	if(indexDeleteAccount != indexAdmAccount) {
		auto begin = vectorAccounts.cbegin();
		auto end = vectorAccounts.cend();
		vectorAccounts.erase(begin + indexDeleteAccount);
		if (getAccept() && zapisAccount("-", "-", -1, vectorAccounts, true)) {
			printMessage(1);
		}
	}
	else { printErrorMessage(25); return; }
}


//режим работы с аккаунтами
void rabotaWithAccounts(std::vector<Account>& vectorAccounts, int indexAdmAccount) {
	while (true) {
		printShapka(15);
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
			createNewAccount(vectorAccounts,false);
			break;
		}
		case 3:
		{
			printShapka(6);
			changeAccount(vectorAccounts,indexAdmAccount, inputInt(28, 1));
			break;
		}
		case 4:
		{
			printShapka(7);
			deleteAccount(vectorAccounts, inputInt(28, 1), indexAdmAccount);
			break;
		}
		case 5: {
			printAccInfo(vectorAccounts);
			break;
		}
		default: {
			printErrorMessage(27);
		}
		}
	}
}


//режим обработки данных
void processMode() {
	int vibor;
	std::vector<Flight> flightList = getTickets();
	while (true) {
		printShapka(14);
		vibor = inputInt(8,2);
		switch (vibor) {
		case 0: return;
		case 1: {
			if (buyTicket(flightList)) {
				zapisTickets(flightList);
			}
			break;
		}
		case 2: {
			printShapka(4);
			poiskTicket(flightList);
			break;
		}
		case 3: {
			printShapka(3);
			sortTicket(flightList);
			break;
		}
		case 4: {
			printTicketInfo(flightList);
			break;
		}
		default: {
			printErrorMessage(27);
		}
		}
	}
}


//основная функция режима редактирования в "Работа с данными"
void editMode() {
	int vibor;
	std::vector<Flight> ticketList = getTickets();
	while (true) {
		printShapka(13);
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
			if (editZapis(ticketList)) printMessage(3);
			break;
		}
		case 4: {
			printShapka(8);
			if (deleteZapis(ticketList)) printMessage(1);
			break;
		}
		default: {
			printErrorMessage(27);
		}
		}
	}
}


//функция выбора режима
void chooseMode() {
	int vibor;
	while (true) {
		printShapka(16);
		vibor = inputInt(10,2);
		switch (vibor) {
		case 0: return;
		case 1: {
			editMode();
			break;
		}
		case 2: {
			processMode();
			break;
		}
		default: {
			printErrorMessage(27);
		}
		}
	}
}


//реализую метод startAdminMenu
bool Administrator::startAdminMenu(std::vector<Account>&vectorAccounts, int accountIndex) {
	int vibor;
	while (true) {
		printShapka(1);
		vibor = inputInt(11, 2);
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
		default: {
			printErrorMessage(27);
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