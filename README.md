# InduccionBot

Este repositorio cuenta con el código base para la actividad de inducción del Laboratorio de Robótica de la Universidad de Chile 2022, el cual tiene el fin de inicializarse en Arduino, Raspberry Pi y ROS.

## Mecánica del robot
La cinemática está calculada usando la convención que se muestra en la figura. Por lo tanto, asegurarse que los motores estén conectados en ese orden tanto en hardware como software.

<img width="394" alt="order" src="https://user-images.githubusercontent.com/80728332/160318855-45bcb574-2784-4d73-8b00-588db32ab251.png">

## Uso

- ### Arduino - `roscpp`

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

- ### Python - `rospy` 

El código en python permite usar algoritmos de más alto nivel que en el Arduino, y en este caso los programas en python son los que reciben inputs y comandan valocidades al robot. 
La idea de la actividad es modificar/completar éste código para que publique mensajes del tipo `Float32MultiArray`, a los cuales se suscribe el Arduino. Para llevar a cabo lo anterior se deben asiganr botones/ejes del _joystick_ para comandar **velocidad en x, velocidad en y, velocidad angular** y la **señal de freno**.

Por su puesto, luego de aquello hay libertad de programar más funciones (como modos de manejo, secuancias de movimiento definidas, etc).

Para ver los índices de los botones/ejes del _joystick_ se debe comandar en dos terminales (luego del maestro `roscore`):

```bash
rosrun joy joy_node # inicializar el nodo del joystick
```

```bash
rostopic echo /joy # ver output del joystick 
```

## Conexión a los robots y uso

La conexión a la Raspberry Pi se hace mediante el protocolo _ssh_, para el cual se necesita el *hostname* y la clave, que deben ser preguntadas a los mentores. Una vez se conocen ambas, en una terminal:

```bash
ssh pi@hostname.local
```

### Inicialización **sin** roslaunch

En el software hay 2 nodos, `/joy` y `/bot_vel`. La Raspberry se suscribe a los mensajes del control remoto y publica sobre las velocidades que debe tener el robot, las cuales son computadas por el Arduino. Para inicializar el control remoto, la Raspberry y el Arduino se deben ejecutar los siguientes 3 comandos, aparte del nodo maestro en 4 terminales distintas.

```bash
roscore
```
```bash
rosrun joy joy_node
```
```bash
rosrun rosserial_arduino serial_node.py port:=/dev/ttyUSB0
```
```bash
rosrun induccion teleop.py
```

El último comando se puede reemplazar por `python teleop.py`, estando dentro del directorio que contiene al archivo `teleop.py`.

### Inicialización con roslaunch

Como es poco conveniente tener que abrir 4 terminales en la Raspberry, existe una manera más simple de inicializar todos los nodos con un solo comando, llamado [roslaunch](http://wiki.ros.org/roslaunch). En los robots ya está configurado un launchfile que se ejecuta con:

```bash
roslaunch induccion bot_control.launch
```

Como ya está todo configurado, no se debe modificar nada para que funcione. Sin embargo, si se crea un nuevo código en python, es necesario hacerlo ejecutable:

```bash
sudo chmod +x new_script.py
```

Recordar que es necesario agregar al inicio del script:

```python
#!/usr/bin/env python
```

Por último, si se quiere configurar un nuevo launch file para un nuevo script, seguir [este tutorial](https://automaticaddison.com/how-to-create-and-execute-ros-launch-files/).
