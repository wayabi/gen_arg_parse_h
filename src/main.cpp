#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>

#include "Util.h"

using namespace std;

struct arg_param {
public:
	std::string name_;
	std::string type_;
	bool mandatory_;
	std::string default_value_;
};

void write_0(ostream& o)
{
	o << "#ifndef __U_ARG_PARSE__" << endl;
	o << "#define __U_ARG_PARSE__" << endl;
	o << endl;
	o << "#include <string>" << endl;
	o << "#include <ostream>" << endl;
	o << endl;
	o << "#include <boost/program_options.hpp>" << endl;
	o << endl;
	o << "class arg_parse {" << endl;
	o << endl;
	o << "public:" << endl;
}

void write_1(ostream& o)
{
	o << "public:" << endl;
	o << "\tstd::string parse(int argc, char** argv)" << endl;
	o << "\t{" << endl;
	o << "\t\tusing namespace boost::program_options;" << endl;
	o << "\t\toptions_description opt(\"opt\");" << endl;
	o << "\t\topt.add_options()" << endl;
}

void write_2(ostream& o)
{
	o << "\t\t;" << endl;
	o << "\t\tvariables_map vm;" << endl;
	o << "\t\ttry{" << endl;
	o << "\t\t\tstore(parse_command_line(argc, argv, opt), vm);" << endl;
	o << "\t\t\tnotify(vm);" << endl;
}

void write_3(ostream& o)
{
	o << "\t\t}catch(std::exception& e){" << endl;
	o << "\t\t\treturn std::string(e.what());" << endl;
	o << "\t\t}" << endl;
	o << "\t\treturn std::string("");" << endl;
	o << "\t}" << endl;
}

void write_4(ostream& o)
{
	o << endl;
	o << "\tvoid print(std::ostream& o)" << endl;
	o << "\t{" << endl;
}
	
void write_5(ostream& o)
{
	o << "\t}" << endl;
	o << "};" << endl;
	o << "#endif" << endl;
}
//arg0,int,man
//arg1,string,default
//arg2,double,0.3
int main(int argc, char** argv)
{
	ostream& o = cout;
	write_0(o);

	vector<arg_param> params;

	for(int i=1;i<argc;++i){
		auto ss = Util::split(string(*(argv+i)), ',');
		if(ss.size() < 2) continue;
		string name = ss[0];
		string type = ss[1];
		string default_value = "";
		if(ss.size() >= 3){
			default_value = ss[2];
		}
		if(name.size() == 0) continue;
		arg_param p;
		p.name_ = name;
		if(type == "string" || type == "s"){
			p.type_ = "std::string";
		}else if(type == "int" || type == "i"){
			p.type_ = "int";
		}else if(type == "double" || type == "d"){
			p.type_ = "double";
		}
		if(p.type_.size() == 0) continue;
		if(default_value == "man"){
			p.mandatory_ = true;
		}else{
			p.mandatory_ = false;
			if(p.type_ == "std::string"){
				p.default_value_ = string("\"") + default_value + string("\"");
			}else{
				p.default_value_ = default_value;
			}
		}
		params.push_back(p);
	}

	for(auto ite = params.begin();ite != params.end();++ite){
		o << "\t" << ite->type_ << " " << ite->name_ << ";" << endl;
	}
	write_1(o);
	for(auto ite = params.begin();ite != params.end();++ite){
		o << "\t\t\t(\"" << ite->name_ << "\", value<" << ite->type_ << ">()->";
		if(ite->mandatory_){
			o << "required(), \"" << ite->name_ << "\")" << endl;
		}else{
			o << "default_value(" << ite->default_value_ << "), \"" << ite->name_ << "\")" << endl;
		}
	}
	write_2(o);
	for(auto ite = params.begin();ite != params.end();++ite){
		o << "\t\t\t" << ite->name_ << " = vm[\"" << ite->name_ << "\"].as<" << ite->type_ << ">();" << endl;
	}
	write_3(o);
	write_4(o);
	for(auto ite = params.begin();ite != params.end();++ite){
		o << "\t\to << \"" << ite->name_ << "[" << ite->type_ << "]: \" << " << ite->name_ << " << std::endl;" << endl;
	}
	write_5(o);
	return 0;
}
