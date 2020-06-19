
#include <SoftwareSerial.h>

#define RxD 10    //------>Tx BT
#define TxD 11    //------>Rx BT
//#define RST 12    // alimentecion 5v del BT  (conectar directamente a 3.3v~5v)
//#define KEY 4    //  EN del BT  (no hace falta) porque tiene el boton

// en el nuestro tendras que mantener el boton pulsado
// antes de enviar el comando.

SoftwareSerial BTSerial(RxD, TxD);

void setup()
{
 /*
  pinMode(RST, OUTPUT);
  pinMode(KEY, OUTPUT);
  digitalWrite(RST, LOW);
  delay(1000);
  digitalWrite(KEY, HIGH);
  delay(1000);
  digitalWrite(RST, HIGH);
  
  delay(500);
  
  BTSerial.flush();
  delay(500);  */
  BTSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Pulse botton and enter AT commands:");

/*     el script para enviar los comandos automaticamente
 *     me falla, (hace lo que le viene en gana
 *     podemos provar con
 *     BTSerial.flush();
 *     delay(500);
 *     detras de cada comando
 */
/*  BTSerial.print("AT\r\n");
  delay(1000);
  BTSerial.print("AT+VERSION?\r\n");
  delay(1000);
  BTSerial.print("AT+NAME?\r\n");
  delay(1000);
  BTSerial.print("AT+NAME=ARD\r\n");
  delay(1000);
  BTSerial.print("AT+NAME?\r\n");
  delay(1000);
  BTSerial.print("AT+BAUD\r\n");
  delay(1000);
  BTSerial.print("AT+BAUD=4");
  delay(100);
  BTSerial.print("AT+BAUD\r\n");
  delay(100);
  BTSerial.print("AT+PSWD\r\n");
  delay(100);
  BTSerial.print("AT+PSWD=5555");
  delay(100);
  BTSerial.print("AT+PSWD\r\n");
  // Solo para HC-05
  BTSerial.print("AT+ROLE\r\n");
  delay(1000);
  BTSerial.print("AT+ROLE=0");
  delay(1000);
  BTSerial.print("AT+ROLE\r\n"); */
  

}

void loop()
{

  if (BTSerial.available())
    Serial.write(BTSerial.read());

  if (Serial.available())
    BTSerial.write(Serial.read());

}



