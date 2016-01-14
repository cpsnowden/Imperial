



class TableLamp {
	enum {ON, OFF} state;
public:
	TableLamp() { state = ON; } void pressSwitch () {
	state = ( state == ON ? OFF : ON );
// dim(); illegal!
// brightness = 0.4; illegal!
}
	friend ostream& operator <<(ostream& o, const TableLamp& t) {
		return o << (t.state == TableLamp::ON ? " is on" : " is off" );
	}
};

class AdjTableLamp : public TableLamp { 
	float brightness;
public:
	AdjTableLamp() { brightness = 1.0; }
	void dim() {
		if (brightness > 0.1) brightness -= 0.1;
	}
	void print(ostream& o) const {
		o << *this << " with brightness " << brightness << endl;
	} 
};

int main() {

AdjTableLamp myLamp;
cout << "myLamp"; myLamp.print(cout);
// OUT: myLamp is on with brightness 1.0
myLamp.dim();
cout << "myLamp"; myLamp.print(cout);
// OUT: myLamp is on with brightness 0.9
myLamp.pressSwitch();
cout << "myLamp" << myLamp;
// OUT: myLamp is off
TableLamp yourLamp;

AdjTableLamp* hisLamp = new AdjTableLamp(); cout << "hisLamp"; hisLamp ->print(cout);
// OUT: hisLamp is on with brightness 1.0
hisLamp ->dim();
cout << "hisLamp"; hisLamp ->print(cout);
// OUT: hisLamp is on with brightness 0.9
hisLamp->pressSwitch();
cout << "hisLamp" << *hisLamp;
// OUT: hisLamp is off
TableLamp* herLamp = new TableLamp();

}

AdjTableLamp* hisLamp = new AdjTableLamp();
TableLamp* herLamp = hisLamp; // OK
// hisLamp = herLamp;
AdjTableLamp myLamp;
TableLamp theirLamp;
herLamp = &myLamp
// hisLamp = &theirLamp;
illegal!
/* If we allowed the illegal assignments above what would happen if we then did:
hisLamp ->dim()
hisLamp ->print(cout) */
// OK illegal!

AdjTableLamp myLamp; TableLamp yourLamp;
myLamp.pressSwitch();
cout << "myLamp "; myLamp.print(cout);
// OUT: myLamp is off with brightness 1.0
cout << "yourLamp" << yourLamp; // OUT: yourLamp is on
yourLamp = myLamp;
cout << "yourLamp" << yourLamp;
// OUT: yourLamp is off
myLamp.pressSwitch();
cout << "myLamp" << myLamp;
// OUT: myLamp is on
cout << "yourLamp" << yourLamp;
// OUT: yourLamp is off

AdjTableLamp* hisLamp = new AdjTableLamp(); TableLamp* herLamp;
herLamp = hisLamp;
cout << "herLamp" << *herLamp; // OUT: herLamp is on
cout << "hisLamp"; hisLamp ->print(cout);
// OUT: hisLamp is on with brightness 1.0
hisLamp->pressSwitch();
  
cout << "hisLamp"; hisLamp ->print(cout);
 // OUT: hisLamp  is off with brightness 1.0
 cout << "herLamp" << *herLamp; 
 // OUT: herLamp is off

delete hisLamp; // what’s wrong with this? very bad!
// delete herLamp


AdjTableLamp myLamp; TableLamp yourLamp;
AdjTableLamp& myLampRef = myLamp;
TableLamp& yourLampRef = yourLamp;
myLampRef.pressSwitch()
cout << "myLampRef"; myLampRef.print(cout);
// OUT: myLampRef is off with brightness 1.0
cout << "yourLampRef" << yourLampRef; // OUT: yourLampRef is on
yourLampRef = myLampRef;
cout << "yourLampRef" << yourLampRef;
// OUT: yourLampRef is off
myLampRef.pressSwitch();
cout << "myLampRef"; myLampRef.print(cout);
// OUT: is on with brightness 1.0
cout << "yourLampRef" << yourLampRef;
// OUT: yourLampRef is off

 AdjTableLamp myLamp, myOtherLamp;
AdjTableLamp& myLampRef = myLamp;
 TableLamp& myOtherLampRef = myOtherLamp;
myLampRef.dim(); myLampRef.pressSwitch(); 
cout << "myLampRef"; myLampRef.print(cout);
// OUT: myLampRef is off with brightness 0.9
cout << "myOtherLampRef" << myOtherLampRef; // OUT: myOtherLampRef is on
myOtherLampRef = myLampRef;
cout << "myOtherLampRef" << myOtherLampRef; // OUT: myOtherLampRef is off
cout << "myOtherLamp"; myOtherLamp.print(cout); // OUT: myOtherLamp is off with brightness 1.0


// But don’t forget references are aliases
AdjTableLamp myLamp;
AdjTableLamp& myLampRef = myLamp; TableLamp& yourLampRef = myLamp;
cout << "myLampRef"; myLampRef.print(cout); // OUT: myLampRef is on with brightness 1.0
yourLampRef.pressSwitch();
cout << "yourLampRef" << yourLampRef;
// OUT: yourLampRef is off
cout << "myLampRef"; myLampRef.print(cout);
// OUT: myLampRef is off with brightness 1.0



class TableLamp { ...
friend ostream& operator <<(ostream& o, TableLamp& t) {
// If TableLamp& t not const
... }
};
class AdjTableLamp { ...
void print(ostream& o) const {
o << *this ...
// compile error: no match for operator<<
} };

