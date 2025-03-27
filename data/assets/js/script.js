document.addEventListener("DOMContentLoaded", function () {



    const socket = new WebSocket(`ws://${window.location.hostname}/ws`);

    socket.onopen = () => {
    console.log("WebSocket Connected!");
    socket.send("getReadings");  // request initial data
    };

    socket.onmessage = (event) => {
    const data = JSON.parse(event.data);

    // OPTIONAL: console.log(data);
    setInterval(() => {
        if (socket.readyState === WebSocket.OPEN) {
          socket.send("getReadings");
        }
      }, 2000); // request every 2 seconds
      
    // 1. Update graph data (current)
    chart1.data.datasets[0].data.push(data.solarcurrent || 0);
    chart1.data.datasets[0].data = chart1.data.datasets[0].data.slice(-20);
    chart1.update();

    chart2.data.datasets[0].data.push(data.vbatt || 0); // example use for second graph
    chart2.data.datasets[0].data = chart2.data.datasets[0].data.slice(-20);
    chart2.update();

    // 2. Inject solar voltage into textbox
    if (data.solarbatt !== undefined) {
        document.getElementById('textbox-2-left').innerHTML = `
        <textarea>Solar Voltage: ${data.solarbatt}V</textarea>
        `;
    }
    };

    document.getElementById('textbox-1').innerHTML = `<textarea placeholder="Enter notes here..."></textarea>`;
    document.getElementById('textbox-2-left').innerHTML = `<textarea placeholder="Left input..."></textarea>`;
    document.getElementById('textbox-2-right').innerHTML = `<textarea placeholder="Right input..."></textarea>`;
      
    const ctx1 = document.getElementById('chart-1').getContext('2d');
    const chart1 = new Chart(ctx1, {
      type: 'line',
      data: {
        labels: ['0s', '1s', '2s', '3s', '4s'],
        datasets: [{
          label: '5V Current (mA)',
          data: [100, 120, 115, 130, 125],
          borderWidth: 2,
          fill: false,
          borderColor: 'rgb(75, 192, 192)'
        }]
      },
      options: {
        responsive: true,
        scales: {
          y: { beginAtZero: true }
        }
      }
    });
  
    const ctx2 = document.getElementById('chart-2').getContext('2d');
    const chart2 = new Chart(ctx2, {
      type: 'line',
      data: {
        labels: ['0s', '1s', '2s', '3s', '4s'],
        datasets: [{
          label: 'Solar Current (mA)',
          data: [90, 95, 110, 105, 108],
          borderWidth: 2,
          fill: false,
          borderColor: 'rgb(255, 99, 132)'
        }]
      },
      options: {
        responsive: true,
        scales: {
          y: { beginAtZero: true }
        }
      }
    });





    window.sendToggle = function(command) {
        if (socket.readyState === WebSocket.OPEN) {
          socket.send(command);
          console.log("Sent:", command);
        } else {
          console.log("WebSocket not ready");
        }
      };
      

  });
  