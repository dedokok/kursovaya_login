#include<iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <chrono>






class Flight {
private:
	int raceNumber;
	std::string samoletType;
	std::string punktNaznacheniya;
	std::string dateVilet;
	std::string vremyaVilet;
	std::string vremyaPrilet;
	int vmestimost;
	int kolvoTicketBiznes;
	int stoimostBiznes;
	int kolvoTicketEkonom;
	int stoimostEkonom;
public:
	Flight() : raceNumber(0), samoletType(""), punktNaznacheniya(""), dateVilet(""), vremyaVilet(""),
		vremyaPrilet(""), vmestimost(0), kolvoTicketBiznes(0), stoimostBiznes(0), kolvoTicketEkonom(0),
		stoimostEkonom(0) {};

	~Flight() {};


	//метод вывода информации о тикете (полиморфизм)
	void printSomeInfo() {
		std::cout << "Это билет в " << punktNaznacheniya << ", отправка будет " << dateVilet << " в " << vremyaVilet << std::endl;
	}


	//метод проверки правильности введённого поля рейса
	bool isCorrectFlight(int optionIndex) {
		switch (optionIndex) {
		case 1: { if (raceNumber < 0 || raceNumber > 999) { return 0; }; break; } break;
		case 7: { if (vmestimost < 0 || vmestimost > 999)return 0; } break;
		case 8: { if (kolvoTicketBiznes < 0 || kolvoTicketBiznes > 999)return 0; } break;
		case 9: { if (stoimostBiznes < 0 || stoimostBiznes > 9999)return 0; }break;
		case 10: { if (kolvoTicketEkonom < 0 || kolvoTicketEkonom > 999)return 0; } break;
		case 11: { if (stoimostEkonom < 0 || stoimostEkonom > 9999)return 0; } break;
		default: return 0;
		}
		return 1;
	}


	//метод изменения строковых параметров по индексу + снизу перегрузка
	void setParam(std::string strParam, int indexParam) {
		switch (indexParam) {
		case 1: { samoletType = strParam; break; }
		case 2: { punktNaznacheniya = strParam; break; }
		case 3: { dateVilet = strParam; break; }
		case 4: { vremyaVilet = strParam; break; }
		case 5: { vremyaPrilet = strParam; break; }

		}
	}


	//метод изменения числовых параметров по индексу + перегрузка
	void setParam(int intParam, int indexParam) {
		switch (indexParam) {
		case -4: { raceNumber = intParam; break; }
		case 2: { vmestimost = intParam; break; }
		case 3: { kolvoTicketBiznes = intParam; break; }
		case 4: { stoimostBiznes = intParam; break; }
		case 5: { kolvoTicketEkonom = intParam; break; }
		case 6: { stoimostEkonom = intParam; break; }
		}
	}


	//вывод всех строк рейса для таблицы
	void printFlight() {
		std::cout <<
			"| " << std::setw(3) << raceNumber <<
			" | " << std::left << std::setw(15) << samoletType <<
			" | " << std::left << std::setw(15) << punktNaznacheniya <<
			" | " << std::setw(10) << dateVilet <<
			" | " << std::setw(5) << vremyaVilet <<
			" | " << std::setw(5) << vremyaPrilet <<
			" | " << std::setw(3) << vmestimost <<
			" | " << std::setw(3) << kolvoTicketBiznes <<
			" | " << std::setw(4) << stoimostBiznes <<
			" | " << std::setw(3) << kolvoTicketEkonom <<
			" | " << std::setw(4) << stoimostEkonom <<
			"|" << std::endl;
		printf("-------------------------------------------------------------------------------------------------------\n");
	}



	//метод проверки, совпадает ли ведённый номер рейса с номером рейсом записи
	bool isSimilarRaceNumber(int v_raceNumber) {
		if (v_raceNumber == raceNumber) {
			return true;
		}
		return false;
	}

