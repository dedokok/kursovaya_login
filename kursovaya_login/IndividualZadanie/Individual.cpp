#include "Individual.h"


//функци вывода шапки
void printShapkaProsmotr() {
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |       Тип       |       Куда      |    День    | Время | Время | Вмес| Кол | Ст.  | Кол.| Ст. |\n");
	printf("|  №  |    самолёта     |       летит     |   вылета   | вылета|прибыт.| тим.| биз | Биз. | эк. | эк. |\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
}


//функция вывода билетов
void printTickets(std::vector<Ticket> &ticketList, int startI, int kolvoPrint) {
	if (kolvoPrint == -1) { kolvoPrint = ticketList.size(); }
	for (int i = startI; kolvoPrint-i>0; i++) {
		Ticket t = ticketList[i];
		t.printTicket();
	}
}


//Функция проверки формата времени
bool isTrueFormatVremya(std::string vremya) {
	std::tm tm = {};
	std::stringstream ss(vremya);
	ss >> std::get_time(&tm, "%H:%M");
	if (ss.fail()) {
		std::cout << "Неверный формат времени" << std::endl;
		return 0;
	}
	else {
		return 1;
	}
}


//функция проверки формата даты
bool isTrueFormatDate(std::string date) {
	std::tm tm = {};
	std::stringstream ss(date);
	ss >> std::get_time(&tm, "%d.%m.%Y");
	if (ss.fail()) {
		std::cout << "Неверный формат даты" << std::endl;
		return 0;
	}
	else {
		return 1;
	}
}


//функция ввода номера рейса для покупки билета
int getTicketRace() {
	return inputInt("Введите номер рейса\n");
}


//функция получения индекса рейса в векторе по его номеру(рейса)
int getRaceIndex(std::vector<Ticket>& ticketList, int ticketRace) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].getIntParam(1) == ticketRace) {
			return i;
		}
	}
	return -1;
}


//функция записи аккаунта в файл
bool zapisTickets(std::vector<Ticket>& ticketList) {
	nlohmann::json j{};
	j["ticketList"] = ticketList;
	std::ofstream out;
	out.open("ticketList.json");
	if (out.is_open())
	{
		out << j.dump(4) << std::endl;
	}
	out.close();
	return true;
}


//функция записи джсона в вектор
std::vector<Ticket> getTickets() {
	std::ifstream in;
	in.open("ticketList.json");
	std::vector<Ticket> ticketList;
	try {
		auto j = nlohmann::json::parse(in);
		ticketList = j["ticketList"];
		in.close();
		return ticketList;
	}
	catch (...) {
		in.close();
		return ticketList;
	}
	return ticketList;
}


//функция проверки, если ли уже такой рейс
bool checkRace(int ticketRaceNumber, std::vector<Ticket>& ticketList) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].getIntParam(1) == ticketRaceNumber) {
			printMessage(4);
			return 0;
		}
	}
	return 1;
}


//функция проверки длины значений
bool checkDlina(Ticket &ticket) {
	if (ticket.isValidTicket()) {
		return 1;
	}
	else {
		ticket.setParam(-1,1);
		return 0;
	}
	return 0;
}

//функция ввода значений новой записи. Switch, потому что при вызове из editZapis нужно изменить только 1 поле, а не сразу все
bool inputZapis(Ticket& ticket, std::vector<Ticket>& ticketList, int viborEdit) {
	std::string new_data = "-";
	switch (viborEdit) {
	case 1: {
		
		if (!inputIntSsilka(1, "Введите номер рейса",ticket)) {
			return 0;
		}
		else if (!checkRace(ticket.getIntParam(1), ticketList)) {
			return 0;
		}
		break;
	}
	case 2: {
		inputStrSsilka(1, "Введите тип самолёта",ticket);
		if (ticket.getStrParam(1).length() > 15) {
			printMessage(1);
			ticket.setParam(-1,1);
			return 0;
		}
		break;
	}
	case 3: { inputStrSsilka(2,"Введите пункт назначения (латиницей)",ticket); break; }
	case 4: { inputStrSsilka(3,"Введите день вылета", ticket); break; }
	case 5: { inputStrSsilka(4,"Введите время вылета", ticket); break; }
	case 6: { inputStrSsilka(5,"Введите время прилёта", ticket); break; }
	case 7: { if (!inputIntSsilka(2, "Введите вместимость самолёта",ticket)) { return 0; } break; }
	case 8: { if (!inputIntSsilka(3, "Введите количество билетов бизнес класса", ticket)) { return 0; } break; }
	case 9: { if (!inputIntSsilka(4, "Введите стоимость билета бизнес класса", ticket)) { return 0; } break; }
	case 10: { if (!inputIntSsilka(5, "Введите количество билетов эконом класса", ticket)) { return 0; } break; }
	case 11: { if (!inputIntSsilka(6,"Введите стоимость билета эконом класса", ticket)) { return 0; } break; }
	}
	return 1;
}


