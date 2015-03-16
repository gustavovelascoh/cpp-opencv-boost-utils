/*
 * option_parser.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: Gustavo Velasco-Hernandez
 */

//#include <boost/system/api_config.hpp>
#include <boost/program_options.hpp>
//#include <boost/program_options/options_description.hpp>

using namespace std;
namespace po = boost::program_options;

//po::option_description set_desc();
void set_desc(po::options_description & desc);


int main(int ac, char* av[])
{
	//po::options_description desc = set_desc();

	po::options_description desc("Allowed options");

	set_desc(desc);

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
	    cout << desc << "\n";
	    return 1;
	}

	if (vm.count("compression")) {
	    cout << "Compression level was set to "
	 << vm["compression"].as<int>() << ".\n";
	} else {
	    cout << "Compression level was not set.\n";
	}

}

void set_desc(po::options_description & desc)
{

//	po::options_description desc("Allowed options");

	desc.add_options()
    ("help", "produce help message")
    ("compression", po::value<int>(), "set compression level")
	;

    //return desc;
}


