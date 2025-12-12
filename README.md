#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

const string FileClientName = "Client.text";

struct stClientRecord
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

struct stMoneyInfo 
{
    stClientRecord ClientRecord;
    double Deposit;
    double Withdraw;
    double totalBalance;
    double mainMenue;

};

vector<string> SplitString(string S1, string delim)
{
    vector<string> vResult;
    size_t pos = 0;
    string token;

    while ((pos = S1.find(delim)) != string::npos)
    {
        token = S1.substr(0, pos);
        if (!token.empty())
        {
            vResult.push_back(token);
        }
        S1.erase(0, pos + delim.length());
    }

    if (!S1.empty())
    {
        vResult.push_back(S1);
    }
    return vResult;
}

stClientRecord ConvertRecordToLine(string Line, string Seperator = "#//#")
{
    stClientRecord RecordLine;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    if (vClientData.size() >= 5)
    {
        RecordLine.AccountNumber = vClientData[0];
        RecordLine.PinCode = vClientData[1];
        RecordLine.Name = vClientData[2];
        RecordLine.Phone = vClientData[3];
        RecordLine.AccountBalance = stod(vClientData[4]);
    }
    return RecordLine;
}

string ConvertClientToLine(stClientRecord Client, string Seperator = "#//#")
{
    string DataLine = "";
    DataLine += Client.AccountNumber + Seperator;
    DataLine += Client.PinCode + Seperator;
    DataLine += Client.Name + Seperator;
    DataLine += Client.Phone + Seperator;
    DataLine += to_string(Client.AccountBalance);
    return DataLine;
}

vector<stClientRecord> LoadDataFromFile(string FileName)
{
    vector<stClientRecord> vClients;
    fstream Myfile;
    Myfile.open(FileName, ios::in);

    if (Myfile.is_open())
    {
        string line;
        stClientRecord client;
        while (getline(Myfile, line))
        {
            if (!line.empty())
            {
                client = ConvertRecordToLine(line);
                vClients.push_back(client);
            }
        }
        Myfile.close();
    }
    return vClients;
}

vector<string> LoadDataFromFileStrings(string FileName)
{
    vector<string> vLines;
    fstream Myfile;
    Myfile.open(FileName, ios::in);

    if (Myfile.is_open())
    {
        string line;
        while (getline(Myfile, line))
        {
            if (!line.empty())
            {
                vLines.push_back(line);
            }
        }
        Myfile.close();
    }
    return vLines;
}

void SaveClientToFile(stClientRecord Client, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        string DataLine = ConvertClientToLine(Client);
        MyFile << DataLine << endl;
        MyFile.close();
    }
}

bool FindClientByAccountNumber(string accountNum, stClientRecord& client)
{

    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);

    for (stClientRecord& C : vClients)
    {
        if (C.AccountNumber == accountNum)
        {
            client = C;
            return true;
        }
    }
    return false;
}

bool IsAccountNumberExist(string AccountNumber)
{

    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);

    for (stClientRecord& Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            return true;
        }
    }
    return false;
}

stClientRecord ReadNewClient()
{
    stClientRecord Client;

    do {
        cout << "Enter Account Number? ";
        getline(cin >> ws, Client.AccountNumber);

        if (IsAccountNumberExist(Client.AccountNumber))
        {
            cout << "Account Number already exists! Please enter a different one.\n";
        }
    } while (IsAccountNumberExist(Client.AccountNumber));

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    cin.ignore();

    return Client;
}

void SaveVectorToFile(const string& fileName,  vector<string>& vFileContent)

{
    fstream myfile;
    myfile.open(fileName, ios::out);
    if (myfile.is_open())
    {
        for (string& Line : vFileContent)
        {
            if (!Line.empty())
            {
                myfile << Line << endl;
            }
        }
        myfile.close();
    }
}

void DeleteClient(string fileName, string accountNumber)
{
    vector<string> vLines = LoadDataFromFileStrings(fileName);
    vector<string> vNewLines;

    for (string& line : vLines)
    {

        vector<string> vClientData = SplitString(line, "#//#");
        if (vClientData.size() >= 5 && vClientData[0] != accountNumber)
        {
            vNewLines.push_back(line);
        }
    }
    SaveVectorToFile(fileName, vNewLines);
    cout << "\nClient with Account Number (" << accountNumber << ") deleted successfully!\n";
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter Account Number? ";
    cin >> AccountNumber;
    cin.ignore();
    return AccountNumber;
}

bool UpdateRecordInFile(string fileName, string Record, string UpdateTo)
{
    vector<string> vFileContent = LoadDataFromFileStrings(fileName);
    bool updated = false;

    for (string& Line : vFileContent)
    {
        if (Line == Record)
        {
            Line = UpdateTo;
            updated = true;
            break;
        }
    }

    SaveVectorToFile(fileName, vFileContent);
    return updated;
}

