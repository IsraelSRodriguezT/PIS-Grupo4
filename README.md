# Manual de Usuario para Panel Solar Automático

## Índice

1. [Introducción](#introducción)
2. [Descripción del Sistema](#descripción-del-sistema)
3. [Componentes](#componentes)
4. [Instalación](#instalación)
5. [Orientación de la Caja del Panel Solar](#orientación-de-la-caja-del-panel-solar)
6. [Funcionamiento](#funcionamiento)
   - [Modo Manual](#modo-manual)
   - [Modo Automático](#modo-automático)
7. [Mantenimiento](#mantenimiento)
8. [Solución de Problemas](#solución-de-problemas)
9. [Información de Contacto](#información-de-contacto)

## Introducción

Bienvenido al manual de usuario del panel solar automático. Este dispositivo está diseñado para optimizar la captura de energía solar mediante el seguimiento del sol en dos modos: manual y automático. 

## Descripción del Sistema

El panel solar automático puede operar en dos modos:

- **Modo Manual:** El usuario ingresa las coordenadas geográficas y el sistema calcula la posición del sol para ajustar el panel.
- **Modo Automático:** Utiliza fotorresistencias para seguir la luz solar de manera automática.

## Componentes

- **Arduino Uno R3:** Controlador principal que recibe y envía señales.
- **Panel Solar de 5V:** Dispositivo que captura la energía solar.
- **Batería tipo LiPo de 2200 mAh con 3.7V:** Fuente de almacenamiento de energía.
- **Elevador de Voltaje Módulo MT3608:** Convierte voltajes de entrada de 2 a 24V a salida de 5 a 28V.
- **Módulo de Carga para Baterías LiPo TP4056:** Regula la carga de la batería LiPo.
- **Servomotores SG90:** Motores para ajustar la posición del panel solar.
- **Protoboard:** Plataforma para montar y conectar los componentes electrónicos.
- **Diodo 1N5819:** Diodo de rectificación para evitar la inversión de polaridad.
- **Controlador de Carga Solar HW 736:** Controlador específico para la carga de baterías solares.
- **Fotorresistencias:** Detectores de luz que permiten el seguimiento automático.
- **Interruptores:**
  - **Interruptor de Modo** Permite seleccionar entre modo manual (posición derecha) y modo automático (posición izquierda).
  - **Interruptor para salida de USB (Establecer una carga):**  Permite encender (posición derecha) o apagar (posición izquierda) la salida de carga del panel solar. Debe estar en la posición derecha (encendido) solo cuando desee cargar dispositivos, como un celular. En la posición izquierda (apagado), la salida de carga está desactivada.

## Instalación

1. **Conexión del Hardware:**
   - Conecte las fotorresistencias en los lados del panel solar según las indicaciones del diagrama de conexión.
   - Conecte el Arduino al computador a través del puerto USB (COM 3).

2. **Configuración del Software:**
   - Instale los drivers necesarios para Arduino desde [Arduino Software (IDE) y Drivers](https://www.arduino.cc/en/software).
   - Compile y cargue el programa en C en su sistema utilizando el entorno de desarrollo adecuado.

## Cómo Compilar el Programa en C

1. **Preparación:**
   - Asegúrese de tener un entorno de desarrollo en C instalado, como [Code::Blocks](http://www.codeblocks.org/) o [Dev-C++](https://sourceforge.net/projects/orwelldevcpp/).

2. **Código Fuente:**
   - Copie el código fuente del programa en C en un archivo con extensión `.c`.

3. **Compilación:**
   - Abra el entorno de desarrollo.
   - Cree un nuevo proyecto y añada el archivo `.c`.
   - Compile el programa seleccionando la opción de compilación en el menú del entorno.
   - Si la compilación es exitosa, el programa ejecutable estará disponible en la carpeta de salida del proyecto.

4. **Carga en Arduino:**
   - Conecte el Arduino al computador y asegúrese de que el puerto COM (COM 3) esté seleccionado en el entorno de desarrollo.
   - Use el IDE de Arduino para cargar el archivo compilado al Arduino.

## Orientación de la Caja del Panel Solar

Para un funcionamiento óptimo del panel solar, la orientación de la caja debe ser precisa. La flecha verde en la parte superior de la caja debe apuntar exactamente al norte verdadero.

### Materiales Necesarios

- Brújula o GPS para orientación
- Nivel de burbuja (opcional, pero recomendado para asegurar que la caja esté nivelada)

### Instrucciones de Ubicación y Orientación

1. **Seleccionar el Lugar:**
   - Elija un lugar despejado que reciba la mayor cantidad de luz solar durante el día.
   - Asegúrese de que no haya obstáculos (como árboles o edificios) que puedan bloquear la luz solar.

2. **Orientar la Caja:**
   - Coloque la caja en el lugar seleccionado.
   - Utilice una brújula o un GPS para determinar la dirección del norte verdadero (no el norte magnético).
   - Gire la caja hasta que la flecha verde en la parte superior apunte exactamente al norte verdadero.

3. **Nivelar la Caja:**
   - Use un nivel de burbuja para asegurarse de que la caja esté nivelada.
   - Ajuste la posición de la caja si es necesario para garantizar que esté perfectamente horizontal.

### Verificación

1. **Confirmar Orientación:**
   - Verifique con la brújula o GPS que la flecha verde esté alineada con el norte verdadero.
   - La precisión en la orientación es crucial para el cálculo correcto del azimut.

2. **Pruebas Iniciales:**
   - Ejecute el sistema en modo manual ingresando las coordenadas y la hora del sistema.
   - Verifique que el panel solar se mueva en la dirección correcta según los cálculos del programa en C.

## Funcionamiento

### Modo Manual

1. **Ingreso de Coordenadas:**

   - **Paso 1:** Conecte su computadora al Arduino y asegúrese de que el puerto COM (COM 3) esté correctamente configurado.
   - **Paso 2:** Compile y ejecute el programa en C en su entorno de desarrollo.
   - **Paso 3:** El programa pedirá que ingrese las coordenadas geográficas y la hora actual a través de la consola. Ingrese las siguientes coordenadas predefinidas para realizar una prueba:

     - **Latitud:** -3.99313
     - **Longitud:** -79.20422

     ```c
     // Ejemplo de ingreso de coordenadas y hora
     printf("Ingresa como dato decimal el valor de la latitud de tu zona. Teniendo en cuenta el rango [-90,90]\n");
     datoingresado = scanf("%f", &coordenada.lat);
     
     printf("Ingresa como dato decimal el valor de la longitud de tu zona. Teniendo en cuenta el rango [-180,180]\n");
     datoingresado2 = scanf("%f", &coordenada.lon);
     ```

   - **Paso 4:** El programa calculará la posición del sol (azimut y altura solar) basado en las coordenadas ingresadas.

2. **Ejecución del Programa en C:**

   - El programa en C ejecutará los cálculos necesarios para determinar el azimut y la altura solar.
   - Los valores calculados se enviarán al Arduino a través del puerto COM 3. Asegúrese de que el puerto serial esté correctamente configurado en su código y hardware.

     ```c
     FILE *serial = fopen("COM3", "w");
     fprintf(serial, "%d %d\n", psSpa.aziG, psSpa.asG);
     fclose(serial);
     ```

### Modo Automático

1. **Seguimiento con Fotorresistencias:**

   - Asegúrese de que las fotorresistencias estén correctamente instaladas y calibradas.
   - En modo automático, el sistema ajustará el panel solar en función de la luz detectada por las fotorresistencias.

2. **Interruptores:**

   - **Interruptor Principal:** 
     - **Encendido (izquierda):** La salida de carga del panel solar está activada. Use esta posición para cargar dispositivos, como un celular.
     - **Apagado (derecha):** La salida de carga está desactivada.
   - **Interruptor de Modo:** 
     - **Modo Manual (derecha):** El panel solar se ajustará basado en las coordenadas y hora ingresadas manualmente.
     - **Modo Automático (izquierda):** El panel solar ajustará su posición automáticamente según la luz detectada por las fotorresistencias.

## Mantenimiento

- Revise regularmente las conexiones y el estado de las fotorresistencias.
- Mantenga el panel solar limpio y libre de obstrucciones para garantizar una captación óptima de energía.
- Verifique periódicamente la orientación y nivelación de la caja para asegurar el correcto funcionamiento del sistema.

## Solución de Problemas

- **No se mueve en modo manual:**
  - Verifique la conexión del Arduino al puerto USB (COM 3).
  - Asegúrese de que el programa en C esté correctamente compilado y cargado en el Arduino.

- **No se mueve en modo automático:**
  - Revise las fotorresistencias y sus conexiones.
  - Asegúrese de que el interruptor principal esté en la posición izquierda (encendido) si está intentando cargar un dispositivo y el interruptor de modo esté en la posición izquierda (modo automático).

## Información de Contacto

Para más información o asistencia técnica, puede contactarse con nosotros:

- **Isrrael Rodrigues:** [GitHub](https://github.com/IsraelSRodriguezT)
- **Royel Jima:** [GitHub](https://github.com/R0yalCode)
- **Steveen Pardo:** [GitHub](https://github.com/Dan1el17)
- **Juan Calopino:** [GitHub](https://github.com/JuaaanCalopino)
- **Carlos Granda:** [GitHub](https://github.com/Carlosjosu)