//функция добавления новой записи
bool addZapis(std::vector<Ticket> &ticketList) {
	printShapka(9);
	Ticket ticket;
	for (int i = 1; i < 12; i++) {
		if (!inputZapis(ticket, ticketList,i)) {
			return 0;
		}
	}
	if (checkDlina(ticket)&& isTrueFormatVremya(ticket.getStrParam(4))
		&& isTrueFormatVremya(ticket.getStrParam(5))&&isTrueFormatDate(ticket.getStrParam(3))) {
		ticketList.push_back(ticket);
		zapisTickets(ticketList);
	}
	else { printMessage(1); return 0; }
	return 1;
}


//функция редактирования
bool editZapis(std::vector<Ticket>& ticketList) {
	int ticketRace = getTicketRace();
	int indexRaceInVector = getRaceIndex(ticketList, ticketRace);
	if (indexRaceInVector != -1) {
		std::cout << "Выберите, что изменить:\n" <<
			"1.Номер рейса\n" <<
			"2.Тип самолёта\n" <<
			"3.Пункт назначения\n" <<
			"4.Дата вылета\n" <<
			"5.Время вылета\n" <<
			"6.Время прилёта\n" <<
			"7.Вместимость самолёта\n" <<
			"8.Количество билетов бизнес класса\n" <<
			"9.Стоимость билета бизнес класса\n" <<
			"11.Количество билетов эконом класса\n" <<
			"12.Стоимость билета эконом класса\n" <<
			"0.Назад\n";
		int viborEdit = inputInt("");
		if (viborEdit == -1 || viborEdit==0) {
			return 0;
		}
		Ticket ticket = ticketList[indexRaceInVector];
		inputZapis(ticket, ticketList, viborEdit);
		if (checkDlina(ticket) && isTrueFormatVremya(ticket.getStrParam(4))
			&& isTrueFormatVremya(ticket.getStrParam(5)) && isTrueFormatDate(ticket.getStrParam(3))) {
			ticketList.push_back(ticket);
			zapisTickets(ticketList);
		}
		else { printMessage(1); return 0; }
		return 1;
	}
	return 0;
}


//функция удаления записи
bool deleteZapis(std::vector<Ticket>& ticketList) {
	int ticketRace = getTicketRace();
	int indexRaceInVector = getRaceIndex(ticketList, ticketRace);
	auto begin = ticketList.cbegin();
	try {
		if (getAccept()) {
			ticketList.erase(begin + indexRaceInVector);
			return 1;
		}
	}
	catch (...) { return 0; }
	return 0;
}


////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных


//функция покупки билета
int buyTicket(std::vector<Ticket>& ticketList) {
	printShapka(5);
	int ticketRace = inputInt("Введите номер рейса");
	int indexRace = getRaceIndex(ticketList, ticketRace);
	if (indexRace == -1) {
		printMessage(1);
		return -1;
	}
	int kolvoTicket = inputInt("Введите количество билетов\n");
	if (kolvoTicket == -1) {
		printMessage(1);
		return -1;
	}
	int classType = inputInt("Введите класс билета : \n1.Бизнес\n2.Эконом\n");
	if (classType == -1) {
		printMessage(1);
		return -1;
	}
	
	if (classType == 1) {
		if (ticketList[indexRace].getIntParam(3) >= kolvoTicket) {
			ticketList[indexRace].setParam(ticketList[indexRace].getIntParam(3)-kolvoTicket,3);
			std::cout << "\nУспешная покупка!\n";
		}
		else if (ticketList[indexRace].getIntParam(5) >= kolvoTicket) {
			std::cout << "\nНа этот рейс нет нужного количества билетов бизнес класса" <<
				"но есть билеты эконом класса в количестве " <<
				ticketList[indexRace].getIntParam(5) << std::endl;
		}
		else {
			std::cout << "\nНа этот рейс нет нужного количеста билетов!\n";
		}
		return 1;
	}
	else if (classType == 2) {
		if (ticketList[indexRace].getIntParam(5) >= kolvoTicket) {
			ticketList[indexRace].setParam(ticketList[indexRace].getIntParam(5)-kolvoTicket,5);
		}
		else if (ticketList[indexRace].getIntParam(3) >= kolvoTicket) {
			std::cout << "\nНа этот рейс нет нужного количества билетов эконом класса" <<
				"но есть билеты бизнес класса в количестве " <<
				ticketList[indexRace].getIntParam(3) << std::endl;
		}
		else {
			std::cout << "\nНа этот рейс нет нужного количеста билетов\n";
		}
		return 1;
	}
	else { printMessage(1); }
	return -1;
}


