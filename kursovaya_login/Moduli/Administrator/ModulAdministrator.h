#pragma once
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include "../../Funkcii/Funkcii.h"
//эти 2 для toLower для поиска логина с списке
#include <algorithm>
#include <cctype> 

//для звёздочек в консоли
#include <conio.h>

#include <nlohmann/json.hpp>
void startAdministrator(std::vector<Account> &vectorAccounts,int accountIndex);