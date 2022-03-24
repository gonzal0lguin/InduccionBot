#ifndef BOT_SLAVE_PARSER_H
#define BOT_SLAVE_PARSER_H

#include <Arduino.h>
#include <ArduinoSTL.h>

#define MAX_MSG_LEN 100
#define _NOCMD_ 9999
#define BAUD_RATE 57600

class Parser { 
    public:
        // VARIABLES
        bool parseState = false;

        // FUNCTIONS
        bool read_input(char (&serial_data) [MAX_MSG_LEN]);
        void clear_data(char (&serial_data) [MAX_MSG_LEN]);
        void parse_inputs(char serial_data [MAX_MSG_LEN], std::vector<std::string> &args);
        void parse_int(std::string inpt, char &cmd, int &value);
        void parse_floats(std::string inpt, char &cmd, double &value);
        void update_commands(std::vector<std::string> inputs);
        double get(char key_cmd);
        
    private:
        std::vector<char> __commands;
        std::vector<double> __values;
};

#endif