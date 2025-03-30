document.addEventListener("DOMContentLoaded", function () {
  const socket = new WebSocket(`ws://${window.location.hostname}/ws`);

  socket.onopen = () => {
    console.log("WebSocket Connected!");
  };

  socket.onmessage = (event) => {
    console.log("Received:", event.data);

    try {
      const data = JSON.parse(event.data);
      if (data.solarVoltage !== undefined) {
        console.log("Solar Voltage:", data.solarVoltage);
        if (data.solarVoltage !== undefined) {

        document.getElementById("solarVoltageDisplay").innerHTML = `<strong>${data.solarVoltage.toFixed(2)}</strong> V`;;
      }
    }
    } catch (e) {
      console.warn("Could not parse message as JSON");
    }
  };

  socket.onerror = (err) => {
    console.error("WebSocket error:", err);
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
  }, 5000);
});
