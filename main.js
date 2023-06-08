function sleep(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

var yValue;
var xValue;

async function getWebsocketData() {
  const event = {
    ready: true,
  };

  const websocket = new WebSocket("ws://localhost:8001/");

  websocket.onopen = function () {
    websocket.send(JSON.stringify(event));
  };

  websocket.addEventListener("message", ({ data }) => {
    
    const event = JSON.parse(data);

    console.log("Received: " + data);
    // console.log("Date 1:" + new Date())
    // console.log("Date 2:" + new Date(event.date))
    yValue = event.value
    xValue = new Date(event.date * 1000); // The argument receive in milliseconds, not seconds
  });
}

window.addEventListener("load", function () {



  getWebsocketData();

  // Setup Block
  const data = {
    labels: ["Red", "Blue", "Yellow", "Green", "Purple", "Orange"],
    datasets: [
      {
        label: "# of Votes",
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
