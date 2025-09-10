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



//функция получения индекса рейса в векторе по его номеру(рейса)
int getRaceIndex(std::vector<Ticket>& ticketList, int ticketRace) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].isSimilarRace(ticketRace)){
			return i;
		}
	}
	return -1;
}


//метод получения информации о билете (полиморфизм)
void printTicketInfo(std::vector<Ticket>& ticketList) {
	int ticketRace = inputInt(9, 1);
	int ticketIndex = getRaceIndex(ticketList,ticketRace);
	if (ticketIndex != -1) {
		Ticket ticket = ticketList[ticketIndex];
		printSomeInfo(ticket);//шаблон, полиморфизм
	}
	else {
		printErrorMessage(2);
	}
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
		if (ticketList[i].isSimilarRace(ticketRaceNumber)) {
			printErrorMessage(1);
			return 0;
		}
	}
	return 1;
}

//функция проверки правильности поля
bool isTruePole(int viborEdit, std::vector<Ticket>& ticketList, Ticket& ticket) {
	if ((viborEdit==1 || viborEdit==7 || viborEdit == 8 || viborEdit == 10) && !ticket.isCorrectRaceOption(viborEdit)){
		if (viborEdit == 1 && getRaceIndex(ticketList, ticket.getIntSortParam(5)) != -1) {
			printErrorMessage(1);
			return 0;
		}
		return 1;

	}
	printErrorMessage(viborEdit + 9); return 0;
	return 0;
}


//функция ввода значений новой записи. Switch, потому что при вызове из editZapis нужно изменить только 1 поле, а не сразу все
bool inputZapis(Ticket& ticket, std::vector<Ticket>& ticketList, int viborEdit) {

	std::string new_data = "-";
	int new_data_int = -1;

	if (viborEdit == 1 || (viborEdit >= 7 && viborEdit <= 11)) {
		if (inputIntSsilka(viborEdit + 8, new_data_int, 1)) { ticket.setParam(new_data_int, viborEdit - 5); }
		else {
			printErrorMessage(viborEdit + 9); return 0;
		}
		if (!isTruePole(viborEdit, ticketList, ticket)) {
			return 0;
		}
		return 1;
	}


	if ((viborEdit >= 2 && viborEdit <= 6)) {
		if (inputStrSsilka(viborEdit + 8, new_data, 1)) {
			ticket.setParam(new_data, viborEdit - 1);
		}
		else { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 4 && !ticket.isTrueFormatDate()) { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 5 && !ticket.isTrueFormatVremya(1)) { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 6 && !ticket.isTrueFormatVremya(2)) { printErrorMessage(viborEdit + 9); return 0; }
		return 1;
	}

}


//функция вызова ввода новых данных в запись по ссылке
bool inputNewData(Ticket &ticket, std::vector<Ticket> ticketList) {
	for (int i = 1; i < 12; i++) {
		if (!inputZapis(ticket, ticketList, i)) {
			return 0;
		}
	}
	return 1;
}


//функция создания новой записи
bool addNewZapis(std::vector<Ticket>& ticketList) {
	Ticket ticket;
	bool isTrue = inputNewData(ticket, ticketList);
	if (isTrue) {
		ticketList.push_back(ticket);
		if (zapisTickets(ticketList)) {
			return 1;
		}
	}
	return false;
}


//функция редактирования
bool editZapis(std::vector<Ticket>& ticketList) {
	int ticketRace = inputInt(9, 1);
	int indexRaceInVector = getRaceIndex(ticketList, ticketRace);
	if (indexRaceInVector != -1) {
		int viborEdit = inputInt(13,2);
		if (viborEdit == -1 || viborEdit==0) {
			return 0;
		}
		Ticket ticket = ticketList[indexRaceInVector];
		if (!inputZapis(ticket, ticketList, viborEdit))return 0;
		if (ticket.isTrueFormatVremya(1) && ticket.isTrueFormatVremya(2) && ticket.isTrueFormatDate()) {
			//ticketList.push_back(ticket);
			ticketList[indexRaceInVector] = ticket;
			zapisTickets(ticketList);
		}
		else { printErrorMessage(-1); return 0; }
		return 1;
	}
	return 0;
}


