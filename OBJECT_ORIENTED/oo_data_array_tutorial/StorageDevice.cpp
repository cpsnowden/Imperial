	#include <vector>
#include <iostream>
using namespace std;

class StorageDevice {

private:
		int storageCapacity;
		int dTBandwidth;

public:
		StorageDevice(int _storageCapacity, int _dTBandwidth) :
							 storageCapacity(_storageCapacity),
							 dTBandwidth(_dTBandwidth) {};

		virtual double getLatency() const = 0;
		int getCapacity() const {
			return storageCapacity;
		}
		int getdTBandwidth() const {
			return dTBandwidth;
		}
		int getStorageCapacity() const {
			return storageCapacity;
		}
};

class HDD : public StorageDevice {

private:
		double avRotationTime;
		double avSeekTime;
public:
		HDD(int _storageCapacity, int _dTBandwidth, double _avRotationTime, double _avSeekTime) :
							 StorageDevice(_storageCapacity, _dTBandwidth),
							 avRotationTime(_avRotationTime),
							 avSeekTime(_avSeekTime) {};

		double getLatency() const {
			return avRotationTime + avSeekTime;
		}

};

class SSD : public StorageDevice {

private:
		double avAccessTime;
public:
		SSD(int _storageCapacity, int _dTBandwidth, double _avAccessTime) :
							 StorageDevice(_storageCapacity, _dTBandwidth),
							 avAccessTime(_avAccessTime) {};
		double getAvAccessTime() const {
			return avAccessTime;
		}

		double getLatency() const {
			return getAvAccessTime();
		}

};

class DataStorageArray {

protected:
		static const int devLim = 12;
		int devCount;
		vector<StorageDevice*> storagedevices;
public:
		DataStorageArray() {
			devCount = 0;
		}
		bool addStorageDevice(StorageDevice* storagedevice) {
			if (devCount >=devLim)
				return false;
			storagedevices.push_back(storagedevice);
			devCount++;
			return true;
		}

		bool addMultipleStorageDevice(StorageDevice* storagedevice, int n) {
			if (devCount + n >=devLim)
				return false;
			for (int i = 0; i<n; i++) {
				storagedevices.push_back(storagedevice);
				devCount++;	
			}
			return true;
		}		

		double getLatency() {
			if(storagedevices.size()==0)
				return -1;

			int maxLatency = 0;
			vector<StorageDevice*>::iterator it;
			for(it=storagedevices.begin(); it!=storagedevices.end() ;it++) {
				if((*it)->getLatency() > maxLatency)
					maxLatency = (*it)->getLatency();
			}
			return maxLatency;
		}
		virtual double getEffCapacity()  = 0;
		virtual double getEffBand()  = 0;
};

class Raid1 : public DataStorageArray{

public: 
		double getEffCapacity()  {

			int total = 0;
			vector<StorageDevice*>::iterator it;
			for(it=storagedevices.begin();it!=storagedevices.end(); ++it) {
					total += (*it)->getCapacity();
			}
			return static_cast<double>(total)/2;
		}
		double getEffBand() {

			int total = 0;
			vector<StorageDevice*>::iterator it;
			for(it=storagedevices.begin();it!=storagedevices.end(); ++it) {
					total += (*it)->getdTBandwidth();
			}
			return static_cast<double>(total)/2;
		}
}; 

class Raid5: public DataStorageArray{

public:
		double getEffCapacity()  {

			int total = 0;
			int size = storagedevices.size();
			vector<StorageDevice*>::iterator it;
			for(it=storagedevices.begin(); it!=storagedevices.end(); it++) {
					total += (*it)->getCapacity();
			}
			return static_cast<double>(total)*(size-1)/size;
		}
		double getEffBand()  {

			int total = 0;
			int size = storagedevices.size();

			vector<StorageDevice*>::iterator it;
			for(it=storagedevices.begin(); it!=storagedevices.end(); ++it) {
					total += (*it)->getdTBandwidth();
			}
			return static_cast<double>(total)*size/(size-1);
		}

};

int main() {

	HDD hdd(500, 100, 4, 8);
	Raid1 raid1;
	raid1.addMultipleStorageDevice(&hdd,4);


	SSD ssd(30, 300, 0.01);
	Raid5 raid5;
	raid5.addMultipleStorageDevice(&ssd,4);
	cout << raid1.getEffBand() << " " << raid1.getLatency() << endl;
	cout << raid5.getEffCapacity() << endl;

	return 0;
}
