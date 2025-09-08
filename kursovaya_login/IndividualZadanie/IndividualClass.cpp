#include<iostream>
#include <nlohmann/json.hpp>


class Ticket {
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
	Ticket() : raceNumber(0), samoletType(""), punktNaznacheniya(""), dateVilet(""), vremyaVilet(""),
		vremyaPrilet(""), vmestimost(0), kolvoTicketBiznes(0), stoimostBiznes(0), kolvoTicketEkonom(0),
		stoimostEkonom(0) {};
	
	~Ticket() {};

	//метод изменения строковых параметров по индексу
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
		case 1: { raceNumber = intParam; break; }
		case 2: { vmestimost = intParam; break; }
		case 3: { kolvoTicketBiznes = intParam; break; }
		case 4: { stoimostBiznes = intParam; break; }
		case 5: { kolvoTicketEkonom = intParam; break; }
		case 6: { stoimostEkonom = intParam; break; }
		}
	}


	void printTicket(){
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

	bool isValidTicket() {
		if(raceNumber < 1000 && raceNumber>0 && samoletType.length() < 16 && samoletType.length() > 0
			&& dateVilet.length() > 0 && dateVilet.length() < 11
			&& vremyaPrilet.length() > 0 && vremyaPrilet.length() < 6
			&& vremyaVilet.length() > 0 && vremyaVilet.length() < 6
			&& vmestimost > -1 && vmestimost<1000
			&& kolvoTicketBiznes>-1 && kolvoTicketBiznes<1000
			&& kolvoTicketEkonom>-1 && kolvoTicketEkonom<1000
			&& stoimostBiznes>-1 && stoimostBiznes<10000
			&& stoimostEkonom>-1 && stoimostEkonom < 10000) {
			return true;
		}
		else { return false; }
	}


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Ticket, raceNumber, samoletType, punktNaznacheniya, dateVilet, vremyaVilet,
		vremyaPrilet, vmestimost, kolvoTicketBiznes, stoimostBiznes, kolvoTicketEkonom,
		stoimostEkonom); //чтобы можно было преобразовать json строки в объекты типа класса
};