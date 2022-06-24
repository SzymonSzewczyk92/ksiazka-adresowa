#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

fstream file;
int userID;

void showUserMainMenu(); //function without body, necessary to activate showExitMenu
void showMainMenu(); //function without body, necessary to activate showExitMenu

void showExitMenu() {
  int actionNumber;
  system("cls");
  cout << "Wybierz numer akcji:" << endl;
  cout << "1. Wroc do menu glownego" << endl;
  cout << "2. Zamknij ksiazke adresowa" << endl;
  cin >> actionNumber;
  if (actionNumber == 1) {
    showMainMenu();
  } else if (actionNumber == 2) {
    exit(0);
  }
}

struct contactElements {
  int IDnumber = 0; int userIDnumber = 0;
  string name = "", surname = "", phoneNumber = "", emailAddress = "", address = "";
};

vector < contactElements > contactBook;

struct userElements {
  int userIDnumber = 0;
  string userName = "", password = "";
};

vector < userElements > userBook;

void deleteContactData() {
  ofstream file("dane.txt");
}

void deleteUserData() {
  ofstream file("users.txt");
}

int findHighestIDnumber() {
  ifstream in ("dane.txt");
  int contactsNumber = contactBook.size();
  int highestID = 0;
  for (int i = 0; i < contactsNumber; i++) {
    if (contactBook[i].IDnumber > highestID) {
      highestID = contactBook[i].IDnumber;
    };
  };
  return (highestID);
}

int findHighestUserIDnumber() {
  ifstream in ("users.txt");
  int usersNumber = userBook.size();
  int highestUserID = 0;
  for (int i = 0; i < usersNumber; i++) {
    if (userBook[i].userIDnumber > highestUserID) {
      highestUserID = userBook[i].userIDnumber;
    };
  };
  return (highestUserID);
}

void getContactsFromFile() {
  contactBook.clear();
  contactElements imported;
  string line, importedElements;
  int lineLength;

  file.open("dane.txt", ios:: in );
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream ss(line);
      while (getline(ss, line, '|')) {
        imported.IDnumber = atoi(line.c_str());
        getline(ss, line, '|');
        imported.userIDnumber = atoi(line.c_str());
        getline(ss, line, '|');
        imported.name = line;
        getline(ss, line, '|');
        imported.surname = line;
        getline(ss, line, '|');
        imported.phoneNumber = line;
        getline(ss, line, '|');
        imported.emailAddress = line;
        getline(ss, line, '|');
        imported.address = line;
        contactBook.push_back(imported);
      };
    }
  }
  file.close();
}

void getUsersFromFile() {
  userBook.clear();
  userElements imported;
  string line, importedElements;
  int lineLength;

  file.open("users.txt", ios:: in );
  if (file.is_open()) {
    while (getline(file, line)) {
      std::stringstream ss(line);
      while (getline(ss, line, '|')) {
        imported.userIDnumber = atoi(line.c_str());
        getline(ss, line, '|');
        imported.userName = line;
        getline(ss, line, '|');
        imported.password = line;
        userBook.push_back(imported);
      };
    }
  }
  file.close();
}

void exportContactDataToFile() {
  deleteContactData();
  fstream file;
  file.open("dane.txt", ios::app);
  system("cls");
  int highestID = findHighestIDnumber();
  int contactsNumber = contactBook.size();

  for (int j = 1; j <= highestID; j++) {
    for (int i = 0; i < contactsNumber; i++) {
      if (contactBook[i].IDnumber == j) {
        file << contactBook[i].IDnumber << "|";
        file << contactBook[i].userIDnumber << "|";
        file << contactBook[i].name << "|";
        file << contactBook[i].surname << "|";
        file << contactBook[i].phoneNumber << "|";
        file << contactBook[i].emailAddress << "|";
        file << contactBook[i].address << endl;
      }
    }
  }
  file.close();
  file.flush();
  getContactsFromFile();
  showExitMenu();
}

void exportUserDataToFile() {
  deleteUserData();
  fstream file;
  file.open("users.txt", ios::app);
  system("cls");
  int highestID = findHighestUserIDnumber();
  int usersNumber = userBook.size();

  for (int j = 1; j <= highestID; j++) {
    for (int i = 0; i < usersNumber; i++) {
      if (userBook[i].userIDnumber == j) {
        file << userBook[i].userIDnumber << "|";
        file << userBook[i].userName << "|";
        file << userBook[i].password << endl;
      }
    }
  }
  file.close();
  file.flush();
  getUsersFromFile();
  showUserMainMenu();
}

int findFirstFreeIdNumber() {
  ifstream in ("dane.txt");
  int contactsNumber = contactBook.size();
  int lastLine = 0;
  for (int i = 0; i < contactsNumber; i++) {
    if (contactBook[i].IDnumber != (i + 1)) {
      lastLine = i + 1;
      return (lastLine);
    }
  };
  lastLine = contactsNumber + 1;
  return (lastLine);
}