void PrintClientCard(stClientRecord Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "----------------------------------------------" << endl;
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

void PrintPattern()
{
    cout << "____________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(10) << "Pin Code"
        << "| " << left << setw(25) << "Client Name"
        << "| " << left << setw(15) << "Phone"
        << "| " << left << setw(10) << "Balance" << endl;
    cout << "____________________________________________________________________________________\n";
}

void PrintBalancePatter()
{
    cout << "____________________________________________________________________________________\n\n";

    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(25) << "Client Name"
        << "| " << left << setw(10) << "Balance" << endl;

    cout << "____________________________________________________________________________________\n";
}

void PrintClientRecords(vector<stClientRecord>& vClients)
{
    cout << "\n\t\tClient List (" << vClients.size() << ") Client(s).\n";
    PrintPattern();

    for (stClientRecord& client : vClients)
    {
        cout << "| " << left << setw(15) << client.AccountNumber
            << "| " << left << setw(10) << client.PinCode
            << "| " << left << setw(25) << client.Name
            << "| " << left << setw(15) << client.Phone
            << "| " << left << setw(10) << client.AccountBalance << endl;
    }
    cout << "____________________________________________________________________________________\n";
}

void AddNewClient()
{
    stClientRecord Client = ReadNewClient();
    SaveClientToFile(Client, FileClientName);
}

void ShowClientScreen()
{
    cout << "__________________________________________________________________\n";
    cout << "\n\tAdding New Client:" << endl;
    cout << "__________________________________________________________________\n"<<endl;
}
void AddClients()
{
    char AddMore = 'Y';
    do {
        system("cls");
        ShowClientScreen();
        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
        cin.ignore();
    } while (toupper(AddMore) == 'Y');
}

void ShowAllClients()
{
    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);
    PrintClientRecords(vClients);
}

void DeleteClientByAccount()
{
    string AccountNumber = ReadClientAccountNumber();
    if (IsAccountNumberExist(AccountNumber))
    {
        DeleteClient(FileClientName, AccountNumber);
       
    }
    else
        cout << "\nClient not found!\n";
}

void UpdateClientByAccount()
{
    string AccountNumber = ReadClientAccountNumber();
    stClientRecord OldClient;
    if (FindClientByAccountNumber(AccountNumber, OldClient))
    {
        cout << "\nCurrent client data:\n";
        PrintClientCard(OldClient);

        cout << "\nEnter the new client information:\n";
        stClientRecord NewClient = ReadNewClient();

        string OldRecord = ConvertClientToLine(OldClient);
        string NewRecord = ConvertClientToLine(NewClient);
        UpdateRecordInFile(FileClientName, OldRecord, NewRecord);
        cout << "\nClient updated successfully!\n";
        
    }
    else
        cout << "\nClient not found!\n";
}

void FindClientByAccount()
{
    string AccountNumber = ReadClientAccountNumber();
    stClientRecord Client;
    if (FindClientByAccountNumber(AccountNumber, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient not found!\n";
}

double DepositeTransactions()
{
    stClientRecord  client;
    double DepositAmount;
    char AddMore = 'Y';
    double totalDeposit = 0;

   cout << "Enter your deposit amount: ";
   cin >> DepositAmount;
    totalDeposit += DepositAmount;
   client.AccountBalance += totalDeposit;  

    return totalDeposit;
}

double WithdrawTransactions()
{
    stClientRecord  client;
    double WithdrawAmount;
    char AddMore = 'Y';
    double totalWithdrwa = 0;

    do {
        cout << "Enter your deposit amount: ";
        cin >> WithdrawAmount;
        totalWithdrwa += WithdrawAmount;
        cout << "\nAre you sure you want to perform this transaction? Y/N? ";
        cin >> AddMore;
        cin.ignore();
    } while (toupper(AddMore) != 'Y');

    client.AccountBalance -= totalWithdrwa;

    return totalWithdrwa;
}

void TransactionScreen()
{
    cout << "===========================================" << endl;
    cout << "\n\t Transaction Screen\n" << endl;
    cout << "===========================================" << endl;
    cout << "\n\t[1] Deposit." << endl;
    cout << "\t[2] Withdraw." << endl;
    cout << "\t[3] Total Balance." << endl;
    cout << "\t[4] Exit.\n" << endl;
    cout << "===========================================" << endl;


}

void Deposit()
{
    system("cls");
    cout << "__________________________________________________________________\n";
    cout << "\n\t\t\tDeposit Screen" << endl;
    cout << "__________________________________________________________________\n";
    string AccouNum = ReadClientAccountNumber();
    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);

    if (!IsAccountNumberExist(AccouNum))
    {
        cout << "Account not found.\n";
        return;
    }

    double amount = DepositeTransactions();
    if (amount <= 0)
    {
        cout << "Invalid deposit amount.\n";
        return;
    }

    char Choice;
    cout << "Are you sure you want to deposit " << amount << "? (Y/N): ";
    cin >> Choice;

    if (toupper(Choice) == 'Y')
    {
        for (stClientRecord& client : vClients)
        {
            if (client.AccountNumber == AccouNum)
            {
                client.AccountBalance += amount;
                cout << "Deposit successful! " << endl;
                cout<<"The total balance is : "<<client.AccountBalance << endl;
                system("pause>0");
                break;
            }
        }

    }
    else
    {
        cout << "Deposit cancelled.\n";
    }
}

void WithDraw()
{
    system("cls");
    cout << "__________________________________________________________________\n";
    cout << "\n\t\t\tWithdraw Screen" << endl;
    cout << "__________________________________________________________________\n";
    string AccouNum = ReadClientAccountNumber();
    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);

    if (!IsAccountNumberExist(AccouNum))
    {
        cout << "Account not found.\n";
        return;
    }

    double amount = WithdrawTransactions();
    if (amount <= 0)
    {
        cout << "Invalid withdraw amount.\n";
        return;
    }

    char Choice;
    cout << "Are you sure you want to withdraw " << amount << "? (Y/N): ";
    cin >> Choice;

    if (toupper(Choice) == 'Y')
    {
        for (stClientRecord& client : vClients)
        {
            if (client.AccountNumber == AccouNum)
            {
                client.AccountBalance -= amount;
                SaveClientToFile(client, FileClientName);
                cout << "withdraw successful! " << endl;
                cout << "The total balance is : " << client.AccountBalance << endl;
                system("pause>0");
            }
        }
    }
    else
    {
        cout << "withdraw cancelled.\n";
    }
}

