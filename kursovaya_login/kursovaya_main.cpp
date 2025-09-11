#pragma once
#include "Funkcii\Funkcii.h"
#include <Windows.h>
#include <clocale>
#include "Moduli\Administrator\ModulAdministrator.h"
#include "Moduli\Polzovatel\PolzovatelModul.h"
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::locale::global(std::locale(""));
    srand(static_cast<unsigned int>(time(0)));
    int accountIndex = -1;
    std::vector<Account> vectorAccounts = getAccounts();
    while (true) {
        if (accountIndex!=-1) {
            int vibor;
            if (vectorAccounts[accountIndex].getRole()==0) {
                startPolzovatel();
            }
            else if (vectorAccounts[accountIndex].getRole() == 1) {
                startAdministrator(vectorAccounts, accountIndex);
            }
            return 0;
        }
        else {
            accountIndex = loginInAccount(vectorAccounts);
        }
    }
    return 1;
}