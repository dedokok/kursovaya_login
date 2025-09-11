#include "Individual.h"


//функци вывода шапки
void printShapkaProsmotr() {
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |       Тип       |       Куда      |    День    | Время | Время | Вмес| Кол | Ст.  | Кол.| Ст. |\n");
	printf("|  №  |    самолёта     |       летит     |   вылета   | вылета|прибыт.| тим.| биз | Биз. | эк. | эк. |\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
}


//функция вывода билетов
void printTickets(std::vector<Flight> &ticketList, int startI, int kolvoPrint) {
	if (kolvoPrint == -1) { kolvoPrint = ticketList.size(); }
	for (int i = startI; kolvoPrint-i>0; i++) {
		ticketList[i].printFlight();
	}
}


//функция получения индекса рейса в векторе по его номеру(рейса)
int getRaceIndex(std::vector<Flight>& ticketList, int ticketRace) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].isSimilarRaceNumber(ticketRace)){
			return i;
		}
	}
	return -1;
}


//метод получения информации о билете (полиморфизм)
void printTicketInfo(std::vector<Flight>& ticketList) {
	int ticketRace = inputInt(9, 1);
	if (ticketRace == -1) { return; }
	int ticketIndex = getRaceIndex(ticketList,ticketRace);
	if (ticketIndex != -1) {
		Flight ticket = ticketList[ticketIndex];
		printSomeInfo(ticket);//шаблон, полиморфизм
	}
	else {
		printErrorMessage(2);
	}
}


