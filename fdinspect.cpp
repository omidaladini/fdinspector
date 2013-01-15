#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

int report_buffer_size(int fd);

int main(int argc, char* argv[]) {

  int PID = 0;

  if(argc != 2) {
    cout << "Usage: fdinspect PID" << endl; return 1;
  } else PID = atoi(argv[1]);

  stringstream ss_in, ss_out;

  ss_in << "/proc/" << PID << "/fd/0"; 
  ss_out << "/proc/" << PID << "/fd/1"; 

  int fd_in = open(ss_in.str().c_str(), O_RDONLY);
  int fd_out = open(ss_out.str().c_str(), O_RDONLY);

  const string tab = "\t";

  cout << "PID" << tab << "stdin" 
	        << tab << "stdout" 
	        << endl;

  cout << PID << tab << report_buffer_size(fd_in) 
              << tab << report_buffer_size(fd_out) 
              << endl;
}

int report_buffer_size(int fd) {
  int bytes = -1;
  ioctl(fd, FIONREAD, &bytes);
  return bytes;
}

