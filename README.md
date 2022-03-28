# InduccionBot

Este repositorio cuenta con el código base para la actividad de inducción del Laboratorio de Robótica de la Universidad de Chile 2022.

## Mecánica del robot
config ruedas

## Uso

### Arduino - `roscpp`

Todo el código está escrito sobre la librería de Adafruit `AFMotor` para el shield L293D. Para su uso es necesario declarar 4 motores según dicha librería.

```cpp
AF_DCMotor m0(1, MOTOR12_64KHZ);
//...
AF_DCMotor m3(4, MOTOR12_64KHZ);
```
Estos deben ser pasados al constuctor de la clase `RobotController`, con la cual se comandará al robot.

```cpp
RobotController bot(m0, m1, m2, m3);
```

La lógica de uso es: cuando ocurre un evento -> modificar velocidades. 

```cpp
void callback_func(){
  // a partir de un evento, modificar las velocidades
  // __speeds = ...
  set_speeds()
```

Finalmente, para que los motores den los pasos necesarios, en el `loop`:

```cpp
void loop() {
  //...
  bot.run()
}
```

El archivo [main.cpp](https://github.com/gonzal0lguin/InduccionBot/blob/main/arduino/InduccionBot/src/main.cpp) es una implementación directa del ejemplo de ROS.org para un [subscriptor simple de arduino](http://wiki.ros.org/rosserial_arduino/Tutorials/Blink). En este caso se usaron mensajes de tipo `Float32MultiArray`, conteniendo velocidad en x-y, velocidad angular y una señal de freno de los motores.

#### IDE

El código fue hecho usando el IDE para VScode [platformIO](https://platformio.org/), el cual es más conveniente que el IDE de Arduino para programar. Para usar el entorno de PlatformIO importar el proyecto de [InduccionBot](https://github.com/gonzal0lguin/InduccionBot/tree/main/arduino/InduccionBot). Para usar el ArduinoIDE importar el proyecto de [InduccionBot-arduinoIDE](https://github.com/gonzal0lguin/InduccionBot/tree/main/arduino/InduccionBot-arduinoIDE).

### Python - `rospy` 

later 

## Configuración ROS

El proyecto ya está configurado para las Raspberry Pi's, por lo tanto no se debe modificar nada para que funcione. Sin embargo, si se crea un nuevo código en python, es necesario hacerlo ejecutable:

```bash
sudo chmod +x new_script.py
```

Recordar que es necesario agregar al inicio del script:

```python
#!/usr/bin/env python
```

Si se quiere configurar un nuevo launch file, seguir [este tutorial](https://automaticaddison.com/how-to-create-and-execute-ros-launch-files/)

## Conexión a los robots y uso

- ssh
- sin launchfile
- con launchfile