int findFirstFreeUserIdNumber() {
  ifstream in ("users.txt");
  int usersNumber = userBook.size();
  int lastLine = 0;
  for (int i = 0; i < usersNumber; i++) {
    if (userBook[i].userIDnumber != (i + 1)) {
      lastLine = i + 1;
      return (lastLine);
    }
  };
  lastLine = usersNumber + 1;
  return (lastLine);
}

void addNewContact() {
  getContactsFromFile();
  ifstream file;
  file.open("dane.txt", ios::app);
  contactElements imported;

  imported.IDnumber = findFirstFreeIdNumber();
  imported.userIDnumber = userID;
  cout << "Wpisz imie:";
  cin >> imported.name;
  cout << "Wpisz nazwisko:";
  cin >> imported.surname;
  cout << "Wpisz numer telefonu:";
  cin >> imported.phoneNumber;
  cout << "Wpisz adres mailowy:";
  cin >> imported.emailAddress;
  cout << "Wpisz adres zamieszkania:";
  cin.ignore();
  getline(cin, imported.address);
  contactBook.push_back(imported);

  system("cls");
  cout << "Kontakt zostal pomyslnie dodany!" << endl << endl;
  file.close();
  exportContactDataToFile();
}

void searchByName() {
  getContactsFromFile();
  string nameToFind;
  cout << "Podaj imie do wyszukania:";
  cin >> nameToFind;

  int contactsNumber = contactBook.size();

  for (int i = 0; i < contactsNumber; i++) {
    if ((contactBook[i].name == nameToFind) && (contactBook[i].userIDnumber == userID)) {
      cout << contactBook[i].IDnumber << " ";
      cout << contactBook[i].name << " ";
      cout << contactBook[i].surname << " ";
      cout << contactBook[i].phoneNumber << " ";
      cout << contactBook[i].emailAddress << " ";
      cout << contactBook[i].address << endl;
    };
  }
  cout << endl;
  system("pause");
  showExitMenu();
}

void searchBySurname() {
  getContactsFromFile();
  string surnameToFind;
  cout << "Podaj nazwisko do wyszukania:";
  cin >> surnameToFind;

  int contactsNumber = contactBook.size();

  for (int i = 0; i < contactsNumber; i++) {
    if ((contactBook[i].surname == surnameToFind) && (contactBook[i].userIDnumber == userID)) {
      cout << contactBook[i].IDnumber << " ";
      cout << contactBook[i].name << " ";
      cout << contactBook[i].surname << " ";
      cout << contactBook[i].phoneNumber << " ";
      cout << contactBook[i].emailAddress << " ";
      cout << contactBook[i].address << endl;
    };
  }
  cout << endl;
  system("pause");
  showExitMenu();
}

void showAllContacts() {
  system("cls");
  getContactsFromFile();
  int contactsNumber = contactBook.size();
  for (int i = 0; i < contactsNumber; i++) {
    if (contactBook[i].userIDnumber == userID){
    cout << contactBook[i].IDnumber << " ";
    cout << contactBook[i].userIDnumber << " ";
    cout << contactBook[i].name << " ";
    cout << contactBook[i].surname << " ";
    cout << contactBook[i].phoneNumber << " ";
    cout << contactBook[i].emailAddress << " ";
    cout << contactBook[i].address << endl;
    }
  }
  cout << endl;
  system("pause");
  showExitMenu();
}

void deleteContact() {
  system("cls");
  int contactToDelete;
  int contactsNumber = contactBook.size();
  char deletionConfirmation;
  string line;

  cout << "Wpisz numer ID kontaktu do usuniecia:";
  cin >> contactToDelete;

  system("cls");

  for (int i = 0; i < contactsNumber; i++) {
    if (contactBook[i].IDnumber == contactToDelete) {
      cout << "Czy chcesz usunac ponizszy kontakt? <t/n>" << endl << endl;
      cout << contactBook[i].IDnumber << " " << contactBook[i].name << " " << contactBook[i].surname << " " << contactBook[i].phoneNumber << " " << contactBook[i].emailAddress << " " << contactBook[i].address << endl << endl;

      cin >> deletionConfirmation;
      if (deletionConfirmation == 't') {
        auto it = contactBook.begin() + i;
        contactBook.erase(it);
        exportContactDataToFile();
      } else showExitMenu();
    }
  };

  int newContactsNumber = contactBook.size();
  if (contactsNumber == newContactsNumber) {
    cout << "Brak kontaktu o podanym numerze ID" << endl;
    system("pause");
    showExitMenu();
  }
};

