
string make_stringf(string fmt, ...) {

	va_list args;
	va_start(args, fmt);

	string ret = make_vstringf(fmt, args);

	va_end(args);

	return ret;
}

#include <cstdio>
#pragma warning(push)
#pragma warning(disable : 4996)
string make_vstringf(string fmt, va_list args) {

	i32 len = _vscprintf(fmt.c_str, args) + 1;

	string ret = make_string(len);
	ret.len = len;

	vsnprintf(ret.c_str, ret.len, fmt.c_str, args);

	return ret;
}
#pragma warning(pop)

string string_literal(const char* literal) {

	return string_from_c_str((char*)literal);
}

string string_from_c_str(char* c_str) {

	string ret;

	u32 len;
	for(len = 0; c_str[len] != '\0'; len++);
	len++;

	ret.c_str = c_str;
	ret.len = len;
	ret.cap = len;

	return ret;
}

string make_string_from_c_str(char* c_str) {

	u32 len;
	for(len = 0; c_str[len] != '\0'; len++);
	len++;

	string ret = make_string(len);
	ret.len = len;

	for(u32 i = 0; i <= len; i++) { // will copy null terminator
		ret.c_str[i] = c_str[i];
	}

	return ret;
}

void free_string(string s) {

	_free(s.c_str);

	s.c_str = NULL;
	s.cap = 0;
	s.len = 0;
}

string make_string(u32 cap) {

	string ret;

	ret.c_str = (char*)_malloc(cap);
	ret.cap = cap;

	return ret;
}

string make_copy_string(string src) {

	string ret = make_string(src.cap);

	ret.len = src.len;

	for(u32 i = 0; i < ret.len; i++) { // will copy null terminator
		ret.c_str[i] = src.c_str[i];
	}

	return ret;
}

// end inclusive
string make_substring(string str, u32 start, u32 end) {

	string ret = make_string(end - start + 1);

	ret.len = end - start + 1;

	for(u32 i = 0, s_i = start; s_i <= end; i++, s_i++) {
		ret.c_str[i] = str.c_str[s_i];
	}

	return ret;
}

string make_cat_strings(i32 num_strs, ...) {

	va_list args;
	va_start(args, num_strs);

	array<string> params = make_array<string>(num_strs);

	for(i32 i = 0; i < num_strs; i++) {

		*array_get(&params, i) = va_arg(args, string);
	}

	va_end(args);

	u32 len = 0;

	for(i32 i = 0; i < num_strs; i++) {

		len += array_get(&params, i)->len - 1;
	}

	string ret = make_string(len + 1);
	ret.len = len + 1;
	u32 place = 0;

	for(i32 i = 0; i < num_strs; i++) {

		for(u32 j = 0; j < array_get(&params, i)->len - 1; j++) {
			
			ret.c_str[place] = array_get(&params, i)->c_str[j];
			place++;
		}
	}

	ret.c_str[place] = '\0';

	destroy_array(&params);

	return ret;
}

string make_cat_string(string first, string second) {

	string ret = make_string(first.len + second.len - 1);

	ret.len = first.len + second.len - 1;

	u32 c_i = 0;

	for(u32 i = 0; i < first.len - 1; i++, c_i++) {
		ret.c_str[c_i] = first.c_str[i];
	}

	for(u32 i = 0; i < second.len; i++, c_i++) {
		ret.c_str[c_i] = second.c_str[i];
	}

	return ret;
}
