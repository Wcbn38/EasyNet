#pragma once

//error ranges from 0x100 to 0x200
#define PARSE_ERROR_OFFSET

//error codes
#define PARSE_NO_ERROR PARSE_ERROR_OFFSET + 0x00
#define PARSE_CORRUPTED_FORMAT PARSE_ERROR_OFFSET + 0x01
#define PARSE_FAILED_TO_BUILD PARSE_ERROR_OFFSET + 0x02
#define PARSE_NOT_FOUND PARSE_ERROR_OFFSET + 0x03

#define PARSE_UNKNWON_ERROR PARSE_ERROR_OFFSET + 0xFF

struct ERROR
{
	std::string msg;
	int code;
};

struct DELIM
{
	std::string tag;
	DELIM_MODE mode;
};