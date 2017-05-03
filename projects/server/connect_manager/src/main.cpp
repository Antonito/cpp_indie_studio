#include "connect_manager_stdafx.hpp"

int main()
{
	std::cout << "Starting server" << std::endl;

	// Connection to License Manager
	// Accept Game Server's connection

	// Accept Client's connection

	std::cout << "Server stopped" << std::endl;
#if defined(_WIN32) && !defined(__on__linux__)
	system("pause");
#endif
  return (0);
}
