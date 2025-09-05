#include "Individual.h"


void printTickets(std::vector<Ticket> &ticketList) {
	 //     | 0 | AirBus111 | Moscow | 18.02.2008 | 18:00 | 20 : 00 | 100 | 10 | 1000 | 40 | 500 |
	printf("------------------------------------------------------------------------------------\n");
	printf("| № |    Тип    |  Куда  |    День    | Время | Время | Вмес| Кол| Ст.  | Кол.| Ст.|\n");
	printf("| № | самолёта  |  летит |   вылета   | вылета|прибыт.| тим.| биз| Биз. | эк. | эк.|\n");
	printf("------------------------------------------------------------------------------------\n");
	for (int i = 0; i < ticketList.size(); i++) {
		Ticket t = ticketList[i];
		printf("| %i | %s | %s | %s | %s | %s | %i | %i | %i | %i | %i |\n",
			t.raceNumber, 
			t.samoletType.c_str(),
			t.punktNaznacheniya.c_str(),
			t.dateVilet.c_str(),
			t.vremyaVilet.c_str(),
			t.vremyaPrilet.c_str(),
			t.vmestimost, 
			t.kolvoTicketBiznes,
			t.stoimostBiznes, 
			t.kolvoTicketEkonom, 
			t.stoimostEkonom);
		printf("------------------------------------------------------------------------------------\n");
	}

}

int getMaxWidth(std::vector<Ticket>& ticketList, int setType) {
	int maxWidth = 0;
	for (int g = 0; g < 11; g++) {
		for (int i = 0; i < ticketList.size(); i++) {
			if (ticketList[i].punktNaznacheniya.length() > maxWidth) {
				maxWidth = ticketList[i].punktNaznacheniya.length();
			}
		}
	}
	return maxWidth;
}

void setMaxWidth(std::vector<Ticket>& ticketList) {
	int maxWidth = getMaxWidth(ticketList, 1);
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].punktNaznacheniya.length() < maxWidth) {
			int raznica = maxWidth - ticketList[i].punktNaznacheniya.length();
			for (int j = 0; j < raznica; j++) {
				ticketList[i].punktNaznacheniya += " ";
			}
		}
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

int getRaceIndex(std::vector<Ticket>& ticketList, int ticketRace) {
	for (int i = 0; i < ticketList.size(); i++) {
		if (ticketList[i].raceNumber == ticketRace) {
			return i;
		}
	}
	return -1;
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
		std::cout << "Ошибка\n";
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
		std::cout << "Слишком много!";
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


//void normalShirina(std::vector<Ticket>& ticketList) {
//	for (int i = 0; i < 11; i++) {
//		int maxLength = 0;
//		for (int j = 0; j < ticketList.size(); j++) {
//			if(ticketList[i].leng)
//		}
//	}
//}


void editMode() {
	int vibor;
	std::vector<Ticket> ticketList = getTickets();
	setMaxWidth(ticketList);
	//std::vector<Ticket> ticketList;
	//Ticket t;
	//t.raceNumber = 0;
	//t.samoletType = "AirBus111";
	//t.punktNaznacheniya = "Moscow";
	//t.dateVilet = "18.02.2008";
	//t.vremyaVilet = "18:00";
	//t.vremyaPrilet = "20:00";
	//t.vmestimost = 100;
	//t.kolvoTicketBiznes = 10;
	//t.stoimostBiznes = 1000;
	//t.kolvoTicketEkonom = 40;
	//t.stoimostEkonom = 500;
	//for (int i = 0; i < 30; i++) {
		//ticketList.push_back(t);
	//}
	//zapisTickets(ticketList);
	
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
			//if (buyTicket(ticketList) == 1) {
			//	zapisTickets(ticketList);
			//}
			//break;
		}

		}
	}
}