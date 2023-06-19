const chargeLevel = document.getElementById("charge-level");
const charge = document.getElementById("charge");
const batteryValue = document.getElementById("battery-value");
const sensorValue = document.getElementById("sensor-value");
const handValue = document.getElementById("hand-value");
const handImg = document.getElementById("hand-img");
const handSrc = {
  true: "assets/mao-fechada.png",
  false: "assets/mao-aberta.png"
};

var yValue;
var xValue;

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

function updateBatteryData(level) {
  let batteryLevel = `${parseInt(level * 100)}%`;
  charge.style.width = batteryLevel;
  chargeLevel.textContent = batteryLevel;
  batteryValue.innerText = batteryLevel; 
}

function updateHandImage(status){
  handImg.src = handSrc[status];
  if (status) {
    handValue.innerText = "Fechada"
  } else {
    handValue.innerText = "Aberta"
  }
}

async function getWebsocketData() {
  const event = {
    ready: true,
  };

  const websocket = new WebSocket(`ws://${configWebsocket.host}:${configWebsocket.port}/`);

  websocket.onopen = function () {
    websocket.send(JSON.stringify(event));
  };

  websocket.addEventListener("message", ({ data }) => {
    
    const event = JSON.parse(data);

    console.log("Received: " + data);

    yValue = event.value
    xValue = new Date(event.date * 1000); // The argument receive in milliseconds, not seconds
    sensorValue.innerText = event.value;
    updateBatteryData(event.battery)
    updateHandImage(event.status)
  });
}

window.addEventListener("load", function () {

  getWebsocketData();

  // Setup Block
  const data = {
    labels: ["Red", "Blue", "Yellow", "Green", "Purple", "Orange"],
    datasets: [
      {
        label: "EMG Sensor Value",
        data: [],
        backgroundColor: "rgba(75, 192, 192, 0.2)",
        borderColor: "rgba(75, 192, 192, 1)",
        borderWidth: 1,
      },
    ],
  };

  // Config block
  const config = {
    type: "line",
    data,
    options: {
      scales: {
        x: {
          type: "realtime",
          realtime: {
            refresh: 200,
            onRefresh: (chart) => {
              chart.data.datasets.forEach((dataset) => {
                dataset.data.push({
                  x: xValue,
                  y: yValue,
                });
              });
            },
          },
        },
        y: {
          beginAtZero: true,
        },
      },
    },
  };

  // Render init Block
  const myChart = new Chart(document.getElementById("myChart"), config);
});
