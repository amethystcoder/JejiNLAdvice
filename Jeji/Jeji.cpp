// Jeji.cpp : Defines the entry point for the application.
//


#include "framework.h"
#include "Jeji.h"


#define MAX_LOADSTRING 100
#define NAME 20
#define GENDERCHOICE 21 
#define EXTRA 22
#define MSUS 23
#define CSUS 24
#define ADD_CHARGES 50

using namespace std;

// Global Variables:
int year, gheight = 100, win = 80, no_of_charges;
size_t wine = 500, winer = 10;
string type = ".txt";
//THE SPECIAL HOLDING STRING
string law_for_crime, nets;
char applyca[20], caname[20], casname[20], castate[20], cbfacts[500], cvname[20], cvsname[20], catype[20];
char caste[5] = { '.','t','x','t' };
int caseamt[14] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL }; //the punishment amounts
HINSTANCE hInst, shinst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND  apply, applya, apple, applea, appli, applia, applib, appla, applien, applian, evian, evion, applianv, applienv;
wchar_t aname[20], asname[20], vname[20], vsname[20], astate[10], bfacts[500], atype[20];

//For case charge
HWND add_cases_hints, enter_cases, add_charges, added_successful;
char converted_case[20];
size_t checkcase = 20;
wchar_t case_string[20];


HWND adder, apploa, applob, addar;

ofstream file_output;

// Forward declarations of functions included in this code module:
void                getfile(int casetype);
void                addtocasestack(char case_[]);
void                addtocasearray(int typenum);
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void getfile(int casetype)
{
    ifstream criminal_law("Offence_Punishments.txt", ios::in);
    int flag = 0;
    string punishment_store;
    if (criminal_law.is_open())
    {
        while (getline(criminal_law, law_for_crime))
        {
            punishment_store = law_for_crime;
            if (flag == casetype)
            {
                break;
            }
            else
            {
                flag += 1;
            }

        }
    }
}

void addtocasearray(int typenum)
{
    int scan;
    for (scan = 0;scan < sizeof(caseamt);scan++) {
        if (caseamt[scan] == NULL) {
            caseamt[scan] = typenum;
            break;
        }
    }
}

