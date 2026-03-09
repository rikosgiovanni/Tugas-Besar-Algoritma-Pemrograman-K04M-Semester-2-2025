#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <string.h>
#include "auth.h" // untuk struct User
void printmenu();

//Print menu
void help(User *loggedInUser);

#endif