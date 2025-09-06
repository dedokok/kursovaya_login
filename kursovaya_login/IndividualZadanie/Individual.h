#pragma once
#pragma execution_character_set("utf-8")
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <windows.h>
#include <limits>
#include <vector>
#include "IndividualClass.cpp"
#include "../Funkcii/sha256.h" //взял библиотеку https://create.stephan-brumme.com/hash-library/ для хеширования
//эти 2 для toLower для поиска логина с списке
#include <algorithm>
#include <cctype> 

//для звёздочек в консоли
#include <conio.h>
#include <nlohmann/json.hpp>

void printMessage(int messageCode);
std::vector<Ticket> getTickets();
bool addZapis(std::vector<Ticket>& ticketList);
bool editZapis(std::vector<Ticket>& ticketList);
bool deleteZapis(std::vector<Ticket>& ticketList);
int buyTicket(std::vector<Ticket>& ticketList);
void poiskTicket(std::vector<Ticket>& ticketList);
void sortTicket(std::vector<Ticket> ticketList);
void printShapka();
void printTickets(std::vector<Ticket>& ticketList, int startI, int kolvoPrint);