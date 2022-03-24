#include "Parser.h"


bool Parser::read_input(char (&serial_data) [MAX_MSG_LEN])
{
  uint8_t index = 0;
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      delayMicroseconds(200); // lowest i could get working
      char newchar = Serial.read();
      if ((newchar != '\n') and (index < MAX_MSG_LEN)) {
        serial_data[index] = newchar;
        index++;
      }
      else {
        break;
      }
    }
    return true;
  }
  return false;
}

void Parser::clear_data(char (&serial_data) [MAX_MSG_LEN]) {
  for (uint16_t i = 0; i < MAX_MSG_LEN; i++) {
    serial_data[i] = '\0';
  }
}

void Parser::parse_inputs(char serial_data[MAX_MSG_LEN], std::vector<std::string> &args) {
    char delim= ' ';
    uint32_t index= 0;
    std::string tmp_str;
    args.clear();

    while (serial_data[index] != '\0') {
        tmp_str += serial_data[index];
        index++;
        if (serial_data[index] == delim) {
            args.push_back(tmp_str);
            tmp_str = "";
            index++;
        }
        // timeout
        if (index > MAX_MSG_LEN) return;
    }
    args.push_back(tmp_str);
}

void Parser::parse_int(std::string inpt, char &cmd, int &value) {
    
    cmd = inpt[0];
    char tmp_char[3]; // commands are no higher tan 999
    char *p = tmp_char;

    for (uint32_t i = 1; i < inpt.length(); i++) {
        *p = inpt[i];
        p++;
    }
    //value = stoi(temp_arg_char);
    value = (int)strtol(tmp_char, nullptr, 10);
}

void Parser::parse_floats(std::string inpt, char &cmd, double &value) {

    cmd = inpt[0];
    char temp_arg_char[8]; // commands are no higher than s9999.00
    char *p = temp_arg_char;

    for (uint32_t i = 1; i < inpt.length(); i++) {
        *p = inpt[i];
        p++;
    }

    value = strtod(temp_arg_char, nullptr);
}


void Parser::update_commands(std::vector<std::string> inputs){

    __commands.clear();
    __values.clear(); 

    if (inputs.size() == 1) // there´s only mode command
        return;

    for(uint32_t arg_i = 1; arg_i < inputs.size(); arg_i++) // desde adelante del comando 1
    {
        char char_value;
        double dob_value;
        parse_floats(inputs[arg_i], char_value, dob_value);

        __commands.push_back(tolower(char_value));
        __values.push_back(dob_value);
    }
}

double Parser::get(char key_cmd){
    auto it = std::find(__commands.begin(), __commands.end(), key_cmd);
    if (it != __commands.end())
        return __values[std::distance(__commands.begin(), it)];

    return _NOCMD_;
}
