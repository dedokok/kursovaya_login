#include "PolzovatelModul.h";


//запуск меню пользователя
int startPolzovatel() {
	int vibor;
	std::vector<Ticket> ticketList = getTickets();
	while (true) {
		vibor = inputInt("Выберите пункт меню:\n1.Просмотр\n2.Покупка билета (инд. задание)\n3.Поиск\n4.Сортировка\n0.Выход\n");
		switch (vibor) {
		case 0: return 1;
		case 1: {
			printShapka();
			printTickets(ticketList, 0, -1);
			break;
		}
		case 2: {
			if (buyTicket(ticketList)) {
				zapisTickets(ticketList);
			}
			break;
		}
		case 3: {
			poiskTicket(ticketList);
			break;
		}
		case 4: {
			sortTicket(ticketList);
			break;
		}
		}
	}
	return 0;
}