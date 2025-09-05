
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
	std::cout << "Что хотите сделать с аккаунтом?\n1. Изменить пароль\n2. Изменить логин\n3. Изменить роль\n4. Изменить соль\n";
	std::cin >> vibor;
	std::string new_data;
	std::cout << "Введите новые данные:\n";
	switch (vibor) {
	case -1:break;
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





//запуск меню администратора
void startAdministrator(std::vector<Account> &vectorAccounts, int accountIndex) {
	int vibor;
	bool isRunAdm = true;
	while (isRunAdm) {
		std::cout << "Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n";
		std::cin >> vibor;
		switch (vibor) {
		case 1:
		{
			rabotaWithAccounts(vectorAccounts, accountIndex);
			break;
		}
		case 2: {
			editMode();
			break;
		}
			
		}
	}
}