//функция поиска по типу самолёта
void poiskSamoletType(std::vector<Ticket>& ticketList, std::string samoletType) {
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].getStrParam(1).find(samoletType) != -1) {
			printTickets(ticketList, i, i+1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printMessage(9); }
}


//функция поиска по пункту назначения
void poiskPunktNaznach(std::vector<Ticket>& ticketList, std::string punktNaznach){
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].getStrParam(2).find(punktNaznach) != -1) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printMessage(9); }
}


//функция поиска по цене билета
void poiskTicketPrice(std::vector<Ticket>& ticketList,int classType, int sravnenie, int summa) {
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (classType == 1 && sravnenie == 1 && ticketList[i].getIntParam(4) > summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (classType == 1 && sravnenie == 2 && ticketList[i].getIntParam(4) < summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (classType == 2 && sravnenie == 1 && ticketList[i].getIntParam(6) > summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (classType == 2 && sravnenie == 2 && ticketList[i].getIntParam(6) < summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (classType == 3 && sravnenie == 1 && (ticketList[i].getIntParam(4) > summa || ticketList[i].getIntParam(6) > summa)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (classType == 3 && sravnenie == 2 && (ticketList[i].getIntParam(4) < summa || ticketList[i].getIntParam(6) < summa)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printMessage(9); }
}


//функция выбора типа поиска
void poiskTicket(std::vector<Ticket>& ticketList) {
	std::cout << "Введите, по какому полю будете искать:\n" <<
		"1. Тип самолёта\n" <<
		"2. Пункт назначения\n" <<
		"3. Стоимость билета\n" <<
		"0. Назад\n";
	int viborPoisk = inputInt("");
	switch (viborPoisk) {
	case 0: return;
	case 1: {
		poiskSamoletType(ticketList,inputStr("Введите пункт назначения"));
		break;
	}
	case 2: {
		poiskPunktNaznach(ticketList, inputStr("Введите пункт назначения"));
		break;
	}
	case 3: {
		int classType = inputInt("Введите, в каком классе искать\n1.Бизнес\n 2.Эконом\n3.Во всех\n0.Назад");
		if (classType == -1) { return; }
		int sravnenie = inputInt("Введите, больше или меньше какой-то цены\n1.Больше\n2.Меньше\n0.Назад\n");
		if (sravnenie == -1) { return; }
		int summa = inputInt("Укажите цену");
		if (summa == -1) { return; }
		poiskTicketPrice(ticketList, classType, sravnenie, summa);
		break;
	}
	}
}


//компаратор для сортировки по стоимости бизнес класса
bool compareSortBiznesPrice(Ticket& a, Ticket& b) {
	return a.getIntParam(4) < b.getIntParam(4);
}
//сортировка по стоимости бизнес класса
void sortBiznesPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortBiznesPrice);
}



//компаратор для сортировки по стоимости эконом класса
bool compareSortEkonomPrice(Ticket& a, Ticket& b) {
	return a.getIntParam(6) < b.getIntParam(6);
}
//сортировка по стоимости эконом класса класса
void sortEkonomPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortEkonomPrice);
}



//компаратор для сортировки по колву бизнес
bool compareSortKolvoBiznes(Ticket& a, Ticket& b) {
	return a.getIntParam(3) < b.getIntParam(3);
}
//сортировка по колву бизнес
void sortKolvoBiznes(std::vector<Ticket>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoBiznes);
}


//компаратор для сортировки по колву эконом
bool compareSortKolvoEkonom(Ticket& a,Ticket& b) {
	return a.getIntParam(5) < b.getIntParam(5);
}
//сортировка по колву эконом
void sortKolvoEkonom(std::vector<Ticket>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoEkonom);
}


//функция выбора сортировки
void sortTicket(std::vector<Ticket> ticketList) {
	std::cout << "Выберите, по чём сортировать:\n"<<
		"1.Цене билетов бизнес класса\n"<<
		"2.Цене билетов эконом класса\n"<<
		"3.Количеству билетов бизнес класса\n"<<
		"4.Количеству билетов эконом класса\n"<<
		"0.Назад\n";
	int viborSort = inputInt("");
	if (viborSort == 0) { return; }
	printShapkaProsmotr();
	switch (viborSort) {
	
	case 1: {
		sortBiznesPrice(ticketList); break;
	}
	case 2: {
		sortEkonomPrice(ticketList); break;
	}
	case 3: {
		sortKolvoBiznes(ticketList); break;
	}
	case 4: {
		sortKolvoEkonom(ticketList); break;
	}
	}
	printTickets(ticketList, 0, -1);
}