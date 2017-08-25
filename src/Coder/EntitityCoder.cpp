/*
 * EntitityCoder.cpp
 *
 *  Created on: Aug 24, 2017
 *      Author: user
 */

#include "EntitityCoder.h"

namespace networkingLab {

EntitityCoder::EntitityCoder()
{
	initDecodeMap();
	initEncodeMap();
}

EntitityCoder::~EntitityCoder() {

}

vector<Entity*> EntitityCoder::encode(vector<Entity*> decoded)
{
	vector<Entity*>::iterator it = decoded.begin();
	while(it != decoded.end())
	{
		encodeEntity(*it);
		it++;
	}
	return decoded;
}

vector<Entity*> EntitityCoder::decode(vector<Entity*> encoded)
{
	vector<Entity*>::iterator it = encoded.begin();
	while(it != encoded.end())
	{
		decodeEntity(*it);
		it++;
	}
	return encoded;
}

Entity* EntitityCoder::encodeEntity(Entity* decoded)
{
	vector<string> decoded_params = decoded->getParams();
	vector<string> encoded_params;
	// name stays the same
	encoded_params.push_back(decoded_params[0]);
	// password hashing
	encoded_params.push_back(encodeStr(decoded_params[1]));
	decoded->setParams(encoded_params);
	return decoded;
}

string EntitityCoder::encodeStr(string decoded)
{
	string encoded_str="";
	for(size_t i=0;i<decoded.length();++i)
	{
		char letter= decoded[i];
		encoded_str+=map_encode[letter];
	}
	return encoded_str;
}

Entity* EntitityCoder::decodeEntity(Entity* encoded)
{
	vector<string> encoded_params = encoded->getParams();
	vector<string> decoded_params;
	// name stays the same
	decoded_params.push_back(encoded_params[0]);
	// password hashing
	decoded_params.push_back(decodeStr(encoded_params[1]));
	encoded->setParams(decoded_params);
	return encoded;
}

string EntitityCoder::decodeStr(string encoded)
{
	string decoded_str="";
	for(size_t i=0;i<encoded.length();++i)
	{
		char letter= encoded[i];
		decoded_str+=map_decode[letter];
	}
	return decoded_str;
}

void EntitityCoder::initEncodeMap()
{
	map_encode['a'] = '1';
	map_encode['b'] = 'a';
	map_encode['c'] = 'z';
	map_encode['d'] = '2';
	map_encode['e'] = 'w';
	map_encode['f'] = 's';
	map_encode['g'] = 'x';
	map_encode['h'] = '3';
	map_encode['i'] = 'e';
	map_encode['j'] = 'd';
	map_encode['k'] = 'c';
	map_encode['l'] = '4';
	map_encode['m'] = 'r';
	map_encode['n'] = 'f';
	map_encode['o'] = 'v';
	map_encode['p'] = '5';
	map_encode['q'] = 't';
	map_encode['r'] = 'g';
	map_encode['s'] = 'b';
	map_encode['t'] = '6';
	map_encode['u'] = 'y';
	map_encode['v'] = 'h';
	map_encode['w'] = 'n';
	map_encode['x'] = '7';
	map_encode['y'] = 'u';
	map_encode['z'] = 'j';
	map_encode['0'] = 'm';
	map_encode['1'] = '8';
	map_encode['2'] = 'i';
	map_encode['3'] = 'k';
	map_encode['4'] = ',';
	map_encode['5'] = '0';
	map_encode['6'] = 'p';
	map_encode['7'] = ';';
	map_encode['8'] = '.';
	map_encode['9'] = '_';
	map_encode['-'] = '!';
	map_encode['_'] = '@';
	map_encode['!'] = '#';
	map_encode['@'] = '$';
	map_encode['#'] = '%';
	map_encode['$'] = '^';
	map_encode['%'] = '&';
	map_encode['^'] = '*';
	map_encode['&'] = '(';
	map_encode['*'] = ')';
	map_encode['('] = '-';
	map_encode[')'] = '~';
	map_encode['~'] = '|';
	map_encode['A'] = 'Q';
	map_encode['B'] = 'A';
	map_encode['C'] = 'Z';
	map_encode['D'] = 'W';
	map_encode['E'] = 'S';
	map_encode['F'] = 'X';
	map_encode['G'] = 'R';
	map_encode['H'] = 'F';
	map_encode['I'] = 'V';
	map_encode['J'] = 'T';
	map_encode['K'] = 'G';
	map_encode['L'] = 'B';
	map_encode['M'] = 'Y';
	map_encode['N'] = 'H';
	map_encode['O'] = 'N';
	map_encode['P'] = 'U';
	map_encode['Q'] = 'J';
	map_encode['R'] = 'E';
	map_encode['S'] = 'I';
	map_encode['T'] = 'K';
	map_encode['U'] = 'M';
	map_encode['V'] = 'O';
	map_encode['W'] = 'L';
	map_encode['X'] = 'P';
	map_encode['Y'] = 'C';
	map_encode['Z'] = 'D';
}

void EntitityCoder::initDecodeMap()
{
	map_decode['A'] = 'B';
	map_decode['B'] = 'L';
	map_decode['C'] = 'Y';
	map_decode['D'] = 'Z';
	map_decode['E'] = 'R';
	map_decode['F'] = 'H';
	map_decode['G'] = 'K';
	map_decode['H'] = 'N';
	map_decode['I'] = 'S';
	map_decode['J'] = 'Q';
	map_decode['K'] = 'T';
	map_decode['L'] = 'W';
	map_decode['M'] = 'U';
	map_decode['N'] = 'O';
	map_decode['O'] = 'V';
	map_decode['P'] = 'X';
	map_decode['Q'] = 'A';
	map_decode['R'] = 'G';
	map_decode['S'] = 'E';
	map_decode['T'] = 'J';
	map_decode['U'] = 'P';
	map_decode['V'] = 'I';
	map_decode['W'] = 'D';
	map_decode['X'] = 'F';
	map_decode['Y'] = 'M';
	map_decode['Z'] = 'C';
	map_decode['.'] = '8';
	map_decode[','] = '4';
	map_decode[';'] = '7';
	map_decode['|'] = '~';
	map_decode['a'] = 'b';
	map_decode['b'] = 's';
	map_decode['c'] = 'k';
	map_decode['d'] = 'j';
	map_decode['e'] = 'i';
	map_decode['f'] = 'n';
	map_decode['g'] = 'r';
	map_decode['h'] = 'v';
	map_decode['i'] = '2';
	map_decode['j'] = 'z';
	map_decode['k'] = '3';
	map_decode['m'] = '0';
	map_decode['n'] = 'w';
	map_decode['p'] = '6';
	map_decode['r'] = 'm';
	map_decode['s'] = 'f';
	map_decode['t'] = 'q';
	map_decode['u'] = 'y';
	map_decode['v'] = 'o';
	map_decode['w'] = 'e';
	map_decode['x'] = 'g';
	map_decode['y'] = 'u';
	map_decode['z'] = 'c';
	map_decode['0'] = '5';
	map_decode['1'] = 'a';
	map_decode['2'] = 'd';
	map_decode['3'] = 'h';
	map_decode['4'] = 'l';
	map_decode['5'] = 'p';
	map_decode['6'] = 't';
	map_decode['7'] = 'x';
	map_decode['8'] = '1';
	map_decode['-'] = '(';
	map_decode['_'] = '9';
	map_decode['!'] = '-';
	map_decode['@'] = '_';
	map_decode['#'] = '!';
	map_decode['$'] = '@';
	map_decode['%'] = '#';
	map_decode['^'] = '$';
	map_decode['&'] = '%';
	map_decode['*'] = '^';
	map_decode['('] = '&';
	map_decode[')'] = '*';
	map_decode['~'] = ')';

}

} /* namespace networkingLab */