//функция удаления записи
bool deleteZapis(std::vector<Ticket>& ticketList) {
	int ticketRace = inputInt(9, 1);
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



//функция ввода данных покупаемого билета
bool inputBuyTicket(int& raceNumber, int& kolvoTickets, int& classType) {
	raceNumber = inputInt(36,1);
	kolvoTickets = inputInt(37,1);
	classType = inputInt(38,1);
	return 1;
}

//функция проверки правильности введённых данных покупаемого билета
bool isValidBuyTicket(int& kolvoTickets, int& classType, int &indexRace) {
	if (indexRace == -1 || kolvoTickets == -1 || classType == -1) {
		printMessage(1);
		return 0;
	}
	return 1;
}

//функция вывода количества билетов
void printKolvoTickets(int classType, Ticket ticket) {
	std::cout << ticket.getKolvoTickets(classType);
}

//функция покупки билета
bool buyTicket(std::vector<Ticket>& ticketList) {
	printShapka(5);
	int raceNumber, kolvoTickets, classType;
	inputBuyTicket(raceNumber, kolvoTickets, classType);

	int indexRace = getRaceIndex(ticketList, raceNumber);

	Ticket ticket = ticketList[indexRace];

	if (classType == 1) {
		if (ticket.isValidTicketKolvo(kolvoTickets, 1) && ticket.buyTickets(kolvoTickets,1)) {
			printMessage(12);
			return 1;
		}
		else if (ticket.isValidTicketKolvo(kolvoTickets, 2)) {
			printErrorMessage(6);
			printKolvoTickets(2, ticket);
		}
	}

	else if (classType == 2) {
		if (ticket.isValidTicketKolvo(kolvoTickets, 2) && ticket.buyTickets(kolvoTickets, 2)) {
			printMessage(12);
			return 1;
		}
		else if (ticket.isValidTicketKolvo(kolvoTickets, 1)) {
			printErrorMessage(5);
			printKolvoTickets(1, ticket);
		}
	}
	else { printMessage(1); }
	return -1;
}


//функция поиска по типу самолёта
void poiskSamoletType(std::vector<Ticket>& ticketList, std::string samoletType) {
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].isSimilarSamoletType(samoletType)){
			printTickets(ticketList, i, i+1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printErrorMessage(2); }
}


//функция поиска по пункту назначения
void poiskPunktNaznach(std::vector<Ticket>& ticketList, std::string punktNaznach){
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].isSimilaPunktNaznach(punktNaznach)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printErrorMessage(2); }
}


//функция поиска по цене билета
void poiskTicketPrice(std::vector<Ticket>& ticketList,int classType, int sravnenie, int summa) {
	printShapkaProsmotr();
	int kolvoPoisk = 0;
	for (int i = 0; i < ticketList.size(); i++) {
		Ticket t = ticketList[i];
		if (t.sravnenieCen(1,summa,1)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (t.sravnenieCen(2, summa, 1)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (t.sravnenieCen(1, summa, 2)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (t.sravnenieCen(2, summa, 2)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (t.sravnenieCen(3,summa,1)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
		else if (t.sravnenieCen(3, summa, 2)) {
			printTickets(ticketList, i, i + 1);
			kolvoPoisk++;
		}
	}
	if (kolvoPoisk == 0) { printErrorMessage(2); }
}


//функция выбора типа поиска
void poiskTicket(std::vector<Ticket>& ticketList) {
	int viborPoisk = inputInt(2,2);
	switch (viborPoisk) {
	case 0: return;
	case 1: {
		poiskSamoletType(ticketList,inputStr(35,1));
		break;
	}
	case 2: {
		poiskPunktNaznach(ticketList, inputStr(27,1));
		break;
	}
	case 3: {
		int classType = inputInt(3,2);
		if (classType == -1) { return; }
		int sravnenie = inputInt(4,2);
		if (sravnenie == -1) { return; }
		int summa = inputInt(39,1);
		if (summa == -1) { return; }
		poiskTicketPrice(ticketList, classType, sravnenie, summa);
		break;
	}
	}
}


//компаратор для сортировки по стоимости бизнес класса
bool compareSortBiznesPrice(Ticket& a, Ticket& b) {
	return a.getIntSortParam(1) < b.getIntSortParam(1);
}
//сортировка по стоимости бизнес класса
void sortBiznesPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortBiznesPrice);
}



//компаратор для сортировки по стоимости эконом класса
bool compareSortEkonomPrice(Ticket& a, Ticket& b) {
	return a.getIntSortParam(2) < b.getIntSortParam(2);
}
//сортировка по стоимости эконом класса класса
void sortEkonomPrice(std::vector<Ticket> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortEkonomPrice);
}



//компаратор для сортировки по колву бизнес
bool compareSortKolvoBiznes(Ticket& a, Ticket& b) {
	return a.getIntSortParam(3) < b.getIntSortParam(3);
}
//сортировка по колву бизнес
void sortKolvoBiznes(std::vector<Ticket>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoBiznes);
}


//компаратор для сортировки по колву эконом
bool compareSortKolvoEkonom(Ticket& a,Ticket& b) {
	return a.getIntSortParam(4) < b.getIntSortParam(4);
}
//сортировка по колву эконом
void sortKolvoEkonom(std::vector<Ticket>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoEkonom);
}


//функция выбора сортировки
void sortTicket(std::vector<Ticket> ticketList) {
	int viborSort = inputInt(5,2);
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
