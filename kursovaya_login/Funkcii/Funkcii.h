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


int checkLogin(std::string v_login, std::string v_password, std::vector<Account> &vectorAccounts);
int checkIfInDB(std::string login, std::vector<Account>&vectorAccounts);
std::string vvodParol();
void isThereBD();
std::vector<Account> getAccounts();
bool zapisAccount(std::string login, std::string password, int role, std::vector<Account>&vectorAccounts, bool isChange);
int loginInAccount(std::vector<Account> &vectorAccounts);
std::vector<Account> inputNewAccountData(bool isAdministrator);
std::string saultGen();