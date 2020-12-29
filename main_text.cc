#include "straight.h"
#include "controller.h"
#include "text_view.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int main(int argc, char *argv[])
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	if (argc > 1)
	{
		try
		{
			seed = std::stoi(std::string{argv[1]});
		}
		catch (std::invalid_argument &e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
		catch (std::out_of_range &e)
		{
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	}	  // if

	Straight model{seed};
	Controller controller(&model);
	TextView view(&controller, &model);
} // main
