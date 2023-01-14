#include "test.hpp"

// https://github.com/divinepet/ft_containers-unit-test

void print_element(std::string t)
{
	if (t == "OK")
	    t = GREEN + t + RESET;
	else if (t == "FAILED")
		t = RED + t + RESET;
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}

void print_header(std::string container)
{
	print_element(YELLOW + container + RESET);
	std::cout << RESET << std::endl;

	print_element("TEST NAME");
	print_element(WHITE + "RESULT" + RESET);
	print_element(WHITE + "STD TIME");
	print_element(WHITE + "FT TIME");
	print_element("LEAKS");
	std::cout << RESET << std::endl;
}

bool isTimeout(int std_time, int ft_time)
{
	if (ft_time < 0)
		return (std_time < 0 ? true : false);
	return (std_time * 20 < ft_time);
}

std::string exec(const char* cmd)
{
	char buffer[128];
	std::string result = "";
	FILE* pipe = popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch (...) { pclose(pipe); throw; }
	pclose(pipe);
	return result;
}

std::string get_leak_string(std::string s)
{
	std::string tmp;
	int idx = s.find("total leaked bytes");
	for (; s[idx] != '\n' ; --idx) {}
	int edx = idx + 1;
	for (; s[edx] != '\n' ; ++edx) {}

	return s.substr(++idx, edx - 101);
}


int leaks_test(pid_t pid)
{
	std::string a = "leaks ";
	a += std::to_string(static_cast<int>(pid));
	usleep(50);
	std::string s = get_leak_string(exec(a.c_str()));

	if (s.find("0 leaks for 0 total leaked bytes") != std::string::npos) {
		print_element(GREEN + "CLEAR" + RESET);
		return (0);
	}
	else {
	    print_element(RED + "LEAKS" + RESET);
	    return (1);
	}
}