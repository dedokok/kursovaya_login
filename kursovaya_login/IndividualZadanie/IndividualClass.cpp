#include<iostream>
#include <nlohmann/json.hpp>

class Ticket {
public:
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

	Ticket() : raceNumber(0), samoletType(""), punktNaznacheniya(""), dateVilet(""), vremyaVilet(""),
		vremyaPrilet(""), vmestimost(0), kolvoTicketBiznes(0), stoimostBiznes(0), kolvoTicketEkonom(0),
		stoimostEkonom(0) {};
	
	~Ticket() {};


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Ticket, raceNumber, samoletType, punktNaznacheniya, dateVilet, vremyaVilet,
		vremyaPrilet, vmestimost, kolvoTicketBiznes, stoimostBiznes, kolvoTicketEkonom,
		stoimostEkonom); //чтобы можно было преобразовать json строки в объекты типа класса

};