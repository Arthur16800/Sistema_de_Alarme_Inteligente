void testeBotao(int pinoBotao){
  Serial.print(F("Estado botao: "));
  Serial.println(digitalRead(pinoBotao));
  delay(500);
}