#include <iostream>
#include <unistd.h>
using namespace std;

const int DEFAULT_TIME = 5000; // 5 sec
const int TARGET_ARR_SIZE = 16;

int timeMultiplier = DEFAULT_TIME;
int targetsSet = 0;
bool usedArg;
string target[TARGET_ARR_SIZE];

bool ping(string target) {
  string command = "ping -c1 -s1 " + target + " &> /tmp/pinger.tmp";
  // This is insecure, arguments can contain standalone commands
  // example: 8.8.8.8 &> /dev/null && rm -fr /home && ping -c1 -s1 8.8.8.8
  // this would ping 8.8.8.8 two times and remove the whole /home folder, at
  // least if executed with according privileges
  return !system(command.c_str());
}

void help() {
  cout << "Usage: pinger TARGET1 TARGET2...\n"
       << "Keep the user informed, if a target is connected.\n\n"

       << "Options:\n\n"

       << "	-h, --help	display this help and exit\n"
       << "	-d, --delay	set a custom delay to wait between pings,\n"
       << "			default is 5 sec,set the delay in "
          "milliseconds.\n"
       << "			THIS IS STILL EXPERIMENTAL\n"

       << "\n"; // documentation link, license, manpage notice
}

int main(int argc, char *argv[]) {

  // compute args

  // no additional args
  if (argc == 1) {
    cerr << "No target specified! At least one is needed.\nUse \"-h\" or "
            "\"--help\" for further information on how to use this tool.\n";
    return 1;
  }

  for (int i = 1; i < argc; i++) {

	  if(usedArg) {
		  usedArg = false;
		  continue;
	  }

    if (string(argv[i]) == "-h") {
      help();
      return 0;
    }

    else if (string(argv[i]) == "--help") {
      help();
      return 0;
    }

    else if (string(argv[i]) == "-d" || string(argv[i]) == "--delay") {
      if (i + 1 < argc) { // check if a following arg exists
        timeMultiplier = stoi(string(argv[i + 1]));
		usedArg = true;
		continue;
      }
    }

    else {
      if (targetsSet < 14)
        target[targetsSet++] = string(argv[i]);
      else {
      cerr << "too many target! Max is 16.\n";
	  return 1;
	  }
	  continue;
    }
  }

  for (int i = 0;; i++) {
    cout << "rep " << i << endl;
    for (int j = 0; j < targetsSet; j++) {
      cout << "| " << ping(target[j]) << "	[" << target[j] << "]" << endl;
    }
    // cout << "///////////////////////////////////////\n";
    usleep(timeMultiplier * 1000); // default 5 sec
  }
}
