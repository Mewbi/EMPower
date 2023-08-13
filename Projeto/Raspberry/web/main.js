const sensorValue = document.getElementById("sensor-value");
const triggerStatus = document.getElementById("trigger-status");
const handValue = document.getElementById("hand-value");
const handImg = document.getElementById("hand-img");
const handSrc = {
  false: "assets/mao-fechada.png",
  true: "assets/mao-aberta.png"
};

var yValue;
var xValue;

function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

function updateTriggerStatus(value){
  // Convert o percent
  let percent = ( value / 2 ) * 100
  triggerStatus.innerText = `${percent}%`
}

function updateHandImage(status){
  handImg.src = handSrc[status];
  if (status) {
    handValue.innerText = "Aberta"
  } else {
    handValue.innerText = "Fechada"
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
    updateTriggerStatus(event.trigger_status)
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
