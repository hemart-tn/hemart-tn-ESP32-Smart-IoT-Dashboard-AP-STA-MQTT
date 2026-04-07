// ================= MODE DETECTION =================
let useMQTT = false;
let websocket;
let client;

// ================= GRAPH =================
let canvas, ctx;
let dataPoints = [];

// ================= INIT =================
window.addEventListener('load', () => {

    canvas = document.getElementById("chart");
    ctx = canvas.getContext("2d");

    canvas.width = 300;
    canvas.height = 200;

    detectMode();
});

// ================= DETECT MODE =================
function detectMode(){

    // kalau IP ESP32 (AP biasanya 192.168.4.x)
    if (location.hostname.startsWith("192.168.4")) {
        console.log("Mode AP (WebSocket)");
        useMQTT = false;
        initWebSocket();
    } else {
        console.log("Mode Internet (MQTT)");
        useMQTT = true;
        initMQTT();
    }
}

// ================= MQTT =================
function initMQTT(){

    client = mqtt.connect(
        "wss://7f55e70e343b4baaada935114c7f9610.s1.eu.hivemq.cloud:8884/mqtt",
        {
            username: "hemart",
            password: "Hemart123@"
        }
    );

    client.on("connect", () => {
        console.log("MQTT Connected");
        client.subscribe("iot/esp32/jarak");
    });

    client.on("message", (topic, message) => {
        updateData(parseInt(message.toString()));
    });
}

// ================= WEBSOCKET =================
function initWebSocket(){

    let gateway = `ws://${location.hostname}/ws`;
    websocket = new WebSocket(gateway);

    websocket.onopen = () => console.log("WS Connected");

    websocket.onclose = () => {
        console.log("WS reconnect...");
        setTimeout(initWebSocket, 2000);
    };

    websocket.onmessage = (event) => {
        updateData(parseInt(event.data));
    };
}

// ================= UPDATE DATA =================
function updateData(value){

    let d = document.getElementById('distance');
    d.innerHTML = value;

    d.style.transform = "scale(1.2)";
    setTimeout(() => d.style.transform = "scale(1)", 150);

    dataPoints.push(value);
    if (dataPoints.length > 30) dataPoints.shift();

    drawGraph();
}

// ================= GRAPH =================
function drawGraph(){

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    ctx.beginPath();
    ctx.strokeStyle = "#00ffff";
    ctx.lineWidth = 2;

    let max = 100;

    for (let i = 0; i < dataPoints.length; i++) {

        let x = (i / 30) * canvas.width;
        let y = canvas.height - (dataPoints[i] / max * canvas.height);

        if (i === 0) ctx.moveTo(x, y);
        else ctx.lineTo(x, y);
    }

    ctx.stroke();
}

// ================= RGB CONTROL =================
function updateRGB(){

    const r = document.getElementById("sliderRed").value;
    const g = document.getElementById("sliderGreen").value;
    const b = document.getElementById("sliderBlue").value;

    document.getElementById("valueRed").value = r;
    document.getElementById("valueGreen").value = g;
    document.getElementById("valueBlue").value = b;

    document.getElementById("barRed").style.width = (r/255*100)+"%";
    document.getElementById("barGreen").style.width = (g/255*100)+"%";
    document.getElementById("barBlue").style.width = (b/255*100)+"%";

    // 🔥 brightness dinamis (tidak ubah logic MQTT/WS)
    document.getElementById("barRed").style.filter = `brightness(${r/255})`;
    document.getElementById("barGreen").style.filter = `brightness(${g/255})`;
    document.getElementById("barBlue").style.filter = `brightness(${b/255})`;

    // ✨ efek glow ringan (opsional, aman)
    document.getElementById("barRed").style.boxShadow = `0 0 ${r/20}px red`;
    document.getElementById("barGreen").style.boxShadow = `0 0 ${g/20}px lime`;
    document.getElementById("barBlue").style.boxShadow = `0 0 ${b/20}px cyan`;

    let msg = `${r},${g},${b}`;

    if (useMQTT && client && client.connected) {
        client.publish("iot/esp32/rgb", msg);
    } else if (websocket && websocket.readyState === WebSocket.OPEN) {
        websocket.send(msg);
    }
}

// ================= EVENT =================
["sliderRed","sliderGreen","sliderBlue"].forEach(id=>{
    document.getElementById(id).addEventListener("input", updateRGB);
});