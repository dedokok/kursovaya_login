#include "Individual.h"


//функци вывода шапки
void printShapka() {
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |       Тип       |       Куда      |    День    | Время | Время | Вмес| Кол | Ст.  | Кол.| Ст. |\n");
	printf("|  №  |    самолёта     |       летит     |   вылета   | вылета|прибыт.| тим.| биз | Биз. | эк. | эк. |\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
}


void printTickets(std::vector<Ticket> &ticketList, int startI, int kolvoPrint) {
	if (kolvoPrint == -1) { kolvoPrint = ticketList.size(); }
	for (int i = startI; kolvoPrint-i>0; i++) {
		Ticket t = ticketList[i];
		std::cout <<
			"| "  << std::setw(3) << t.raceNumber <<
			" | " << std::left << std::setw(15) << t.samoletType <<
			" | " << std::left << std::setw(15) << t.punktNaznacheniya <<
			" | " << std::setw(10) << t.dateVilet <<
			" | " << std::setw(5) << t.vremyaVilet <<
			" | " << std::setw(5) << t.vremyaPrilet <<
			" | " << std::setw(3) << t.vmestimost <<
			" | " << std::setw(3) << t.kolvoTicketBiznes <<
			" | " << std::setw(4) << t.stoimostBiznes <<
			" | " << std::setw(3) << t.kolvoTicketEkonom <<
			" | " << std::setw(4) << t.stoimostEkonom <<
			"|"  << std::endl;
		printf("-------------------------------------------------------------------------------------------------------\n");
	}
}


//функция ввода номера рейса для покупки билета
int getTicketRace() {
	int ticketRace;
	return inputInt("Введите номер рейса\n");
}


//функция получения индекса рейса в векторе по его номеру(рейса)
int getRaceIndex(std::vector<Ticket>& ticketList, int ticketRace) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].raceNumber == ticketRace) {
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
	//std::string login, password, sault;
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
		if (ticketList[i].raceNumber == ticketRaceNumber) {
			printMessage(4);
			return 0;
		}
	}
	return 1;
}


//функция проверки длины значений
bool checkDlina(Ticket &ticket) {
	if (ticket.raceNumber < 1000 && ticket.raceNumber>0 && ticket.samoletType.length() < 16 && ticket.samoletType.length() > 0
		&& ticket.dateVilet.length() > 0 && ticket.dateVilet.length() < 11
		&& ticket.vremyaPrilet.length() > 0 && ticket.vremyaPrilet.length() < 6
		&& ticket.vremyaVilet.length() > 0 && ticket.vremyaVilet.length() < 6
		&& ticket.vmestimost > -1 && ticket.vmestimost<1000
		&& ticket.kolvoTicketBiznes>-1 && ticket.kolvoTicketBiznes<1000
		&& ticket.kolvoTicketEkonom>-1 && ticket.kolvoTicketEkonom<1000
		&& ticket.stoimostBiznes>-1 && ticket.stoimostBiznes<10000
		&& ticket.stoimostEkonom>-1 && ticket.stoimostEkonom < 10000) {
		return 1;
	}
	else {
		ticket.raceNumber = -1;
		return 0;
	}
	return 0;
}

//функция ввода значений новой записи. Switch, потому что при вызове из editZapis нужно изменить только 1 поле, а не сразу все
bool inputZapis(Ticket& ticket, std::vector<Ticket>& ticketList, int viborEdit) {
	switch (viborEdit) {
	case 1: {
		if (!inputIntSsilka(ticket.raceNumber, "Введите номер рейса")) {
			return 0;
		}
		else if (!checkRace(ticket.raceNumber, ticketList)) {
			return 0;
		}
		break;
	}
	case 2: {
		inputStrSsilka(ticket.samoletType, "Введите тип самолёта");
		if (ticket.samoletType.length() > 15) {
			printMessage(1);
			ticket.raceNumber == -1;
			return 0;
		}
		break;
	}
	case 3: { inputStrSsilka(ticket.punktNaznacheniya, "Введите пункт назначения (латиницей)"); break; }
	case 4: { inputStrSsilka(ticket.dateVilet, "Введите день вылета"); break; }
	case 5: { inputStrSsilka(ticket.vremyaVilet, "Введите время вылета"); break; }
	case 6: { inputStrSsilka(ticket.vremyaPrilet, "Введите время прилёта"); break; }
	case 7: { if (!inputIntSsilka(ticket.vmestimost, "Введите вместимость самолёта")) { return 0; } break; }
	case 8: { if (!inputIntSsilka(ticket.kolvoTicketBiznes, "Введите количество билетов бизнес класса")) { return 0; } break; }
	case 9: { if (!inputIntSsilka(ticket.stoimostBiznes, "Введите стоимость билета бизнес класса")) { return 0; } break; }
	case 10: { if (!inputIntSsilka(ticket.kolvoTicketEkonom, "Введите количество билетов эконом класса")) { return 0; } break; }
	case 11: { if (!inputIntSsilka(ticket.stoimostEkonom, "Введите стоимость билета эконом класса")) { return 0; } break; }
	}
	return 1;
}


