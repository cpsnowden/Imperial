#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Date {
private:
  int year;
  int month;
  int day;
  int hour;
  int minute;
public:
  Date(int yr, int mn, int dy, int hr, int min) :
    year(yr),
    month(mn),
    day(dy),
    hour(hr),
    minute(min) {};
  friend ostream& operator<<(ostream& os, const Date& dt);
};

ostream& operator<<(ostream& os, const Date& dt) {
  os << dt.day << "/" << dt.month << "/" << dt.year << " "
     << dt.hour << "h" << dt.minute;
  return os;
}

class Fine {
protected:
  int offenceCode;
  string registration;
  Date date;
public:
  Fine(int oC, string reg, Date dt) :
    offenceCode(oC),
    registration(reg),
    date(dt) {}
  virtual double amount() = 0;
  friend ostream& operator<<(ostream& os,  Fine* fn);
  virtual ~Fine() {};
};

ostream& operator<<(ostream& os, Fine* fn) {
  os << " [" << fn->offenceCode << "," << fn->registration
     << "," << fn->date << ","  << fn->amount() << "]";
  return os;
}

class FixedPen : public Fine {
public:
  static double am;
  FixedPen(int oC, string reg, Date dt) : Fine(oC, reg, dt) {}
  double amount() { return am;}
  ~FixedPen(){};
};

class ExcessPen : public Fine {
private:
  int overStay;
  static double varAmmount;
  static double am;
public:
  ExcessPen(int oC, string reg, Date dt, int oS) :
    Fine(oC, reg, dt), overStay(oS) {}
  double amount() {
    double vam = am + varAmmount * overStay;
    if(vam < FixedPen::am)
      return vam;
    return FixedPen::am;
  };
  ~ExcessPen(){};
};

class ParkingAttendant {
private:
  int badgeN;
  string name;
  
  vector<Fine*> fines;
  double valFines() {
    double val = 0.0;
    vector<Fine*>::iterator it;
    for(it=fines.begin(); it!=fines.end(); it++) {
      val += (*(*it)).amount();
    }
    return val;
  }
  
protected:
  virtual double percentBonus() const = 0;
  virtual double baseSalary() const = 0;
  
public:
  ParkingAttendant(int bN, string nm) :
    badgeN(bN), name(nm)
  {
    cout << "[" << name << "," << bN << "]";
  };
  bool issueFine(Fine* fine) {
    cout << badgeN << " issueing fine" <<  fine << endl;
    fines.push_back(fine);
    return true;
  }
  double salary() {
    return baseSalary() + percentBonus()*valFines();
  };

  ~ParkingAttendant() {
    vector<Fine*>::iterator it;
    for(it=fines.begin(); it!=fines.end(); it++) {
      delete(*it);
    }
  }
};

class JuniorAttendant : public ParkingAttendant {
protected:
  double percentBonus() const { return 5.0;}
  double baseSalary() const { return 900.0;}  
public:
  JuniorAttendant(int bN, string nm) :
    ParkingAttendant(bN, nm) {
    cout << " - junior Attendant " << endl;
  }
};

class SeniorAttendant : public ParkingAttendant {
protected:
  double percentBonus() const { return 10.0;}
  double baseSalary() const { return 1200.0;}  
public:
  SeniorAttendant(int bN, string nm) :
    ParkingAttendant(bN, nm) {
    cout << " - senior Attendant " << endl;
  } 
};

class Council {
private:
  string name;
  vector<ParkingAttendant*> attendants;
public:
  Council(string nm) : name(nm) {}
  void addAttendant(ParkingAttendant* pa) {
    attendants.push_back(pa); }
  void setFixedPen(double fn) {
    FixedPen::am = fn;
    cout << "Fixed Penalty set to " << FixedPen::am << endl;
  };
};

double FixedPen::am = 100.0;
double ExcessPen::am = 20.0;
double ExcessPen::varAmmount = 5.0;

int main() {

  Council stc("Sleepy Town Council");

  SeniorAttendant charon(666, "Charon");
  stc.addAttendant(&charon);
  JuniorAttendant nelson(111, "Nelson");
  stc.addAttendant(&nelson);
  
  Date dt1(2006,2,16,9,50);
  charon.issueFine(new FixedPen(26,"LO52RNA",dt1));

  stc.setFixedPen(120.0);

  Date dt2(2006,2,17,10,15);
  nelson.issueFine(new ExcessPen(4,"B14NCA",dt2,15));

  cout << "Nelson's salary is £" << nelson.salary() << endl;

  return 0;
}




  