void editContactAttributes() {
  system("cls");
  int contactToChange;
  int attributeToChange, attributeNumber;
  int contactsNumber = contactBook.size();
  string attributeContent;

  cout << "Wpisz numer ID kontaktu do zmiany:";
  cin >> contactToChange;

  cout << endl << "Wybierz atrybut do zmiany:" << endl;
  cout << "1. Imie" << endl;
  cout << "2. Nazwisko" << endl;
  cout << "3. Numer telefonu" << endl;
  cout << "4. Adres email" << endl;
  cout << "5. Adres zamieszkania" << endl;
  cout << "6. Wroc do menu" << endl;
  cin >> attributeToChange;
  cout << "Wpisz nowa wartosc atrybutu:" << endl;
  cin >> attributeContent;

      for (int i = 0; i < contactsNumber; i++) {
        if (contactBook[i].IDnumber == contactToChange) {
          attributeNumber = i;
          cout << contactBook[i].IDnumber;
        }
      };

  switch (attributeToChange) {
  case 1:
    contactBook[attributeNumber].name = attributeContent;
    exportContactDataToFile();
    break;
  case 2:
    contactBook[attributeNumber].surname = attributeContent;
    exportContactDataToFile();
    break;
  case 3:
    contactBook[attributeNumber].phoneNumber = attributeContent;
    exportContactDataToFile();
    break;
  case 4:
    contactBook[attributeNumber].emailAddress = attributeContent;
    exportContactDataToFile();
    break;
  case 5:
    contactBook[attributeNumber].address = attributeContent;
    exportContactDataToFile();
    break;
  case 6:
    showMainMenu;
    break;
  }
  exportContactDataToFile();
}

void userRegistration() {
getUsersFromFile();
  ifstream file;
  file.open("users.txt", ios::app);
  userElements imported;

  imported.userIDnumber = findFirstFreeUserIdNumber();
  cout << "Wpisz nazwe:";
  cin >> imported.userName;
  cout << "Wpisz haslo:";
  cin >> imported.password;
  cin.ignore();
  userBook.push_back(imported);

  system("cls");
  cout << "Uzytkownik zostal pomyslnie dodany!" << endl << endl;
  file.close();
  exportUserDataToFile();
}

void userLogin() {
  system("cls");
  getUsersFromFile();

  cout << "Podaj nazwe uzytkownika: ";
  string userLogin;
  cin >> userLogin;

  cout << "Podaj haslo: ";
  string userPassword;
  cin >> userPassword;

  int usersNumber = userBook.size();

  for (int i = 0; i < usersNumber; i++) {
    if ((userBook[i].userName == userLogin) && (userBook[i].password == userPassword)) {
    userID = userBook[i].userIDnumber;
    showMainMenu();
    }
  }
  cout << endl;
  cout << "Bledna nazwa uzytkownika lub haslo. Wprowadz poprawne dane lub zarejestruj sie." << endl;
  system("pause");
  showUserMainMenu();
}

void editUserAttributes() {
  system("cls");
  ifstream file;
  file.open("users.txt");
  int attributeNumber;
  int usersNumber = userBook.size();
  string attributeContent;

  cout << "Wpisz nowe haslo:" << endl;
  cin >> attributeContent;

      for (int i = 0; i < usersNumber; i++) {
        if (userBook[i].userIDnumber == userID) {
          attributeNumber = i;
        }
      };

    userBook[attributeNumber].password = attributeContent;
    exportUserDataToFile();
}

void showMainMenu() {
  system("cls");
  cout << "****KSIAZKA ADRESOWA**** ID:" << userID << endl << endl;
  cout << "Wybierz akcje:" << endl;
  cout << "1. Dodaj adresata" << endl;
  cout << "2. Wyszukaj po imieniu" << endl;
  cout << "3. Wyszukaj po nazwisku" << endl;
  cout << "4. Wyswietl wszystkich adresatow" << endl;
  cout << "5. Usun adresata" << endl;
  cout << "6. Edytuj adresata" << endl;
  cout << "7. Zmien haslo" << endl;
  cout << "8. Wyloguj sie" << endl;
  cout << "9. Zakoncz program" << endl;

  int actionNumber;
  do {
    cin >> actionNumber;
  }
  while ((actionNumber < 1) && (actionNumber > 7)); {
    switch (actionNumber) {
    case 1:
      addNewContact();
      break;
    case 2:
      searchByName();
      break;
    case 3:
      searchBySurname();
      break;
    case 4:
      showAllContacts();
      break;
    case 5:
      deleteContact();
      break;
    case 6:
      editContactAttributes();
      break;
    case 7:
      editUserAttributes();
      break;
    case 8:
      userID = 0;
      showUserMainMenu();
      break;
    case 9:
      exit(0);
      break;
    }
  }
}

void showUserMainMenu() {
  system("cls");
  cout << "****MENU GLOWNE****" << endl << endl;
  cout << "1. Rejestracja" << endl;
  cout << "2. Logowanie" << endl;
  cout << "9. Koniec programu" << endl;

  int actionNumber;
  do {
    cin >> actionNumber;
  }
  while ((actionNumber != 1) && (actionNumber != 2) && (actionNumber != 9)); {
    switch (actionNumber) {
    case 1:
      userRegistration();
      break;
    case 2:
      userLogin();
      break;
    case 9:
      exit(0);
      break;
    }
  }
}

int main() {
  ifstream file;
  file.open("data.txt");
  if (file) {
    file.close();
    getContactsFromFile();
    getUsersFromFile();
    showUserMainMenu();;
  }
  else {
    file.close();
    showUserMainMenu();
  }
}