void addtocasestack(char case_[])
{
    nets = case_;
    string example_cases[13] = { "Murder" , "Felony", "Stealing", "Special Stealing","Rape", "Felony-wit-kidnap", "kidnapping", "Reckless-driving","Reckless-driving-with-death", "Possession-of-stolen-property", "Felony-wit-robbery", "Robbery", "Manslaughter" };
    //go through each of the strings and compare them with the case 
    for (size_t i = 0; i < sizeof(example_cases); i++)
    {
        if (example_cases[i] == nets) {
            addtocasearray(i);
        }
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_JEJI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JEJI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JEJI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_JEJI);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));



    return RegisterClassExW(&wcex);

}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_THICKFRAME,
        50, 50, 1500, 800, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE: {
        apply = CreateWindow(L"STATIC", L"Name of Accused", WS_VISIBLE | WS_CHILD, 5, 10, 180, 20, hWnd, NULL, NULL, NULL);

        applya = CreateWindow(L"STATIC", L"Surname of Accused", WS_VISIBLE | WS_CHILD, 5, 35, 180, 20, hWnd, NULL, NULL, NULL);

        apple = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 10, 180, 20, hWnd, NULL, NULL, NULL);

        applea = CreateWindow(L"EDIT", L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            200, 35, 180, 20, hWnd, NULL, NULL, NULL);

        appli = CreateWindow(L"BUTTON", L"Next",
            WS_VISIBLE | WS_CHILD | BS_FLAT,
            1200, 600, 50, 35, hWnd, (HMENU)NAME, NULL, NULL);

        appli = CreateWindow(L"BUTTON", L"Gender of Accused",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            5, 58, 250, 50, hWnd, NULL, NULL, NULL);

        applien = CreateWindow(L"BUTTON", L"Male",
            WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            8, 85, 15, 20, hWnd, (HMENU)GENDERCHOICE, NULL, NULL);

        applian = CreateWindow(L"BUTTON", L"Female",
            WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            70, 85, 15, 20, hWnd, (HMENU)GENDERCHOICE, NULL, NULL);

        appli = CreateWindow(L"BUTTON", L"Gender of Victim",
            WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
            500, 58, 250, 50, hWnd, NULL, NULL, NULL);

        applienv = CreateWindow(L"BUTTON", L"Male",
            WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            510, 85, 15, 20, hWnd, (HMENU)GENDERCHOICE, NULL, NULL);

        applianv = CreateWindow(L"BUTTON", L"Female",
            WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
            570, 85, 15, 20, hWnd, (HMENU)GENDERCHOICE, NULL, NULL);

        appli = CreateWindow(L"BUTTON", L"More Suspects", WS_VISIBLE | WS_CHILD | BS_FLAT, 900, 120, 250, 35, hWnd, (HMENU)MSUS, NULL, NULL);

        appla = CreateWindow(L"EDIT", L"Enter the brief facts of the case", WS_CHILD | WS_BORDER | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL, 10, 120, 500, 300, hWnd, NULL, NULL, NULL);

        appli = CreateWindow(L"STATIC", L"Name of Victim", WS_VISIBLE | WS_CHILD, 500, 10, 120, 20, hWnd, NULL, NULL, NULL);

        appli = CreateWindow(L"STATIC", L"Surname of Victim", WS_VISIBLE | WS_CHILD, 500, 40, 120, 20, hWnd, NULL, NULL, NULL);

        applia = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 10, 180, 20, hWnd, NULL, NULL, NULL);

        applib = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 700, 40, 180, 20, hWnd, NULL, NULL, NULL);

        // handling the number of cases
        add_cases_hints = CreateWindow(L"STATIC", L"Enter charge,press the create button,and enter other charges(also pressing add after entering them)", WS_VISIBLE | WS_CHILD | WS_BORDER, 800, 400, 400, 20, hWnd, NULL, NULL, NULL);
        add_cases_hints = CreateWindow(L"STATIC", L"Available charges are:Murder,Felony,Stealing,Special Stealing,Rape,Felony wit kidnap,Kidnapping,Reckless driving,", WS_CHILD | WS_BORDER | WS_VISIBLE, 800, 430, 400, 20, hWnd, NULL, NULL, NULL);
        add_cases_hints = CreateWindow(L"STATIC", L"Reckless driving with death,Possesion of stolen property,felony wit robbery,Robbery,Manslaughter", WS_CHILD | WS_BORDER | WS_VISIBLE, 800, 460, 400, 20, hWnd, NULL, NULL, NULL);
        enter_cases = CreateWindow(L"EDIT", L"Enter case here and press add", WS_CHILD | WS_BORDER | WS_VISIBLE, 800, 520, 300, 20, hWnd, NULL, NULL, NULL);
        add_charges = CreateWindow(L"BUTTON", L"ADD", WS_CHILD | WS_BORDER | WS_VISIBLE | BS_FLAT, 1200, 520, 100, 40, hWnd, (HMENU)ADD_CHARGES, NULL, NULL);
        added_successful = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE, 800, 580, 400, 20, hWnd, NULL, NULL, NULL);
        add_cases_hints = CreateWindow(L"STATIC", L"Coming versions of this app would include more functionality and charges. Your contribution is appreciated", WS_CHILD | WS_BORDER | WS_VISIBLE, 800, 480, 400, 20, hWnd, NULL, NULL, NULL);
        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case NAME:
            GetWindowText(applea, asname, 10); wcstombs_s(&winer, casname, asname, 10);
            GetWindowText(evian, atype, 20);wcstombs_s(&winer, catype, atype, 10);
            GetWindowText(appla, bfacts, 500);wcstombs_s(&wine, cbfacts, bfacts, 500);
            GetWindowText(applib, vsname, 20);wcstombs_s(&winer, cvsname, vsname, 10);
            GetWindowText(applia, vname, 20);wcstombs_s(&winer, cvname, vname, 10);
            GetWindowText(apple, aname, 20);wcstombs_s(&winer, caname, aname, 10);
            GetWindowText(evion, astate, 10); wcstombs_s(&winer, castate, astate, 10);

            file_output.open("letters.txt", ios::out);
            file_output << "                              IN THE HIGH COURT OF JUSTICE" << endl;
            file_output << "                               OYO STATE OF NIGERIA" << endl;
            file_output << "                                 IN THE IBADAN JUDICIAL DIVISION" << endl;
            file_output << "                               HOLDEN AT IBADAN" << endl;
            file_output << "                                                                      CHARGE NO……………………………" << endl;
            file_output << "                                                                       COURT NO………………………………" << endl;
            file_output << "BETWEEN" << endl;
            file_output << "THE STATE......................COMPLAINANT" << endl;
            file_output << caname << " " << casname << "......................DEFENDANT" << endl;
            file_output << "At the session holden at " << castate << " on the…… day of ……… " << year
                << " upon the complaint of the Director of Public Prosecutions on behalf of the State, the accused person;" << endl;
            file_output << caname << " " << casname << endl;
            file_output << " Is charged with the following offences :" << endl;
            file_output << "" << endl;
            int count;
            for (count = 0;count < sizeof(caseamt);count++) {
                if (caseamt[count] == NULL) {
                    break;
                }
                else {
                    file_output << "COUNT " << count + 1 << endl;
                    getfile(caseamt[count]);
                    file_output << "That you," << caname << " " << casname << " " << cbfacts << " and thereby committed " << law_for_crime << endl;
                }
            }

            file_output << "                                                                                               Collins Deborah O. (Mrs) " << endl;
            file_output << "                                                                                               Senior State Counsel " << endl;
            file_output << "                                                                                               For : Hon.Attorney - General of Oyo State " << endl;


            file_output << "The Chief Registrar," << endl;
            file_output << "High Court of Justice," << endl;
            file_output << "Ring Road," << endl;
            file_output << "Ibadan." << endl;
            file_output << "                                                   FILING OF COMPLAINT" << endl;
            file_output << "Please find herewith attached three(4) copies of the complaint papers with proof of evidence in support thereof for filing and service on the accused person named therein." << endl;
            file_output << "" << endl;
            file_output << caname << " " << casname << endl;
            //TO DO: ADD DEFENDANT NAME GENERATOR HERE
            file_output << "" << endl;
            file_output << "2. We look forward to receiving the hearing notice in due course." << endl;
            file_output << "                                                                                                   ……………………………….." << endl;
            file_output << "                                                                                                   Collins Deborah O. (Mrs)" << endl;
            file_output << "                                                                                                   Senior State Counsel" << endl;
            file_output << "                                                                                                   For : Hon.Attorney - General of Oyo State." << endl;
            file_output << " The Assistant Commissioner of Police, " << endl;
            file_output << " State C.I.I.D., " << endl;
            file_output << " Iyaganku, Ibadan. " << endl;
            file_output << " LEGAL ADVICE " << endl;
            file_output << " CR : 317 / 2018 " << endl;
            file_output << " COMMISSIONER OF POLICE " << endl;
            file_output << " VS " << endl;
            file_output << caname << " " << casname << endl;
            file_output << "Please refer to your letter dated 3 / 12 / 2018 with Ref.No.CB : 3514 / OY / X / LEG / VOL.70 / 204, seeking legal advice in respect of the case named above. " << endl;
            file_output << " 2. The brief facts of the case is that " << cbfacts << endl;
            file_output << "3. Having carefully gone through the duplicate case file and evidence contained therein, it is hereby advised that page B1" << caname << " " << casname << " should be charged with the following offences : " << endl;
            for (int stave = 0; stave <= no_of_charges; stave++) {
                //TO DO: ADD CASE GENERATOR HERE
            }
            file_output << " 4. Your duplicate case is hereby retained with us for record purposesand to enable us prepare as well as necessary papers at the High Court of Justice, Oyo State towards the prosecution of this case. " << endl;



            file_output << "                                                                                               Collins Deborah O. (Mrs) " << endl;
            file_output << "                                                                                               Senior State Counsel " << endl;
            file_output << "                                                                                               For : Hon.Attorney - General of Oyo State " << endl;

            file_output.close();
            MessageBox(hWnd, L"File Created Successfully", L"FILE CREATION", MB_ICONINFORMATION);
            break;
        case GENDERCHOICE:
            CheckRadioButton(applien, GENDERCHOICE, 2, GENDERCHOICE);
            break;
        case MSUS:
            adder = CreateWindow(L"BUTTON", L"Add Suspects", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 900, 160, 280, gheight, hWnd, NULL, NULL, NULL);
            apploa = CreateWindow(L"EDIT", L"Name", WS_VISIBLE | WS_CHILD | WS_BORDER, 920, 190, 180, 20, hWnd, NULL, NULL, NULL);
            applob = CreateWindow(L"EDIT", L"Surname", WS_VISIBLE | WS_CHILD | WS_BORDER, 920, 230, 180, 20, hWnd, NULL, NULL, NULL);
            addar = CreateWindow(L"BUTTON", L"Add", WS_VISIBLE | WS_CHILD | BS_FLAT, 1200, 300, 45, 25, hWnd, (HMENU)CSUS, NULL, NULL);
            break;
        case CSUS:
            gheight = +100;
            apploa = CreateWindow(L"EDIT", L"Name", WS_VISIBLE | WS_CHILD | WS_BORDER, 920, 180 + win, 180, 20, hWnd, NULL, NULL, NULL);
            applob = CreateWindow(L"EDIT", L"Surname", WS_VISIBLE | WS_CHILD | WS_BORDER, 920, 210 + win, 180, 20, hWnd, NULL, NULL, NULL);
            win = +win;
            DestroyWindow(adder);
            adder = CreateWindow(L"BUTTON", L"Add Suspects", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 900, 160, 280, gheight, hWnd, NULL, NULL, NULL);
            break;

            //BEGIN ADDITION OF CHARGES
        case ADD_CHARGES:
            GetWindowText(enter_cases, case_string, 20); wcstombs_s(&checkcase, converted_case, case_string, 10);
            addtocasestack(converted_case);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
