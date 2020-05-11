#ifndef __U_ARG_PARSE__
#define __U_ARG_PARSE__

#include <string>
#include <ostream>

#include <boost/program_options.hpp>

class arg_parse {

public:
	std::string log_level_;
	int log_file_;
	int arg0;
	std::string arg1;
	double arg2;
public:
	std::string parse(int argc, char** argv)
	{
		using namespace boost::program_options;
		options_description opt("opt");
		opt.add_options()
			("log_level", value<std::string>()->default_value("debug"), "log level")
			("log_file", value<int>()->default_value(0), "flag output log to file")
			("arg0", value<int>()->required(), "arg0")
			("arg1", value<std::string>()->default_value("path"), "arg1")
			("arg2", value<double>()->default_value(3.3333), "arg2")
		;
		variables_map vm;
		try{
			store(parse_command_line(argc, argv, opt), vm);
			notify(vm);
			log_level_ = vm["log_level"].as<std::string>();
			log_file_ = vm["log_file"].as<int>();
			arg0 = vm["arg0"].as<int>();
			arg1 = vm["arg1"].as<std::string>();
			arg2 = vm["arg2"].as<double>();
		}catch(std::exception& e){
			return std::string(e.what());
		}
		return std::string();
	}

	void print(std::ostream& o)
	{
		o << "arg0[int]: " << arg0 << std::endl;
		o << "arg1[std::string]: " << arg1 << std::endl;
		o << "arg2[double]: " << arg2 << std::endl;
	}
};
#endif