double CalculateTotalBalances(const vector<stClientRecord>& vClients)
{

    double total = 0.0;

    for (const auto& client : vClients)
        total += client.AccountBalance;
    
    return total;
}

void BalanceList()
{
    vector<stClientRecord> vClients = LoadDataFromFile(FileClientName);

    double totalBalance = CalculateTotalBalances(vClients);
    cout << "\n\t\tBalances List (" << vClients.size() << ") Client(s).\n";
    PrintBalancePatter();
    for (stClientRecord& client : vClients)
    {
        cout << "| " << left << setw(15) << client.AccountNumber
            << "| "<< left << setw(25) << client.Name
            << "| " <<left << setw(10) << client.AccountBalance << endl;
    }
    cout << "____________________________________________________________________________________\n";
   
    cout << "\n\t\t\t\tTotal balance =" << totalBalance << endl;
}

void Transaction()
{
    int choice = 0;

    do
    {
        system("cls");
        TransactionScreen();
        cout << "\nChoose an option [1-4]: ";
        cin >> choice;
    switch (choice)
    {
    case 1:
    {
        Deposit();
        break;
    }
    case 2:
    {
        WithDraw();
        break;
    }
    case 3:
    {
        BalanceList();
        cout << "\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        break;
    }

    case 4:
    {
        cout << "\nExiting program...\n";
        break;
    }
    default:
    {
        cout << "\nInvalid choice, please try again.\n";
        break;
    }
    }
    }while (choice != 4);
}

void PrintMainMenuScreen()
{
    cout << "===========================================" << endl;
    cout << "\n\t Main Menue Screen\n" << endl;
    cout << "===========================================" << endl;
    cout << "\n\t[1] Show Client." << endl;
    cout << "\t[2] Add New Client." << endl;
    cout << "\t[3] Delete Client." << endl;
    cout << "\t[4] Update Client Info." << endl;
    cout << "\t[5] Find Client." << endl;
    cout << "\t[6] Transactions." << endl;
    cout << "\t[7] Exit.\n" << endl;
    cout << "===========================================" << endl;
}

void BankSystemMainMenu()
{
    int choice = 0;

    do
    {
        system("cls");
        PrintMainMenuScreen();

        cout << "\nChoose an option [1-7]: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            ShowAllClients();
            break;
        }
        case 2:
        {
            AddClients();
            break;
        }
        case 3:
        {
            DeleteClientByAccount();
            break;
        }
        case 4:
        {
            UpdateClientByAccount();
            break;
        }
        case 5:
        {
            FindClientByAccount();
            break;
        }
        case 6:
        {
            Transaction();
            break;
        }
        case 7:
        {
            cout << "\nExiting program...\n";
            break;
        }
        default:
        
            cout << "\nInvalid choice, please try again.\n";
            break;
        }

        if (choice != 7)
        {
            cout << "\nPress any key to return to the main menu...";
            system("pause>0");
        }

    } while (choice != 7);
}


int main()
{
    BankSystemMainMenu();
    system("pause>0");
    return 0;
}
