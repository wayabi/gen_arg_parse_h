#!/bin/sh

gen_arg_parse_h \
	dir_input,string,man \
	dir_input2,string,man \
	add_or_subtract,int,1 \
	dir_output,string,man \
	log_level,string,debug \
	> ./src/arg_parse.h
