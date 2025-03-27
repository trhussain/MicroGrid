document.addEventListener("DOMContentLoaded", function () {
  const socket = new WebSocket(`ws://${window.location.hostname}/ws`);

  socket.onopen = () => {
    console.log("WebSocket Connected!");
  };
                                  
  
  socket.onmessage = (event) => {
    console.log("Received:", event.data);
  };

  socket.onerror = (err) => {
    console.error("WebSocket error:", err);
  };

  window.sendToggle = function (command) {
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(command);
      console.log("Sent:", command);
    } else {
      console.warn("WebSocket not ready");
    }
  };
});
