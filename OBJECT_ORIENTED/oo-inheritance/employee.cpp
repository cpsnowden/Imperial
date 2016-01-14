class Employee {
protected: char* name; float salary;
public:
Employee(float s, char* n) {
salary = s;
name = n; }
friend ostream& operator << (ostream& o, const Employee& e) {
return o << e.name << " earns " << e.salary; }
};


class Manager : public Employee { private:
int level;
public:
Manager(int l, char* n) : Employee(10000.0 * l, n) {
level = l; }
ostream& operator >>(ostream& o) const { return o << *this << " at level " << level;
} };

int main() {
Manager Scrooge(5, "Scrooge MacDuck");
Employee Donald(13456.5, "Donald Duck"); cout << Donald << endl;
// OUT: Donald Duck earns 13456.5
cout << Scrooge << endl;
// OUT: Scrooge MacDuck earns 50000.0
Scrooge >> cout << endl;
// OUT: Scrooge MacDuck earns 50000.0 at level 5
return 0; }

class WrongManager : public Employee { private:
int level; public:
WrongManager(int l, char* n) { level = l; name = n;
salary = 10000.0 * l;
}
// Error: no matching function call to
’Employee::Employee()’
};

class Desk { public:
Desk() { cout << "Desk::Desk() \n"; }
~Desk() { cout << "Desk::~Desk() \n"; } };
class Office { public:
Office() { cout << "Office::Office() \n"; }
~Office() { cout << "Office::~Office() \n"; } };
class PC { public:
PC() { cout << "PC::PC() \n"; } ~PC() { cout << "PC::~PC() \n"; }
void turnOn() { cout << "turns PC on \n"; }
void turnOff() { cout << "turns PC off \n"; } };

class Empl {
Desk myDesk; Office* myOffice;
public: Empl(Office* o) {
myOffice = o;
cout << "Empl::Empl() \n"; }
~Empl() { cout << "Empl::~Empl() \n"; } };
class Boss : public Empl { PC myPC;
public:
Boss(Office* o) : Empl(o) {
myPC.turnOn(); cout << "Boss::Boss() \n"; }
~Boss() {
myPC.turnOff(); cout << "Boss::~Boss() \n";
} };



int main() {
Office* pOff = new Office();
// OUT: Office::Office()
Boss* pBoss = new Boss(pOff);
/* OUT: Desk::Desk() Empl :: Empl ()
PC::PC()
turns PC on Boss :: Boss () */
delete pBoss;
/* OUT: turns PC off Boss ::~ Boss ()
PC::~PC()
Empl ::~ Empl () Desk ::~ Desk () */

Empl *pEmpl = new Empl(pOff); /* OUT: Desk::Desk()
Empl :: Empl () */
delete pEmpl;
/* OUT: Empl::~Empl()
Desk ::~ Desk () */

class Employee {
protected: char* name; float salary;
public:
Employee(float s, char* n) { salary = s; name = n;}
friend ostream& operator <<(ostream& o, const Employee& e) {
return o << e.name << " earns " << e.salary; }
virtual void paycut(float amount) { salary -= amount;
} };

class Manager : public Employee { private:
int level;
public:
Manager(int l, char* n) : Employee(10000.0 * l, n){
level = l; }
friend ostream& operator << (ostream& o, const Manager& m) {
return o << (Employee) m << " at level " << m.level;
}
virtual void paycut(float amount) { salary += amount * level;
} };

int main () {
Manager Scrooge(5, "SMD"); Employee Donald(13456.5, "DD");
cout << Donald << endl;
// OUT: DD earns 13456.5
Donald.paycut(300); cout << Donald << endl;
// OUT: DD earns 13156.5
cout << Scrooge << endl;
// OUT: SMD earns 50000.0 at level 5
Scrooge.paycut(300); cout << Scrooge << endl;
// OUT: SMD earns 51500.0 at level 5
Scrooge.Employee::paycut(300); cout << Scrooge << endl;
// OUT: SMD earns 51200.0 at level 5
return 0; }


int main() {
Manager* M1 = new Manager(5, "ScrMcDuck"); Employee* E1 = new Employee(13456.5, "DonDuck"); Employee* E2 = new SuperManager("WaltDisn");
cout << "E1: " << *E1 << endl;
// OUT: E1: DonDuck earns 13456.5
E1->paycut(300);
cout << "E1: " << *E1 << endl;
// OUT: E1: DonDuck earns 13156.5
E1->payrise();
cout << "E1: " << *E1 << endl;
// OUT: E1: DonDuck earns 13956.5
C++ - Object Oriented Paradigm
cout << "M1: " << *M1 << endl;
// OUT: M1: ScrMcDuck earns 50000
M1->paycut(300);
cout << "M1: " << *M1 << endl;
// OUT: M1: ScrMcDuck earns 51500
M1->payrise();
cout << "M1: " << *M1 << endl;
// OUT: M1: ScrMcDuck earns 51600
cout << "E2: " << *E2 << endl;
// OUT: E2: WaltDisn earns 100000
E2->paycut(300);
cout << "E2: " << *E2 << endl;
// OUT: E2: WaltDisn earns 200000
E2->payrise();
cout << "E2: " << *E2 << endl;
// OUT: E2: WaltDisn earns 200800
at level 5
at level 5
at level 5
  C++ - Object Oriented Paradigm
 
E2 = E1;
cout << "E2: " << *E2 << endl;
// OUT: E2: DonDuck earns 13956.5
E2->paycut(300);
cout << "E2: " << *E2 << endl;
// OUT: E2: DonDuck earns 13656.5
E2->payrise();
cout << "E2: " << *E2 << endl;
// OUT: E2: DonDuck earns 14456.5
  C++ - Object Oriented Paradigm
 
Static Binding for Objects
 Employee Donald(30000.0, "Donald Duck"); SuperManager Walter("Walter Disney");
cout << "Donald: " << Donald << endl;
// OUT: Donald: Donald Duck earns 30000
Donald.paycut(300);
cout << "Donald: " << Donald << endl;
// OUT: Donald: Donald Duck earns 29700
Donald.payrise();
cout << "Donald: " << Donald << endl;
// OUT: Donald: Donald Duck earns 30500
  C++ - Object Oriented Paradigm
 
Static Binding for Objects Cont.
<< "Walter: " << Walter << endl;
OUT: Walter: Walter Disney earns 100000 at
cout
Donald = Walter;
cout << "Donald: " << Donald << endl;
// OUT: Donald: Walter Disney earns 100000
Donald.paycut(300);
cout << "Donald: " << Donald << endl;
// OUT: Donald: Walter Disney earns 99700
Donald.payrise();
cout << "Donald: " << Donald << endl;
// OUT: Donald: Walter Disney earns 100500
level 10


// Object assignment (copying of fields)
return 0;
}
// OUT: Donald: Donald Duck earns 30000











