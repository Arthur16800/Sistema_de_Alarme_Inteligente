void handleAlarme(AdafruitIO_Data *data) {
  static bool primeiraChamada = true;   // só vale na 1ª vez
  String valor = data->toString();

  Serial.print(F("Valor recebido do feed: "));
  Serial.println(valor);

  if (primeiraChamada) {
    // sincroniza o estado inicial sem disparar mensagens extras
    alarmeAtivo = (valor == "true");
    digitalWrite(LED_AMARELO, alarmeAtivo ? HIGH : LOW);
    digitalWrite(LED_VERDE,   alarmeAtivo ? LOW  : HIGH);

    primeiraChamada = false;
    return;
  }

  // ===== Reage apenas a mudanças após inicialização =====
  if (valor == "true") {
    alarmeAtivo = true;
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    Serial.println("Alarme Armado pelo dash / app!");
  } else {
    alarmeAtivo = false;
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
    Serial.println("Alarme Desarmado pelo dash / app!");
  }
}

void ativarAlerta(){
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_ALARME, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ALARME, LOW);
}

void desligarAlerta(){
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ALARME, LOW);
}