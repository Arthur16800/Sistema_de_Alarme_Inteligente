import React, { useState, useEffect } from "react";
import { View, Button } from "react-native";
import { useNavigation } from "@react-navigation/native";
import api from "./axios/axios";

const toBool = (v) => v === true || v === "true" || v === 1 || v === "1";

const HomeScreen = () => {
  const [stateLED, setStateLED] = useState({ value: false });
  const navigation = useNavigation();

  const handleCam = () => navigation.navigate("Cam");

  useEffect(() => {
    async function getToggle() {
      try {
        const response = await api.getFeedLed(); 
        const v = toBool(response.data.last_value);
        setStateLED({ value: v });
      } catch (error) {
        console.log("Erro:", error?.response?.data || error.message);
      }
    }
    getToggle();
  }, []);

  async function ledToggle() {
    try {
      const newVal = !stateLED.value;       
      await api.toggleLED({ value: String(newVal) }); 
      setStateLED({ value: newVal });          
    } catch (error) {
      console.log("Erro:", error?.response?.data || error.message);
    }
  }

  return (
    <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
      <View style={{ marginBottom: 20 }}>
        <Button title="Abrir Câmera" onPress={handleCam} color="blue" />
      </View>

      <View style={{ marginBottom: 20 }}>
        <Button
          title={stateLED.value ? "Desligar alarme" : "Ligar alarme"}
          onPress={ledToggle}
          color={stateLED.value ? "red" : "green"}
        />
      </View>

      <View style={{ marginBottom: 20 }}>
        <Button title="Listar Eventos" onPress={() => navigation.navigate("Eventos")} />
      </View>
    </View>
  );
};

export default HomeScreen;
