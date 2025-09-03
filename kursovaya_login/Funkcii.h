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
bool checkLogin(std::string v_login, std::string v_password);
void newRegistration(std::string login, std::string password,int new_role);
int checkIfInDB(std::string login, std::vector<Account>vectorAccounts);
std::string vvodParol();
void isThereBD();
bool loginInAccount();
void zapisAccount(std::string login, std::string password, int role);