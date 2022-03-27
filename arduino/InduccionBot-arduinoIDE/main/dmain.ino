// #include <Arduino.h>
// #include "botController.h"
// #include "parser.h"

// AF_DCMotor m0(1, MOTOR12_64KHZ);
// AF_DCMotor m1(2, MOTOR12_64KHZ);
// AF_DCMotor m2(3, MOTOR12_64KHZ);
// AF_DCMotor m3(4, MOTOR12_64KHZ);

// RobotController bot(m3, m2, m1, m0);
// Parser parser;

// char serialData[MAX_MSG_LEN];
// uint64_t t_last;

// void setup() {
//   t_last = millis();
//   Serial.begin(BAUD_RATE);
// }

// int state = 0;
// void loop() {

//   char base_cmd;
//   int base_val;
//   char input_data[MAX_MSG_LEN];

//   while (true){
//     parser.clear_data(input_data);
//     if (parser.read_input(input_data)){
//       std::vector<std::string> args;
//       parser.parse_inputs(input_data, args);
//       parser.parse_int(args[0], base_cmd, base_val);
//       parser.update_commands(args);

//       switch (tolower(base_cmd)) {
//         case 'g': {
//           switch (base_val) {
//             case 0: {
//               bot.compute_linear_combination(parser.get('x'), parser.get('y'), parser.get('w'));
//               break;
//             }
//             case 1: {
//               //bot.compute_linear_combination(parser.get('x'), parser.get('y'), parser.get('w'));
//               bot.forward();
//               break;
//             }

//             case 2: {
//               bot.backward();
//               break;
//             }

//             case 3: {
//               bot.right();
//               break;
//             }

//             case 4: {
//               bot.left();
//               break;
//             }

//             case 5: {
//               bot.turn_left();
//               break;
//             }

//             case 6: {
//               bot.turn_right();
//               break;
//             }

//             case 12: {
//               bot.stop();
//               break;
//             }
//             default: break;
//           }
//           break;
//         }

//         default: break;
//       }

//       Serial.println("ok");
//     }
  
//     bot.run();
//   }
// }