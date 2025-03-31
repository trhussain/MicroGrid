document.addEventListener("DOMContentLoaded", function () {
  const socket = new WebSocket(`ws://${window.location.hostname}/ws`);
  
  const currentData = {
    labels: [],  // timestamps
    datasets: [{
      label: 'Estimated Current (mA)',
      data: [],
      borderWidth: 2,
      fill: false,
      borderColor: 'rgba(75, 192, 192, 1)'
    }]
  };
  
  const currentChart = new Chart(document.getElementById('loadCurrentChart'), {
    type: 'line',
    data: currentData,
    options: {
      scales: {
        x: { title: { display: true, text: 'Time' }},
        y: {
          title: { display: true, text: 'Current (mA)' },
          min: 0,
          max: 60
        }
      }
    }
  });

  
  socket.onopen = () => {
    console.log("WebSocket Connected!");
    showBanner(true);
  };
  const solarVoltageDenom = 1;
  socket.onmessage = (event) => {
    console.log("Received:", event.data);

    try {
      const data = JSON.parse(event.data);
      if (data.solarVoltage !== undefined) {
        console.log("Load1:", data.load1);
        console.log("Load2:", data.load2);
        console.log("Load3:", data.load3);
        console.log("5V Line On/Off:", data.fiveV);

        if (data.solarVoltage !== undefined) {
          console.log("Solar Voltage:", data.solarVoltage);
          document.getElementById("solarVoltageDisplay").innerHTML = `<strong>${data.solarVoltage.toFixed(2)}</strong> V`;
          document.getElementById("fiveVin").innerHTML = `<strong>${data.fiveVoltage.toFixed(2)}</strong> V`;

          const powerAvailable = ((data.fiveV === "on" || (data.solarRailState === "on" && data.solarVoltage > 3.5))  && data.loadCurrent > 1 && data.loadCurrent < 4); 
          console.log("power available: ");
          console.log(powerAvailable);
          const solarUsed = (data.solarRailState === "on") && (data.fiveV === "off" ||  data.solarVoltage > solarVoltageDenom);
          let solarAttenutation = 1;
          if (solarUsed) { 
            solarAttenutation = data.solarVoltage/5;
          }
          let current = 0;
          if (powerAvailable) {
            if (data.load1 === "on") current += ((Math.floor(Math.random() * 3) + 10) * solarAttenutation);
            if (data.load2 === "on") current += ((Math.floor(Math.random() * 3) + 10) * solarAttenutation) ;
            if (data.load3 === "on") current += ((Math.floor(Math.random() * 3) + 10) * solarAttenutation);
          }
        
          const now = new Date().toLocaleTimeString();
          currentData.labels.push(now);
          currentData.datasets[0].data.push(current);
        
          // Keep only the last 20 entries
          while (currentData.labels.length > 10) {
            currentData.labels.shift();
            currentData.datasets[0].data.shift();
          }
        
          currentChart.update();
          // Send latest current value back to ESP32
          const latestCurrent = currentData.datasets[0].data.at(-1); // Get the most recent value
          if (socket.readyState === WebSocket.OPEN) {
            const message = `updateCurrent:${latestCurrent.toFixed(2)}`;
            socket.send(message);
            console.log("Sent to ESP32:", message);
          }
        }
        


    }
    } catch (e) {
      console.warn("Could not parse message as JSON");
    }
  };

  socket.onerror = (err) => {
    console.error("WebSocket error:", err);
    showBanner(false);
  };
  socket.onclose = (event) => {
    console.warn(`WebSocket closed: code=${event.code}, reason=${event.reason}`);
    showBanner(false);
  };
  // Manual toggle command sender
  window.sendToggle = function (command) {
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(command);
      console.log("Sent:", command);
    } else {
      console.warn("WebSocket not ready");
    }
  };

  // Periodic request every 7 seconds
  setInterval(() => {
    if (socket.readyState === WebSocket.OPEN) {
      socket.send("dataRequest");
      console.log("Sent: dataRequest");
    }
  }, 2000);


  function showBanner(isConnected) {
    const banner = document.getElementById("wsStatusBanner");
    if (!banner) return;
    banner.className = isConnected ? "banner connected" : "banner disconnected";
    if (isConnected) {
      banner.textContent = "✅ Connected to MicroGrid Controller";
      // setTimeout(() => banner.style.display = "none", 3000); // hide after 3s
    } else {
      banner.textContent = "⚠️ Disconnected from MicroGrid Controller. Reconnecting...";
      banner.style.display = "block";
    }
  }
  
});
