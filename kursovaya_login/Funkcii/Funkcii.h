#pragma once
#include <fstream>
#include <string>

#include <iostream>

#include <vector>
#include "Account.cpp"
#include "sha256.h" //взял библиотеку https://create.stephan-brumme.com/hash-library/ для хеширования
//эти 2 для toLower для поиска логина с списке
#include <algorithm>
#include <cctype> 

//для звёздочек в консоли
#include <conio.h>

#include <nlohmann/json.hpp>


bool zapisAccount(std::string login, std::string password, int role, std::vector<Account>& vectorAccounts, bool isChange);
bool inputIntSsilka(int& ticketField, std::string prompt);
bool getAccept();

int checkLogin(std::string v_login, std::string v_password, std::vector<Account> &vectorAccounts);
int checkIfInDB(std::string login, std::vector<Account>&vectorAccounts);
int loginInAccount(std::vector<Account>& vectorAccounts);
int inputInt(std::string prompt);

std::string vvodParol();
std::string inputStr(std::string prompt);
std::string saultGen();

std::vector<Account> getAccounts();
std::vector<Account> inputNewAccountData(bool isAdministrator);

void inputStrSsilka(std::string& ticketField, std::string prompt);
void printMessage(int messageCode);
void isThereBD();
void printShapkaAccounts();
void printAccounts(std::vector<Account>& vectorAccounts, int startI, int kolvoPrint);
void printShapka(int shapkaIndex);