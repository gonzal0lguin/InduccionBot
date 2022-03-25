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
