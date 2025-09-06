#include "Individual.h"
//все вводы сделать через inputInt и inputStr


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
			" | " << t.dateVilet <<
			" | " << t.vremyaVilet <<
			" | " << t.vremyaPrilet <<
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
	std::cout << "Введите номер рейса\n";
	std::cin >> ticketRace;
	std::cout << std::endl;
	return ticketRace;
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

//функция вывода ошибок
void printMessage(int messageCode) {
	std::string message = "Ошибка";
	switch (messageCode) {
	case 1: { message = "Ошибка ввода\n\n"; break; }
	case 2: { message = "Ошибка вывода\n\n"; break; }
	case 3: { message = "Слишком много!\n\n"; break; }
	case 4: { message = "Такой рейс уже есть\n"; break; }
	case 5: { message = "Успешно удалил\n\n"; break; }
	case 6: { message = "Успешно добавил\n\n"; break; }
	case 7: { message = "Успешно изменил\n\n"; break; }
	case 8: { message = "Введите, что будете искать\n"; break; }
	case 9: { message = "Ничего не найдено\n\n\n"; break; }
	}
	std::cout << message;
}


//функция ввода типа и количеста билетов
int getTicketKolvoType(std::vector<Ticket>& ticketList,int &indexRace, int &kolvoTicket, int &classType,int &maxTicket) {

	std::cout << "Введите класс билета:\n1.Бизнес\n2.Эконом\n";
	std::cin >> classType;
	std::cout << "Введите количество билетов(максимум ";
	if (classType == 1) {
		maxTicket = ticketList[indexRace].kolvoTicketBiznes;
	}
	else if (classType == 2) {
		maxTicket = ticketList[indexRace].kolvoTicketEkonom;
	}
	std::cout << maxTicket << ")\n";
	std::cin >> kolvoTicket;
	return 1;
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

//функция ввода числовых значений Ticket (чтобы избежать ошибок если ввели букву)
bool inputInt(int &ticketField,std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> prompt;
	try {
		ticketField= std::stoi(prompt);
	}
	catch (...) {
		printMessage(1);
		return 0;
	}
}

//функция ввода строкового поля Ticket
void inputTicketStr(std::string& ticketField, std::string prompt) {
	std::cout << prompt << std::endl;
	std::cin >> ticketField;
}

//функция ввода значений новой записи. Switch, потому что при вызове из editZapis нужно изменить только 1 поле, а не сразу все
bool inputZapis(Ticket &ticket, std::vector<Ticket>& ticketList, int viborEdit) {
	std::string string_input;
	int int_input;
	bool isRunInputZapis = true;
	switch (viborEdit) {
	case 1: {
		if (!inputInt(ticket.raceNumber, "Введите номер рейса")) {
			return 0;
		}
		else if (!checkRace(ticket.raceNumber, ticketList)) {
			return 0;
		}
		break;
	}
	case 2:  {inputTicketStr(ticket.samoletType, "Введите тип самолёта"); break;}
	case 3:  {inputTicketStr(ticket.punktNaznacheniya, "Введите пункт назначения (латиницей)"); break;}
	case 4:  {inputTicketStr(ticket.dateVilet, "Введите день вылета"); break;}
	case 5:  {inputTicketStr(ticket.vremyaVilet, "Введите время вылета"); break;}
	case 6:  {inputTicketStr(ticket.vremyaPrilet, "Введите время прилёта"); break;}
	case 7:  {if (!inputInt(ticket.vmestimost, "Введите вместимость самолёта")) { return 0; } break;}
	case 8:  {if (!inputInt(ticket.kolvoTicketBiznes, "Введите количество билетов бизнес класса")) { return 0; } break;}
	case 9:  {if (!inputInt(ticket.stoimostBiznes, "Введите стоимость билета бизнес класса")) { return 0; } break;}
	case 10: {if (!inputInt(ticket.kolvoTicketEkonom, "Введите количество билетов эконом класса")) { return 0; } break;}
	case 11: {if (!inputInt(ticket.stoimostEkonom, "Введите стоимость билета эконом класса")) { return 0; } break;}}

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
	ticketList.push_back(ticket);
	zapisTickets(ticketList);
	return 1;
}


//функция редактирования
bool editZapis(std::vector<Ticket>& ticketList) {
	int ticketRace = getTicketRace();
	int viborEdit = -1;
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
		std::cin >> viborEdit;
		if (viborEdit == 0) {
			return 1;
		}
		Ticket ticket=ticketList[indexRaceInVector]; 
			inputZapis(ticket, ticketList, viborEdit);
			ticketList[indexRaceInVector] = ticket;
			zapisTickets(ticketList);
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
	int ticketRace = getTicketRace();
	int indexRace = getRaceIndex(ticketList, ticketRace);
	int kolvoTicket = 0, classType_int, maxTicket = 0;
	std::string classType_str;
	if (indexRace == -1) {
		printMessage(-1);
		return -1;
	}
	getTicketKolvoType(ticketList, indexRace, kolvoTicket, classType_int, maxTicket);

	if (kolvoTicket <= maxTicket) {
		if (classType_int) {
			ticketList[indexRace].kolvoTicketBiznes -= kolvoTicket;
			return 1;
		}
		else {
			ticketList[indexRace].kolvoTicketEkonom -= kolvoTicket;
			return 1;
		}
	}
	else {
		printMessage(3);
	}

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


std::string inputPoiskStr() {
	std::string stroka;
	std::cout << "Введите, что будете искать\n";
	std::cin >> stroka;
	return stroka;
}


//функция выбора типа поиска
void poiskTicket(std::vector<Ticket>& ticketList) {
	int viborPoisk = 0;
	std::cout << "Введите, по какому полю будете искать:\n" <<
		"1. Тип самолёта\n" <<
		"2. Пункт назначения\n" <<
		"3. Стоимость билета\n" <<
		"0. Назад\n";
	std::cin >> viborPoisk;
	switch (viborPoisk) {
	case 0: return;
	case 1: {
		poiskSamoletType(ticketList,inputPoiskStr());
		break;
	}
	case 2: {
		poiskPunktNaznach(ticketList, inputPoiskStr());
		break;
	}
	case 3: {
		int classType, sravnenie, summa;

		std::cout << "Введите, в каком классе искать\n1.Бизнес\n 2.Эконом\n3.Во всех\n0.Назад\n";
		std::cin >> classType;
		if (classType == 0) { return; }
		std::cout << "Введите, больше или меньше какой-то цены\n1.Больше\n2.Меньше\n0.Назад\n";
		std::cin >> sravnenie;
		if (sravnenie == 0) { return; }
		std::cout << "Укажите цену\n";
		std::cin >> summa;
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



//компаратор для сортировки по вместительности
bool compareSortVmestitelnost(const Ticket& a, const Ticket& b) {
	return a.vmestimost < b.vmestimost;
}
//сортировка по вместительности
void sortVmestitelnost(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortVmestitelnost);
}

//функция выбора сортировки
void sortTicket(std::vector<Ticket> ticketList) {
	int viborSort = 0;
	std::cout << "Выберите, по чём сортировать:\n1.Цене билетов бизнес класса\n2.Цене билетов эконом класса\n3.Вместимости\n0.Назад\n";
	std::cin >> viborSort;
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
		sortVmestitelnost(ticketList); break;
	}
	}
	printTickets(ticketList, 0, -1);
}