/********************************************************
 * 
 * AT   test
 * AT+VERSION? Muestra la versión del Firmware. 
 * AT+STATE? 
 * AT+NAME?, Requiere que nos informe del nombre que tiene asignado el modulo.
 * AT+NAMEXXXX, programa el nombre que queremos presentar cuando alguien nos localice
 * AT+BAUD, nos permite solicitar la velocidad a la que está programado el modulo 
 * para hablar con Arduino, y AT+BAUDX, Fija la velocidad de comunicación entre el modulo 
 * y la consola de acuerdo a la siguiente tabla:
 * 
 * 1 configura        1200bps
 * 2 configura        2400bps
 * 3 configura        4800bps
 * 4 configura        9600bps (Default)
 * 5 configura        19200bps
 * 6 configura        38400bps
 * 7 configura        57600bps
 * 8 configura        115200bps
 * 
 * AT+BAUDX
 * AT+ PSWD?
 * AT+ PSWD="XXXX"    //  Siempre 4 digitos
 * 
 * Solo para HC-5
 * 
 * AT+ROLE Nos informa de si está configurado como Esclavo 0, como Maestro 1 o como Slave-Loop 2.
 * AT+ROLEX
 * "o" AT+BAUD? AT+ROLE=X AT+PSSWD AT+PIN
 * 
 * AT+UART
 * AT+UART=<Baud> ,< StopBit>,< Parity>
 * 
 * < Baud > equivale a una velocidad, los valores pueden ser: 
 * 4800, 9600, 19200, 38400, 57600, 115200, 23400, 460800, 
 * 921600 o 1382400.
 * 
 * < StopBit> es el Bit de parada, puede ser 0 o 1, 
 * para 1 bit o 2 bits de parada respectivamente, 
 * Para aplicaciones comunes se trabaja con 1 bit 
 * por lo que este parámetro normalmente se lo deja en 0.
 * 
 * < Parity> Es la paridad, puede ser 
 * 0 (Sin Paridad), 1 (Paridad impar) o 2 (Paridad par). 
 * Para aplicaciones comunes no se usa paridad, 
 * por lo que se recomienda dejar este parámetro en 0.
 * 
 * AT+UART=9600,0,0
 * 
 * ATENCION: SE PERDERA LA CONECCION
 * MODIFICAR BTSerial.begin(38400);
 * POR EL Baud ESPECIFICADO
 * 
 * _________________________
 * MAESTRO
 * 
 * AT+CMODE?
 * AT+CMODE=0
 * 
 * si se va a conectar con un dispositivo en particular 
 * o con cualquiera que esté disponible.
 * 
 * 0 -> Conectarse a un dispositivo con la dirección especificada
 * 
 * 1 -> conectar el módulo a cualquier dirección disponible(aleatorio).
 * 
 * AT+BIND
 * 
 * Para cuando nuestro modulo está configurado como maestro, 
 * y a la vez el modo de conexión está en 0  (CMODE=0)
 * 
 * AT+BIND=<Address>
 * AT+BIND=E668,46,9277F2
 * 
 * < Address > Es la dirección del dispositivo al cual nos vamos
 * a conectar, la dirección se envía de la siguiente forma:
 * 1234,56,ABCDEF la cual equivale a la dirección 12:34:56:AB:CD:EF
 * 
 * AT+RESET
 * 
 * Reiniciar modulo
 * 
 * AT+ORGL
 * 
 * Al hacer esto todos los parámetros del módulo se restablecen, 
 * a los valores por defecto de fábrica. En algunas versiones 
 * la velocidad cambia a 38400 baudios y en otros a 9600.
 * 
 * AT+ADDR?
 * AT+ADDR: 98d3:31:2052e6
 * 
 * Get module address
 * 
 * AT+RNAME
 * 
 * Get the Bluetooth device name
 * 
 * Param: the address of Bluetooth device 
 * 
 * AT+CLASS
 * 
 * Set/Check device class
 * 
 * Param: Device Class 
 * 
 * AT+IAC
 * 
 * Set/Check GIAC (General Inquire Access Code)
 * 
 * Param: GIAC (Default : 9e8b33) 
 * 
 * AT+INQM
 * 
 * Set/Check -- Query access patterns
 * 
 * Param: 
 * 0——inquiry_mode_standard 
 * 1——inquiry_mode_rssi 
 * 
 * Param2: Maximum number of Bluetooth devices to respond to 
 * 
 * Param3: Timeout (1-48 : 1.28s to 61.44s) 
 * 
 * AT+INQM=1,9,48\r\n 
 * 
 * AT+PSWDAT+PIN
 * AT+POLAR
 * 
 * Set/Check LED I/O
 * Param1: 0- PIO8 low drive LED 1- PIO8 high drive LED
 * Param2: 0- PIO9 low drive LED 1- PIO9 high drive LED 
 * 
 * AT+PIO
 * 
 * Set PIO output
 * Param1: PIO number Param2: PIO level 0- low 1- high
 * 
 * AT+IPSCAN
 * 
 * Set/Check – scan parameter
 * Param1: Query time interval
 * Param2 ： Query duration 
 * Param3 ： Paging interval 
 * Param4 ： Call duration 
 * 
 * AT+SHIFF
 * 
 * Set/Check – SHIFF parameter
 * Param1: Max time 
 * Param2: Min time 
 * Param3: Retry time
 * Param4: Time out
 * 
 * AT+SENM
 * 
 * Set/Check security mode
 * 
 * Param1: 
 * 0——sec_mode0+off 
 * 1——sec_mode1+ non_secure 
 * 2——sec_mode2_ service 
 * 3——sec_mode3_l ink 
 * 4——sec_mode_u nknown 
 * 
 * Param2:
 * 0——hci_enc_mod e_off
 * 1——hci_enc_mod e_pt_to_pt
 * 2——hci_enc_mod e_pt_to_pt_and_b cast 
 * 
 * AT+PMSAD
 * 
 * Param: Authenticated Device Address
 * AT+PMSAD =1234,56,abcdef\r\n 
 * 
 * AT+RMAAD
 * 
 * Delete All Authenticated Device
 * 
 * AT+FSAD
 * 
 * Search Authenticated Device
 * 
 * AT+ADCN?
 * 
 * Get Authenticated Device Count
 * 
 * AT+MRAD? 
 * 
 * Most Recently Used Authenticated Device
 * 
 * AT+INIT
 * 
 * Initialize the SPP profile lib
 * 
 * AT+INQ 
 * 
 * Inquiry Bluetooth Device (Buscando dispositivos BT)
 * 
 * AT+ INQC
 * 
 * Cancel Inquiring Bluetooth Device
 * 
 * AT+PAIR
 * 
 * Param1 ：Device Address 
 * Param2：Time out
 * 
 * AT+LINK
 * 
 * Connect Device
 * 
 * Param ： Device Address 
 * 
 * primero autentificar AT+FSAD=1234,56,ABCDEF
 * 
 * AT+DISC
 * 
 * Desconectar
 * 
 * AT+ENSNIFF
 * 
 * Energy-saving mode
 * 
 * Param ： Device Address 
 * 
 * AT+ EXSNIFF
 * 
 * Exerts Energy-saving mode
 * 
 * Param ： Device Address 
 * 
 */


 