	//функция проверки, есть ли введённае строка в строковом поле
	bool isSimilarPole(int poleIndex, std::string whatFind) {
		switch (poleIndex) {
		case 1: if (samoletType.find(whatFind) != -1) { return 1; } break;
		case 2: if (punktNaznacheniya.find(whatFind) != -1) { return 1; } break;
		}
		return 0;
	}


	//метод сравнения указанной цены с ценой в записи, sravnenie == 1 - больше, == 2 - меньше
	int sravnenieCen(int sravnenie, int summa, int typeClass) {
		if(sravnenie ==1){
			if (typeClass == 1) {
				return summa > stoimostBiznes;
			}
			else if(typeClass == 2) {
				return summa > stoimostEkonom;
			}
			else if (typeClass == 3) {
				return summa > stoimostEkonom || summa > stoimostBiznes;
			}
		}
		else if (sravnenie == 2) {
			if (typeClass == 1) {
				bool st = summa < stoimostBiznes;
				return st;
			}
			else if(typeClass==2){
				return summa < stoimostEkonom;
			}
			else if (typeClass == 3) {
				return summa < stoimostEkonom || summa < stoimostBiznes;
			}
		}
		return -1;
	}


	//геттеры
	int getIntSortParam(int paramIndex) {
		switch (paramIndex) {
		case 1: { return stoimostBiznes; }//получение стоимости бизнес класса
		case 2: { return stoimostEkonom; }//получение стоимости эконом класса
		case 3: { return kolvoTicketBiznes; }//получение количества билетов бизнес класса
		case 4: { return kolvoTicketEkonom; }//получение количества билетов эконом класса
		case 5: { return raceNumber; }
		}
		return -1;
	}


	//метод проверки формата времени
	bool isTrueFormatVremya(int whatVremya) {//1 - время вылета, 2 - время прилёта
		std::tm tm = {};
		std::stringstream ss1(vremyaVilet);
		std::stringstream ss2(vremyaPrilet);
		ss1 >> std::get_time(&tm, "%H:%M");
		ss2 >> std::get_time(&tm, "%H:%M");
		if (whatVremya == 1) {
			if (ss1.fail()) {
				return 0;
			}
			else {
				return 1;
			}
		}
		else if (whatVremya==2){
			if (ss2.fail()) {
				return 0;
			}
			else {
				return 1;
			}
		}
		else {
			if (ss2.fail() || ss1.fail()) {
				return 0;
			}
			else {
				return 1;
			}
		}

	}


	//метод проверки формата даты
	bool isTrueFormatDate() {
		std::stringstream ss(dateVilet);
		std::chrono::year_month_day ymd;
		if (ss >> std::chrono::parse("%d.%m.%Y", ymd) && ymd.ok() && ss.eof()) {
			return 1;
		}
		else { return 0; }

	}


	//метод покупки билетов (уменьшение их количества)
	bool buyTickets(int kolvoTickets, int classType) {
		switch (classType) {
		case 1: { kolvoTicketBiznes -= kolvoTickets; return 1; }
		case 2: { kolvoTicketEkonom -= kolvoTickets; return 1; }
		}
		return 0;
	}


	//метод проверки количества билетов
	bool isValidTicketKolvo(int kolvoTicket, int classType) {
		if (classType==1 && kolvoTicketBiznes >= kolvoTicket) {
			return 1;
		}
		else if (classType==2 && kolvoTicketEkonom >= kolvoTicket){
			return 1;
		}
		return 0;
	}


	//метод получения количества билетов
	int getKolvoTickets(int classType) {
		if (classType == 1) { return kolvoTicketBiznes; }
		else if (classType == 2) { return kolvoTicketEkonom; }
		else { return -1; }
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Flight, raceNumber, samoletType, punktNaznacheniya, dateVilet, vremyaVilet,
		vremyaPrilet, vmestimost, kolvoTicketBiznes, stoimostBiznes, kolvoTicketEkonom,
		stoimostEkonom); //чтобы можно было преобразовать json строки в объекты типа класса
};