#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// CLEAR SCREEN FUNCTION

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// STRUCTS


struct Task {
    string text;
    bool done;
};

struct Habit {
    string name;
    int streak;
};

struct JournalEntry {
    string date;
    string text;
};


// GLOBAL ARRAYS


Task tasks[100];
int taskCount = 0;

Habit habits[50];
int habitCount = 0;

JournalEntry journal[100];
int journalCount = 0;

    
// FUNCTION DECLARATIONS


void mainMenu();
void todoMenu();
void habitMenu();
void journalMenu();

void addTask();
void viewTasks();
void markTaskDone();
void saveTasks();
void loadTasks();

void addHabit();
void viewHabits();
void increaseStreak();
void resetStreak();
void saveHabits();
void loadHabits();

void addJournalEntry();
void viewJournal();
void saveJournal();
void loadJournal();


// MAIN


int main() {
    loadTasks();
    loadHabits();
    loadJournal();

    mainMenu();
    return 0;
}


// MAIN MENU



void mainMenu() {
    int choice;

    do {
        clearScreen();
        cout << "==============================\n";
        cout << "   PERSONAL PRODUCTIVITY APP\n";
        cout << "==============================\n";
        cout << "1. To-Do List\n";
        cout << "2. Habit Tracker\n";
        cout << "3. Journal\n";
        cout << "4. Save All\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) todoMenu();
        else if (choice == 2) habitMenu();
        else if (choice == 3) journalMenu();
        else if (choice == 4) {
            saveTasks();
            saveHabits();
            saveJournal();
            cout << "All data saved.\n";
            cin.get();
        }

    } while (choice != 5);

    clearScreen();
    cout << "Goodbye!\n";
}


// TO-DO LIST MENU


void todoMenu() {
    int choice;

    do {
        clearScreen();
        cout << "--- TO-DO LIST ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Done\n";
        cout << "4. Back\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) addTask();
        else if (choice == 2) {
            clearScreen();
            viewTasks();
            cin.get();
        }
        else if (choice == 3) markTaskDone();

    } while (choice != 4);
}

void addTask() {
    clearScreen();
    cout << "Enter task: ";
    getline(cin, tasks[taskCount].text);
    tasks[taskCount].done = false;
    taskCount++;
}

void viewTasks() {
    cout << "Your Tasks:\n";
    for (int i = 0; i < taskCount; i++) {
        cout << i + 1 << ". " << tasks[i].text;
        if (tasks[i].done) cout << " [DONE]";
        cout << endl;
    }
}

void markTaskDone() {
    clearScreen();
    viewTasks();
    int num;
    cout << "\nWhich task number is done? ";
    cin >> num;

    if (num > 0 && num <= taskCount) {
        tasks[num - 1].done = true;
        cout << "Marked as done.\n";
    }
    cin.ignore();
    cin.get();
}

void saveTasks() {
    ofstream file("tasks.txt");
    for (int i = 0; i < taskCount; i++) {
        file << tasks[i].text << endl;
        file << tasks[i].done << endl;
    }
    file.close();
}

void loadTasks() {
    ifstream file("tasks.txt");
    if (!file.is_open()) return;

    while (!file.eof()) {
        string text;
        bool done;

        getline(file, text);
        if (text == "") break;

        file >> done;
        file.ignore();

        tasks[taskCount].text = text;
        tasks[taskCount].done = done;
        taskCount++;
    }

    file.close();
}


// HABIT TRACKER MENU


void habitMenu() {
    int choice;

    do {
        clearScreen();
        cout << "--- HABIT TRACKER ---\n";
        cout << "1. Add Habit\n";
        cout << "2. View Habits\n";
        cout << "3. Increase Streak\n";
        cout << "4. Reset Streak\n";
        cout << "5. Back\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) addHabit();
        else if (choice == 2) {
            clearScreen();
            viewHabits();
            cin.get();
        }
        else if (choice == 3) increaseStreak();
        else if (choice == 4) resetStreak();

    } while (choice != 5);
}

void addHabit() {
    clearScreen();
    cout << "Enter habit name: ";
    getline(cin, habits[habitCount].name);
    habits[habitCount].streak = 0;
    habitCount++;
}

void viewHabits() {
    cout << "Your Habits:\n";
    for (int i = 0; i < habitCount; i++) {
        cout << i + 1 << ". " << habits[i].name
            << " | Streak: " << habits[i].streak << endl;
    }
}

void increaseStreak() {
    clearScreen();
    viewHabits();
    int num;
    cout << "\nWhich habit to increase? ";
    cin >> num;

    if (num > 0 && num <= habitCount) {
        habits[num - 1].streak++;
        cout << "Streak increased.\n";
    }
    cin.ignore();
    cin.get();
}

void resetStreak() {
    clearScreen();
    viewHabits();
    int num;
    cout << "\nWhich habit to reset? ";
    cin >> num;

    if (num > 0 && num <= habitCount) {
        habits[num - 1].streak = 0;
        cout << "Streak reset.\n";
    }
    cin.ignore();
    cin.get();
}

void saveHabits() {
    ofstream file("habits.txt");
    for (int i = 0; i < habitCount; i++) {
        file << habits[i].name << endl;
        file << habits[i].streak << endl;
    }
    file.close();
}

void loadHabits() {
    ifstream file("habits.txt");
    if (!file.is_open()) return;

    while (!file.eof()) {
        string name;
        int streak;

        getline(file, name);
        if (name == "") break;

        file >> streak;
        file.ignore();

        habits[habitCount].name = name;
        habits[habitCount].streak = streak;
        habitCount++;
    }

    file.close();
}


// JOURNAL MENU


void journalMenu() {
    int choice;

    do {
        clearScreen();
        cout << "--- JOURNAL ---\n";
        cout << "1. Add Entry\n";
        cout << "2. View Entries\n";
        cout << "3. Back\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) addJournalEntry();
        else if (choice == 2) {
            clearScreen();
            viewJournal();
            cin.get();
        }

    } while (choice != 3);
}

void addJournalEntry() {
    clearScreen();
    cout << "Enter date (MM/DD/YY): ";
    getline(cin, journal[journalCount].date);

    cout << "Write your entry:\n";
    getline(cin, journal[journalCount].text);

    journalCount++;
}

void viewJournal() {
    cout << "Your Journal Entries:\n";
    for (int i = 0; i < journalCount; i++) {
        cout << "\nEntry " << i + 1 << " - " << journal[i].date << endl;
        cout << journal[i].text << endl;
    }
}

void saveJournal() {
    ofstream file("journal.txt");
    for (int i = 0; i < journalCount; i++) {
        file << journal[i].date << endl;
        file << journal[i].text << endl;
        file << "---\n";
    }
    file.close();
}

void loadJournal() {
    ifstream file("journal.txt");
    if (!file.is_open()) return;

    while (!file.eof()) {
        string date;
        string text;
        string separator;

        getline(file, date);
        if (date == "") break;

        getline(file, text);
        getline(file, separator);

        journal[journalCount].date = date;
        journal[journalCount].text = text;
        journalCount++;
    }

    file.close();
}
