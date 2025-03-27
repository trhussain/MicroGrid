document.addEventListener("DOMContentLoaded", function () {
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
  });
  