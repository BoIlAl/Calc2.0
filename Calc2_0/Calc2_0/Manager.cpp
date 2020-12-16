#include "Manager.h"

Manager::Manager() {
	Calculator* calc = new Calculator();
	string s; 
	double answer;
	

	while (getline(std::cin, s) && s != "\n") {
		CALC_ERRORS temp = calc->countTheString(s, answer);
		switch (temp) {
		case CE_DLLLOADER:
			cout << "dll error" << endl;
			break;
		case CE_OPERATION:
			cout << "operation error" << endl;
			break;
		case CE_PARSER:
			cout << "parser error" << endl;
			break;
		case CE_OTHER:
			cout << "internal error" << endl;
			break;
		case CE_OK:
			cout << answer << endl;
		}
	}
}