//функция записи вектора рейсов в файл
bool zapisTickets(std::vector<Flight>& ticketList) {
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


//функция записи файла в вектор рейсов
std::vector<Flight> getTickets() {
	std::ifstream in;
	in.open("ticketList.json");
	std::vector<Flight> ticketList;
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


//функция проверки правильности поля
bool isTruePole(int viborEdit, std::vector<Flight>& ticketList, Flight& ticket) {
	if (ticket.isCorrectFlight(viborEdit)){//если введённое поле рейса правильное
		if (viborEdit == 1 && getRaceIndex(ticketList, ticket.getIntSortParam(5)) != -1) {//если такой номер рейса уже есть
			printErrorMessage(1);
			return 0;
		}
		return 1;
	}
	printErrorMessage(viborEdit + 9); return 0;
	return 0;
	
}


//функция ввода значений новой записи
bool inputZapis(Flight& ticket, std::vector<Flight>& ticketList, int viborEdit) {
	std::string new_data = "-";
	int new_data_int = -1;
	if (viborEdit == 1 || (viborEdit >= 7 && viborEdit <= 11)) {
		if (inputIntSsilka(viborEdit + 8, new_data_int, 1)) { ticket.setParam(new_data_int, viborEdit - 5); }
		else {
			printErrorMessage(viborEdit + 9); return 0;
		}
		if (isTruePole(viborEdit, ticketList, ticket)) {
			return 1;
		}
		return 0;
	}
	if ((viborEdit >= 2 && viborEdit <= 6)) {
		if (inputStrSsilka(viborEdit + 8, new_data, 1)) { ticket.setParam(new_data, viborEdit - 1); }
		else { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 4 && !ticket.isTrueFormatDate())    { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 5 && !ticket.isTrueFormatVremya(1)) { printErrorMessage(viborEdit + 9); return 0; }
		if (viborEdit == 6 && !ticket.isTrueFormatVremya(2)) { printErrorMessage(viborEdit + 9); return 0; }
		return 1;
	}
}


//функция вызова ввода новых данных в запись
bool inputNewData(Flight &ticket, std::vector<Flight> flightList) {
	for (int i = 1; i < 12; i++) {
		if (!inputZapis(ticket, flightList, i)) {
			return 0;
		}
	}
	return 1;
}


//функция создания новой записи
bool addNewZapis(std::vector<Flight>& flightList) {
	Flight flight;
	bool isTrue = inputNewData(flight, flightList);
	if (isTrue) {
		flightList.push_back(flight);
		if (zapisTickets(flightList)) {
			return 1;
		}
	}
	return false;
}


//функция редактирования рейсов
bool editZapis(std::vector<Flight>& flightList) {
	int ticketFlightNumber = inputInt(9, 1);
	int flightIndex = getRaceIndex(flightList, ticketFlightNumber);
	if (flightIndex != -1) {
		int viborEdit = inputInt(13, 2);
		Flight ticket = flightList[flightIndex];
		if (viborEdit==-1 || viborEdit==0 || !inputZapis(ticket, flightList, viborEdit))return 0;
		flightList[flightIndex] = ticket;
		zapisTickets(flightList);
		return 1;
	}
	else {
		printErrorMessage(10);
	}
	return 0;
}


//функция удаления записи
bool deleteZapis(std::vector<Flight>& flightList) {
	int ticketFlightNumber = inputInt(9, 1);
	int flightIndex = getRaceIndex(flightList, ticketFlightNumber);
	auto begin = flightList.cbegin();
	if (getAccept()) {
		try {
			flightList.erase(begin + flightIndex);
			zapisTickets(flightList);
			return 1;
		}
		catch (...) { return 0; }
	}
	return 0;
}


////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных
////Сверху был режим редактирования, теперь будет режим обработки данных



//функция ввода данных покупаемого билета
bool inputBuyTicket(int& flightRaceNumber, int& kolvoTickets, int& classType) {
	flightRaceNumber = inputInt(9,1);
	if (flightRaceNumber == -1) { printErrorMessage(10); return 0; }
	kolvoTickets = inputInt(21,1);
	if (kolvoTickets == -1) { printErrorMessage(22); return 0; }
	classType = inputInt(1,2);
	if (classType == -1) { printErrorMessage(23); return 0; }
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


//функция вывода количества билетов (ЕСЛИ НА ДАННЫЙ РЕЙС НЕТ БИЛЕТОВ)
void printKolvoTickets(int classType, Flight ticket) {
	std::cout << ticket.getKolvoTickets(classType) << std::endl;
}


//функция покупки билета
bool buyTicket(std::vector<Flight>& flightList) {
	printShapka(5);
	int flightRaceNumber, kolvoTickets, classType;
	inputBuyTicket(flightRaceNumber, kolvoTickets, classType); //ввожу значения в эти переменные
	if (flightRaceNumber == -1 || kolvoTickets == -1 || classType == -1) { return 0; }
	int flightIndex = getRaceIndex(flightList, flightRaceNumber);
	Flight ticket = flightList[flightIndex];
	if (classType == 1 || classType==2) {
		int antiClassType = classType == 1 ? 2 : 1; //определяю противоположный класс билета
		//у меня был выбор, либо выделить память для antiClassType, и тогда только 1 раз вычисляется
		//противоположный класс, либо 2 раза вычислять его. Я выбрал выделить память
		if (ticket.isValidTicketKolvo(kolvoTickets, classType) && ticket.buyTickets(kolvoTickets,classType)) {
			printMessage(12);
			return 1;
		}
		else if (ticket.isValidTicketKolvo(kolvoTickets, antiClassType)) {
			printErrorMessage(classType+4); //такого колва нет, но есть ___ в количестве
			printKolvoTickets(antiClassType, ticket); //таком-то количстве
		}
		else {
			printErrorMessage(21);
		}
	}
	else { printMessage(1); }
	return 0;
}


//функция поиска по пункту назначения(2) или типу самолёта(1)
void poiskByPunktOrType(std::vector<Flight>& flightList, std::string whatFind, int typePoisk) {
	bool isFind = false;
	for (int i = 0; i < flightList.size(); i++) {
		if (flightList[i].isSimilarPole(typePoisk,whatFind)) {
			if (!isFind) {
				printShapkaProsmotr();
				isFind = true;
			}
			printTickets(flightList, i, i + 1);
		}
	}
}


//функция поиска по цене билета
void poiskTicketPrice(std::vector<Flight>& flightList,int classType, int sravnenie, int summa) {
	int caseForSwitch = classType*10 + sravnenie; //выбор кейса при вызове сравнение
	bool isFirstSravnenie = true;
	for (int i = 0; i < flightList.size(); i++) {
		Flight f = flightList[i];
		bool isTrueSravnenie = false;
		switch (caseForSwitch) {
		case 11: if (f.sravnenieCen(2, summa, 1)) { isTrueSravnenie = true; } break; //summa>бизнес
		case 12: if (f.sravnenieCen(1, summa, 1)) { isTrueSravnenie = true; } break; //summa<бизнес
		case 21: if (f.sravnenieCen(2, summa, 2)) { isTrueSravnenie = true; } break; //summa>эконом
		case 22: if (f.sravnenieCen(1, summa, 2)) { isTrueSravnenie = true; } break; //summa<эконом
		case 31: if (f.sravnenieCen(2, summa, 3)) { isTrueSravnenie = true; } break; //summa>бизнес или эконом
		case 32: if (f.sravnenieCen(1, summa, 3)) { isTrueSravnenie = true; } break; //summa<бизнес или эконом
		default: {
			printErrorMessage(27);
			return;
		}
		}
		if (isTrueSravnenie) {
			if (isFirstSravnenie) {
				printShapkaProsmotr();
				isFirstSravnenie = false;
			}
			printTickets(flightList, i, i + 1);
		}
	}
	if (isFirstSravnenie) { printErrorMessage(2); }
}


//функция выбора типа поиска
void poiskTicket(std::vector<Flight>& flightList) {
	int vibor = inputInt(2,2);
	switch (vibor) {
	case 0: return;
	case 1: {
		poiskByPunktOrType(flightList,inputStr(10,1),1); //поиск по типу самолёта
		break;
	}
	case 2: {
		poiskByPunktOrType(flightList, inputStr(7,1),2); //поиск по пункту назначения
		break;
	}
	case 3: { //поиск по цене билета
		int classType = inputInt(3,2);
		if (classType == -1 || (classType != 1 && classType != 2 && classType!=3)){ 
			printErrorMessage(23); 
			return; 
		}
		int sravnenie = inputInt(4,2);
		if (sravnenie == -1 || (sravnenie != 1 && sravnenie != 2)) { 
			printErrorMessage(28);
			return; 
		}
		int summa = inputInt(23,1);
		if (summa == -1) { 
			printErrorMessage(29);
			return; 
		}
		poiskTicketPrice(flightList, classType, sravnenie, summa);
		break;
	}
	default: {
		printErrorMessage(27);
		return;
	}
	}

}


//компаратор для сортировки по стоимости бизнес класса
bool compareSortBiznesPrice(Flight& a, Flight& b) {
	return a.getIntSortParam(1) < b.getIntSortParam(1);
}
//сортировка по стоимости бизнес класса
void sortBiznesPrice(std::vector<Flight> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortBiznesPrice);
}



//компаратор для сортировки по стоимости эконом класса
bool compareSortEkonomPrice(Flight& a, Flight& b) {
	return a.getIntSortParam(2) < b.getIntSortParam(2);
}
//сортировка по стоимости эконом класса класса
void sortEkonomPrice(std::vector<Flight> &ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortEkonomPrice);
}



//компаратор для сортировки по колву бизнес
bool compareSortKolvoBiznes(Flight& a, Flight& b) {
	return a.getIntSortParam(3) < b.getIntSortParam(3);
}
//сортировка по колву бизнес
void sortKolvoBiznes(std::vector<Flight>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoBiznes);
}


//компаратор для сортировки по колву эконом
bool compareSortKolvoEkonom(Flight& a,Flight& b) {
	return a.getIntSortParam(4) < b.getIntSortParam(4);
}
//сортировка по колву эконом
void sortKolvoEkonom(std::vector<Flight>& ticketList) {
	std::sort(ticketList.begin(), ticketList.end(), compareSortKolvoEkonom);
}


//функция выбора сортировки
void sortTicket(std::vector<Flight> ticketList) {
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
	default: {
		printErrorMessage(27);
		return;
	}
	}
	printTickets(ticketList, 0, -1);
}
