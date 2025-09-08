#pragma once
#include "../Funkcii/Funkcii.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

std::vector<Ticket> getTickets();

bool addZapis(std::vector<Ticket>& ticketList);
bool editZapis(std::vector<Ticket>& ticketList);
bool deleteZapis(std::vector<Ticket>& ticketList);
bool zapisTickets(std::vector<Ticket>& ticketList);

int  buyTicket(std::vector<Ticket> &ticketList);

void poiskTicket(std::vector<Ticket>& ticketList);
void sortTicket(std::vector<Ticket> ticketList);
void printShapkaProsmotr();
void printTickets(std::vector<Ticket>& ticketList, int startI, int kolvoPrint);