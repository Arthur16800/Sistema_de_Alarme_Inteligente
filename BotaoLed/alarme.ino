void handleAlarme(AdafruitIO_Data *data){
  String valor = data -> toString();

  Serial.print(F("Valor recebido do feed: "));
  Serial.println(valor);

  if (valor == "true"){
    alarmeAtivo = true;
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    Serial.println("Alarme Armado pelo dash / app!");
  }
  else{
    alarmeAtivo = false;
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
    Serial.println("Alarme Desarmado pelo dash / app!");
  }
}

void ativarAlerta(){
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_ALARME, HIGH);
}

void desativarAlerta(){
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ALARME, LOW);
}