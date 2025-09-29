#include <math.h>
#include "AdafruitIO_WiFi.h"
#include "NewPing.h"


#define BUZZER_PIN 27
#define LED_ALARME 13
#define BOTAO_FISICO 26
#define TRIG_PIN 12
#define ECHO_PIN 14
#define LED_AMARELO 25
#define LED_VERDE 33

// Configuração do ultrassonico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Configurações da rede WIFI
#define WIFI_SSID "IIIII"
#define WIFI_PASS "bonas222"

// Autenticação Adafruit IO
#define IO_USERNAME "pedrolemosbonini"
#define IO_KEY "aio_XyOs09aEFiDCPbwmiAlPRFJ8aTpa"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// #define pinLed 14 //Pino do LED

AdafruitIO_Feed *botaoalarme = io.feed("botaoalarme");
AdafruitIO_Feed *distanciaultrassom = io.feed("distanciaultrassom");

// Variáveis de controle
bool alarmeAtivo = false;
int distancia = 0;
int distancia_anterior = 0;
int LIMITE_DISTANCIA = 15;

void setup() {
  // pinMode(pinLed, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_ALARME, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);

  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  // Vincula a função callback ao feed
  botaoalarme->onMessage(handleAlarme);

  Serial.println("Solicitando o estado inicial do alarme: ");
  botaoalarme->get();

  // Configuração do callack, quando o feed receber(atualizar) um valor
  //botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado
}

void loop() {

  // // Manter a conexão com o Adafruit IO ativa
  io.run();


  // Leitura do botão físico
  if (digitalRead(BOTAO_FISICO) == 1) {
    delay(200);
    alarmeAtivo = !alarmeAtivo;

    botaoalarme->save(String(alarmeAtivo ? "true" : "false"));
    Serial.println(alarmeAtivo ? "Alarme ARMADO pelo botao fisico" : "alarme DESARMADO pelo botao fisico");
  }



  // // Chamada da função publish
  // // publicacao();

  distancia_anterior = distancia;
  distancia = sonar.ping_cm();

  if (distancia != 0 && distancia != distancia_anterior) {
    // Só envia distancias válidas
    distanciaultrassom->save(distancia);
    Serial.print("Distancia: ");
    Serial.println(distancia);
  }

  if (alarmeAtivo) {
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  // Ativação ou desativação do alarme
  if (alarmeAtivo && distancia > 0 && distancia < LIMITE_DISTANCIA) {
    ativarAlerta();
  } else {
    desligarAlerta();
  }

  delay(500);  //Intervalo ideal para a Adafruit
}