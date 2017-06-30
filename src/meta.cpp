
// don't care about using libraries in this; it's just to build the meta-program

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4505)
#pragma warning(disable : 4456)

#include "basic_types.h"

#include <4cpp/4cpp_lexer.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

struct _token {
	_token(Cpp_Token t, char* data) : str(data + t.start, t.size) {
		token = t;
	}
	Cpp_Token token;
	string str;

};
set<string>    files;
vector<_token> all_tokens;
vector<_token> lib_includes;
string path;
ofstream fout;

void load(string file) {

	ifstream fin(file, ios::binary | ios::ate);
	streamsize fsize = fin.tellg();
	fin.seekg(0, ios::beg);

	if(!fin.good()) {
		printf("failed to open file %s\n", file.c_str());
		return;
	}

	vector<char> data((u32)fsize);
	fin.read(data.data(), fsize);

	Cpp_Token_Array tokens = cpp_make_token_array(2048);
	cpp_lex_file(data.data(), (u32)fsize, &tokens);

	for(i32 i = 0; i < tokens.count; i++) {
		Cpp_Token token = tokens.tokens[i];

		if(token.type == CPP_PP_INCLUDE_FILE) {
			char* place = data.data() + token.start;
			string incl(place, token.size);
			if(incl[0] == '\"') {

				all_tokens.pop_back();
				incl = path + incl.substr(1, incl.size() - 2);
				
				if(files.find(incl) == files.end()) {
					files.insert(incl);
					load(incl);
				}

			} else {
				lib_includes.push_back(all_tokens.back());
				all_tokens.pop_back();
				lib_includes.push_back(_token(token, data.data()));
			}
		} else if(token.type == CPP_PP_DEFINE) {

			char* place = data.data() + token.start + token.size;
			_token t(token, data.data());
			do {
				token = tokens.tokens[++i];
			} while((token.flags & CPP_TFLAG_PP_BODY) == CPP_TFLAG_PP_BODY);
			i--;
			u32 size = 0;
			for(char* cursor = place; (*cursor != '\r' && *cursor != '\n') || *cursor == '\\'; cursor++, size++) {
				if(*cursor == '\\') {
					cursor += 3;
					size += 3;
				}
			}
			stringstream ss;
			ss << string(place, size);
			while(ss.good()) {
				string parse;
				ss >> parse;
				if(parse.size() && parse != "\\") {
					t.str = t.str + " " + parse;
				}
			}

			all_tokens.push_back(t);
		} else if(token.type == CPP_TOKEN_COMMENT) {

			_token t(token, data.data());
			t.str = t.str.substr(0, t.str.size() - 1);
			all_tokens.push_back(t);

		} else {

			all_tokens.push_back(_token(token, data.data()));
		}
   	}

   	cpp_free_token_array(tokens);
}

i32 main(i32 argc, char** argv) {
    if (argc < 2){
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fout.open("w:/src/meta_out.h");

    if(!fout.good()) {
    	printf("failed to create file meta_out.h\n");
    	return 1;
    }

    string first(argv[1]); 
    path = first.substr(0, first.find_last_of("\\/") + 1);
    load(first);

    for(i32 i = 0; i < lib_includes.size(); i += 2) {
    	printf("%s %s\n", lib_includes[i].str.c_str(), lib_includes[i+1].str.c_str());
    }

    for(i32 i = 0; i < all_tokens.size(); i++) {
    	_token& t = all_tokens[i];

    	if(t.str == "struct") {
    		
    	}
    }

    fout << endl;
    fout.close();

    return 0;
}

/*

Actual RTTI generated at compile time
The code at the bottom is what I'd like to do; it's basically the same as implemented 
	in JAI and Odin.
However, we can't exactly do this outside of the compiler, so this will have to be limited to 
	struct introspection (i.e. can't combinatorially generate all pointer type information).
I think we can do most of it; just start with basic_types.h info, then struct/enum/union
	introspection and build the table up from there.

enum _type_types : u8 {
	Type_unkown,

	Type_int,
	Type_float,
	Type_bool,
	Type_ptr,
	Type_array,
	Type_func,		// function pointer
	Type_struct,
	Type_enum,

	// do we want these?
	Type_string,
	Type_vec,
	Type_map,
};

struct Type_int_info {

};
struct Type_float_info {

};
struct Type_bool_info {
	
};
struct Type_ptr_info {

};
struct Type_array_info {

};
struct Type_func_info {

};
struct Type_struct_info {

};
struct Type_union_info {

};
struct Type_enum_info {

};
struct Type_string_info {

};

struct _type_info {
	_type_types type_type 	= Type_unkown;
	union {
		Type_int_info 		_int;
		Type_float_info 	_float;
		Type_bool_info 		_bool;
		Type_ptr_info 		_ptr;
		Type_array_info 	_array;
		Type_func_info 		_func;
		Type_struct_info	_struct;
		Type_union_info 	_union;
		Type_string_info 	_string;
		Type_enum_info		_enum;
	};
};

const map<u32,_type_info> type_table = make_map<;
const int NUM_TYPES = <num_structs> + 10;

// we can ignore typedefs; they are simply aliases and typeid() will be the same
_type_info g_type_info[NUM_TYPES] = {
	{
		
	}	
};

*/
