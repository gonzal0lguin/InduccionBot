# InduccionBot

Este repositorio cuenta con el código base para la actividad de inducción del Laboratorio de Robótica de la Universidad de Chile 2022.

## Uso

```cpp
void callback_func(){
  // a partir de un evento, modificar las velocidades
  // __speeds = ...
  set_speeds()
```

Para que los motores den los pasos necesarios, en el `loop` es necesario:

```cpp
void loop() {
  //...
  bot.run()
}
```

## Configuración ROS

Cuando se crea un nuevo código en python, es necesario hacerlo ejecutable:

```bash
sudo chmod +x new_script.py
```

Recordar que es necesario agregar al inicio del script:

```python
#!/usr/bin/env python
```

Si se quiere configurar un nuevo launch file, seguir [este tutorial](https://automaticaddison.com/how-to-create-and-execute-ros-launch-files/)
