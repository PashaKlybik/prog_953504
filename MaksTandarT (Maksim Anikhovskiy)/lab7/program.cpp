#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
 
 
struct Project
{
    vector<pair<string, double> > notMandatoryServices;
    vector<pair<string, double> > mandatoryServices;
 
    class Program
    {
        public:
        string name;
        string date;
        int seats;
        double price;
        vector<pair<string, double> > mandatoryService;
        vector<pair<string, double> >notMandatoryService;
    };
 
    vector<Program> programs;
    vector< pair<string, Program> > users;
 
    void addProgram()
    {
        Program program;
        cout << "Name: ";
        cin >> program.name;
        cout << "Date: ";
        cin >> program.date;
        cout << "Seats: ";
        cin >> program.seats;
        cout << "Price: ";
        cin >> program.price;
        programs.push_back(program);
 
    }
    void printProgram(Program program)
    {
        cout << program.name << "\n";
        cout << program.date << "\n";
        cout << program.seats << "\n";
        cout << program.price << "\n";
        cout << "MandatoryServices:\n";
        for(auto x : program.mandatoryService)
            cout << x.first << " " << x.second << "$\n";
        cout << "NotMandatoryServices:\n";    
        for(auto x : program.notMandatoryService)
            cout << x.first << " " << x.second << "$\n";
        cout << "----------------------------------\n";
    }
 
    void printPrograms()
    {
        for(auto x : programs)
            printProgram(x);
    }
};
 
 
void UserMenu(Project &project)
{
    cout << "Username: ";
    string username;
    cin >> username;
    int index = -1;
    for(int i = 0; i < project.users.size(); i++)
    {
        if(project.users[i].first == username)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
    {
        bool isCorrect = false;
        while(!isCorrect)
        {
            project.printPrograms();
            cout << "Choose program(name): ";
            string s;
            cin >> s;
            for(int i = 0; i < project.programs.size(); i++)
            {
                if(project.programs[i].name == s)
                {
                    isCorrect = true;
                    project.programs[i].seats--;
                    project.users.push_back({username, project.programs[i]});
                    if(!project.programs[i].seats)
                    {
                        project.programs.erase(project.programs.begin() + i);
                    }
                    index = project.users.size() - 1;
                    break;
                }
            }
 
        }
 
    }
    while(true)
    {
        system("cls");
        cout << "1.Print my program\n2.Add not mandatory\n3.Back\n";
        int n;
        cin >> n;
        if(n == 1)
            project.printProgram(project.users[index].second);
        else if(n == 2)
        {
            for(int i = 0; i < project.notMandatoryServices.size(); i++)
                cout << i << " " << project.notMandatoryServices[i].first << " " << project.notMandatoryServices[i].second << "$\n";
            int choose;
            cout << "Choose mandatory(number): ";
            cin >> choose;
            project.users[index].second.notMandatoryService.push_back(project.notMandatoryServices[choose]);
            project.users[index].second.price += project.notMandatoryServices[choose].second;
        }
        else if(n == 3)
            return;
        getch();
    }
 
}
 
int main()
{
    Project project;
    //loadFromFile(project);
    while(true)
    {
        system("cls");
        cout << "1.I'm a user\n2.Add programm\n3.Add mandatory\n4.Add not mandatory\n5.Total price\n6.Add mandatory to program\n7.Print all\n8.Exit\n";
        int n;
        cin >> n;
        if(n == 1)
        {
            UserMenu(project);
        }
        else if(n == 2)
        {
            project.addProgram();
        }
        else if(n == 3)
        {
            system("cls");
            string service;
            double price;
            cout << "Service: ";
            cin >> service;
            cout << "Price: ";
            cin >> price;
            project.mandatoryServices.push_back({service, price});
        }
        else if(n == 4)
        {
            system("cls");
            string service;
            double price;
            cout << "Service: ";
            cin >> service;
            cout << "Price: ";
            cin >> price;
            project.notMandatoryServices.push_back({service, price});
        }
        else if(n == 5)
        {
            double price = 0;
            for(auto x : project.users)
                price += x.second.price;
            cout << "Total price: " << price << "\n";
        }
        else if(n == 6)
        {
            project.printPrograms();
            cout << "Choose program(name): ";
            string s;
            cin >> s;
            for(int i = 0; i < project.programs.size(); i++)
            {
                if(project.programs[i].name == s)
                {
                    for(int i = 0; i < project.mandatoryServices.size(); i++)
                        cout << i << " " << project.mandatoryServices[i].first << " " << project.notMandatoryServices[i].second << "$\n";
                    int choose;
                    cout << "Choose mandatory(number): ";
                    cin >> choose;
                    fflush(stdin);
                    project.programs[i].mandatoryService.push_back(project.mandatoryServices[choose]);
                    project.programs[i].price += project.mandatoryServices[choose].second;
                    break;
                }
            }
 
        }
        else if(n == 7)
        {
            project.printPrograms();
        }
        else if(n == 8)
        {
            return 0;
        }
        getch();
    }
 
}