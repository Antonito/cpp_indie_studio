#include "connect_manager_stdafx.hpp"

int main(int ac, char **av)
{
  std::cout << "Starting server" << std::endl;

  if (ac != 2)
    {
      std::cout << "Usage: " << *av << " port" << std::endl;
      return (1);
    }
  // Connection to License Manager
  try
    {
      LicenseServer mainSrv(
          static_cast<std::uint16_t>(std::strtol(*(av + 1), nullptr, 10)));

      mainSrv.run();
      mainSrv.stop();
    }
  catch (std::exception const &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }

  // Accept Game Server's connection

  // Accept Client's connection

  std::cout << "Server stopped" << std::endl;
#if defined(_WIN32) && !defined(__on__linux__)
  system("pause");
#endif
  return (0);
}
