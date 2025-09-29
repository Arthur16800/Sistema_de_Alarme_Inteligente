import axios from "axios";
 
const api = axios.create({
    baseURL: "https://io.adafruit.com/api/v2/pedrolemosbonini/feeds/",
    headers:{
        accept: "application/json",
        "Content-Type" : "application/json",
        "X-AIO-Key":"aio_XyOs09aEFiDCPbwmiAlPRFJ8aTpa"
    },
});

const sheets = {
    toggleLED: (stateLED) => api.post("botaoalarme/data", stateLED),
    getFeedLed: () => api.get("botaoalarme")
};

export default sheets;

