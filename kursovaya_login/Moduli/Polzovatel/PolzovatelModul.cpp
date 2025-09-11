#include "PolzovatelModul.h";






bool User::startUserMenu(){
	int vibor;
	std::vector<Flight> ticketList = getTickets();
	while (true) {
		printShapka(2);
		vibor = inputInt(12, 2);
		switch (vibor) {
		case 0: return 1;
		case 1: {
			printShapkaProsmotr();
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
		case 5: {
			printTicketInfo(ticketList);
			break;
		}
		default: {
			printErrorMessage(27);
		}
		}
	}
	return 1;
}

//запуск меню пользователя
int startPolzovatel() {
	User user;
	if (user.startUserMenu()) { return 1; }
	return 0;
}