//функция добавления новой записи
bool addZapis(std::vector<Ticket> &ticketList) {
	Ticket ticket;
	for (int i = 1; i < 12; i++) {
		if (!inputZapis(ticket, ticketList,i)) {
			return 0;
		}
	}
	if (checkDlina(ticket)) {
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
			"1. Номер рейса\n" <<
			"2. Тип самолёта\n" <<
			"3. Пункт назначения\n" <<
			"4. Дата вылета\n" <<
			"5. Время вылета\n" <<
			"6. Время прилёта\n" <<
			"7. Вместимость самолёта\n" <<
			"8. Количество билетов бизнес класса\n" <<
			"9. Стоимость билета бизнес класса\n" <<
			"11. Количество билетов эконом класса\n" <<
			"12. Стоимость билета эконом класса\n" <<
			"0. Назад\n";
		int viborEdit = inputInt("");
		if (viborEdit == -1 || viborEdit==0) {
			return 0;
		}
		Ticket ticket = ticketList[indexRaceInVector];
		inputZapis(ticket, ticketList, viborEdit);
		if (checkDlina(ticket)) {
			ticketList[indexRaceInVector] = ticket;
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
		ticketList.erase(begin + indexRaceInVector);
		return 1;
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
	int ticketRace = inputInt("Введите номер рейса");
	int indexRace = getRaceIndex(ticketList, ticketRace);
	int kolvoTicket = inputInt("Введите количество билетов\n");
	int classType = inputInt("Введите класс билета : \n1.Бизнес\n2.Эконом\n");
	if (indexRace == -1) {
		printMessage(-1);
		return -1;
	}
	if (classType == 1) {
		if (ticketList[indexRace].kolvoTicketBiznes >= kolvoTicket) {
			ticketList[indexRace].kolvoTicketBiznes -= kolvoTicket;
			std::cout << "\nУспешная покупка!\n";
		}
		else if (ticketList[indexRace].kolvoTicketEkonom >= kolvoTicket) {
			std::cout << "\nНа этот рейс нет нужного количества билетов бизнес класса" <<
				"но есть билеты эконом класса в количестве " <<
				ticketList[indexRace].kolvoTicketEkonom << std::endl;
		}
		else {
			std::cout << "\nНа этот рейс нет нужного количеста билетов!\n";
		}
		return 1;
	}
	else if (classType == 2) {
		if (ticketList[indexRace].kolvoTicketEkonom >= kolvoTicket) {
			ticketList[indexRace].kolvoTicketEkonom -= kolvoTicket;
		}
		else if (ticketList[indexRace].kolvoTicketBiznes >= kolvoTicket) {
			std::cout << "\nНа этот рейс нет нужного количества билетов эконом класса" <<
				"но есть билеты бизнес класса в количестве " <<
				ticketList[indexRace].kolvoTicketBiznes << std::endl;
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
	printShapka();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].samoletType.find(samoletType) != -1) {
			printTickets(ticketList, i, i+1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printMessage(9); }
}


//функция поиска по пункту назначения
void poiskPunktNaznach(std::vector<Ticket>& ticketList, std::string punktNaznach){
	printShapka();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].punktNaznacheniya.find(punktNaznach) != -1) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printMessage(9); }
}


//функция поиска по цене билета
void poiskTicketPrice(std::vector<Ticket>& ticketList,int classType, int sravnenie, int summa) {
	printShapka();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (classType == 1 && sravnenie == 1 && ticketList[i].stoimostBiznes > summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		if (classType == 1 && sravnenie == 2 && ticketList[i].stoimostBiznes < summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		if (classType == 2 && sravnenie == 1 && ticketList[i].stoimostEkonom > summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		if (classType == 2 && sravnenie == 2 && ticketList[i].stoimostEkonom < summa) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		if (classType == 3 && sravnenie == 1 && (ticketList[i].stoimostBiznes > summa || ticketList[i].stoimostEkonom > summa)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		if (classType == 3 && sravnenie == 2 && (ticketList[i].stoimostBiznes < summa || ticketList[i].stoimostEkonom < summa)) {
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
bool compareSortBiznesPrice(const Ticket& a, const Ticket& b) {
	return a.stoimostBiznes < b.stoimostBiznes;
}
//сортировка по стоимости бизнес класса
void sortBiznesPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortBiznesPrice);
}



//компаратор для сортировки по стоимости эконом класса
bool compareSortEkonomPrice(const Ticket& a, const Ticket& b) {
	return a.stoimostEkonom < b.stoimostEkonom;
}
//сортировка по стоимости эконом класса класса
void sortEkonomPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortEkonomPrice);
}



//компаратор для сортировки по вместимости
bool compareSortVmestimost(const Ticket& a, const Ticket& b) {
	return a.vmestimost < b.vmestimost;
}
//сортировка по вместимости
void sortVmestimost(std::vector<Ticket>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortVmestimost);
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
	printShapka();
	switch (viborSort) {
	
	case 1: {
		sortBiznesPrice(ticketList); break;
	}
	case 2: {
		sortEkonomPrice(ticketList); break;
	}
	case 3: {
		sortVmestimost(ticketList); break;
	}
	}
	printTickets(ticketList, 0, -1);
}