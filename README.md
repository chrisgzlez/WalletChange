# WalletChange
Programa que realiza el cambio de una cantidad introducida por linea de comandos usando el número mínimo de billetes y monedas según un diseño algoritmico voraz.
El proyecto además permite el uso de distintos tipos de moneda (almacenados en .txt)
Y soporta dos modos de cambio:
   * Ilimitado: Sin stock o limite de monedas o billetes a usar
   * Limitado: Con un stock límite de monedas. En este modo el programa es posible que no pueda producir cambio y debe avisar de ello, además está implementada una 
función de re-stock.

# Sumario del Proyecto
Sumario del Proyecto original tal cual se nos fué entregado encontrado en la carpeta 'Docs'
    
# CARPETA TAD:
Se encuentran los modulos TAD (tipos abstractos de datos) empleados en el programa principal. La implementación de estos TADs se nos fué proporcionado de antemano
    
# ARCHIVOS:
Se encuentran los siguientes archivos:
  * main: programa principal que incluye la interfaz de usuario (CLI)
  * utilities: reune diversas herramientas básicas para el programa (conversión de estructuras de datos, user input...)
  * wallet: módulo de manejo de los cambios de monedas y que contiene su propia UI (CLI)
  * .txt: diversos archivos que almacenan los datos de los monederos a usar (tipo de moneda, valores de monedas y cantidad de monedas)
  * makefile: archivo que nos facilita y automatiza el proceso de compilación del proyecto mediante el uso de la terminal y de los comandos especificados en la propia makefile
