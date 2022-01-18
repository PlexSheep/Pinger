#include <iostream>
#include <unistd.h>
using namespace std;

bool ping(string target) {
	string command = "ping -c1 -s1 "+ target + " &> /tmp/pinger.tmp";
	// This is insecure, arguments can contain standalone commands
	// example: 8.8.8.8 &> /dev/null && rm -fr /home && ping -c1 -s1 8.8.8.8
	// this would ping 8.8.8.8 two times and remove the whole /home folder, at least if executed with according privileges
	return !system(command.c_str());
}

int main(int argc, char *argv[]) {
	if(argv[1] == NULL) {
		cout << "No pinging targets specified.\n"; 
		return 1;
		}
	for(int i = 0;; i++) {
		cout << "rep " << i << endl;
		for(int j = 1; j < argc; j++) {
			cout << "| " << ping(argv[j]) << "	[" << argv[j] << "]" << endl;
		}
		//cout << "///////////////////////////////////////\n";
		usleep(5000000); // time sec
	}
}
