#pragma once
#include "../Funkcii/Funkcii.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

std::vector<Flight> getTickets();

bool addNewZapis(std::vector<Flight>& ticketList);
bool editZapis(std::vector<Flight>& ticketList);
bool deleteZapis(std::vector<Flight>& ticketList);
bool zapisTickets(std::vector<Flight>& ticketList);
bool buyTicket(std::vector<Flight> &ticketList);

void poiskTicket(std::vector<Flight>& ticketList);
void sortTicket(std::vector<Flight> ticketList);
void printShapkaProsmotr();
void printTickets(std::vector<Flight>& ticketList, int startI, int kolvoPrint);
void printTicketInfo(std::vector<Flight>& ticketList);