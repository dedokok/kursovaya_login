#include "Individual.h"
//все вводы сделать через inputInt и inputStr

void printTickets(std::vector<Ticket> &ticketList) {
	 //     | 0 | AirBus111 | Moscow | 18.02.2008 | 18:00 | 20 : 00 | 100 | 10 | 1000 | 40 | 500 |
	printf("-------------------------------------------------------------------------------------------------------\n");
	printf("|  №  |       Тип       |       Куда      |    День    | Время | Время | Вмес| Кол | Ст.  | Кол.| Ст. |\n");
	printf("|  №  |    самолёта     |       летит     |   вылета   | вылета|прибыт.| тим.| биз | Биз. | эк. | эк. |\n");
	printf("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < ticketList.size(); i++) {
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
	std::cout << "Введите номер рейса для покупки билета:\n";
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
void printError(int errorCode) {
	std::string error = "Ошибка";
	switch (errorCode) {
	case 1: { error = "Ошибка ввода\n"; break; }
	case 2: { error = "Ошибка вывода\n"; break; }
	case 3: { error = "Слишком много!\n"; break; }
	case 4: { error = "Такой рейс уже есть\n"; break; }
	}
	std::cout << error;
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

//функция покупки билета
int buyTicket(std::vector<Ticket>& ticketList) {
	int ticketRace = getTicketRace();
	int indexRace = getRaceIndex(ticketList, ticketRace);
	int kolvoTicket = 0, classType_int, maxTicket=0;
	std::string classType_str;
	if (indexRace == -1) {
		printError(-1);
		return -1;
	}
	getTicketKolvoType(ticketList, indexRace, kolvoTicket, classType_int, maxTicket);

	if (kolvoTicket <= maxTicket) {
		if (classType_int) {
			ticketList[indexRace].kolvoTicketBiznes-=kolvoTicket;
			return 1;
		}
		else {
			ticketList[indexRace].kolvoTicketEkonom-=kolvoTicket;
			return 1;
		}
	}
	else {
		printError(3);
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
			printError(4);
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
		printError(1);
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
int addZapis(std::vector<Ticket> &ticketList) {

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
	int indexRaceInVector = getRaceIndex(ticketList, ticketRace);
	if (indexRaceInVector != -1) {
		Ticket ticket=ticketList[indexRaceInVector]; 
		
			std::string string_input;
			int int_input;
			bool isRunInputZapis = true;
			

			
			ticketList[indexRaceInVector] = ticket;
			zapisTickets(ticketList);
			return 1;
		
	}
	return 0;
}



//основная функция режима редактирования в "Работа с данными"
void editMode() {
	int vibor;
	std::vector<Ticket> ticketList = getTickets();

	bool isRunEM = true;
	while (isRunEM) {

		std::cout << "Выберите один из вариантов:\n1.Просмотр\n2.Добавление\n3.Редактирование\n4.Удаление\n";
		std::cin >> vibor;
		switch (vibor) {
		case 1: {
			printTickets(ticketList);
			break;
		}
		case 2: {
			addZapis(ticketList);
			break;
		}
		case 3: {
			editZapis(ticketList);
			break;
		}

		}
	}
}
//if (buyTicket(ticketList) == 1) {
			//	zapisTickets(ticketList);
			//}
			//break;