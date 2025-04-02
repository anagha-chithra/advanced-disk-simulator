document.getElementById('toggle-theme').addEventListener('click', function() {
    document.body.classList.toggle('dark-mode');
    localStorage.setItem('theme', document.body.classList.contains('dark-mode') ? 'dark' : 'light');
});

// Preserve theme on reload
if (localStorage.getItem('theme') === 'dark') {
    document.body.classList.add('dark-mode');
}

function simulate() {
    let numRequests = parseInt(document.getElementById("num_requests").value);
    let requestsInput = document.getElementById("requests").value.trim();
    let requests = requestsInput.split(',').map(Number);
    let head = parseInt(document.getElementById("head").value);
    let diskSize = parseInt(document.getElementById("disk_size").value);
    let algorithm = document.getElementById("algorithm").value;
    let output = document.getElementById("output");

    // Input Validations
    if (isNaN(numRequests) || numRequests <= 0) {
        output.innerHTML = "<span style='color:red;'>Enter a valid number of disk requests.</span>";
        return;
    }
    if (requests.length !== numRequests || requests.includes(NaN)) {
        output.innerHTML = `<span style='color:red;'>Enter exactly ${numRequests} valid disk requests.</span>`;
        return;
    }
    if (isNaN(head) || head < 0 || head >= diskSize) {
        output.innerHTML = "<span style='color:red;'>Enter a valid head position within disk size.</span>";
        return;
    }
    if (isNaN(diskSize) || diskSize <= 0) {
        output.innerHTML = "<span style='color:red;'>Enter a valid disk size.</span>";
        return;
    }

    let seekSequence = [];
    let seekTime = 0;
    let currentHead = head;

    if (algorithm === "FCFS") {
        seekSequence = [head, ...requests];
        for (let req of requests) {
            seekTime += Math.abs(currentHead - req);
            currentHead = req;
        }
    } 
    else if (algorithm === "SSTF") {
        let remaining = [...requests];
        seekSequence.push(head);
        while (remaining.length > 0) {
            remaining.sort((a, b) => Math.abs(a - currentHead) - Math.abs(b - currentHead));
            let next = remaining.shift();
            seekSequence.push(next);
            seekTime += Math.abs(currentHead - next);
            currentHead = next;
        }
    }
    else if (algorithm === "SCAN") {
        let left = requests.filter(r => r < head).sort((a, b) => b - a);
        let right = requests.filter(r => r >= head).sort((a, b) => a - b);
        
        seekSequence.push(head);
        for (let i of right) {
            seekSequence.push(i);
            seekTime += Math.abs(currentHead - i);
            currentHead = i;
        }
        if (currentHead < diskSize - 1) {
            seekSequence.push(diskSize - 1);
            seekTime += Math.abs(currentHead - (diskSize - 1));
            currentHead = diskSize - 1;
        }
        for (let i of left) {
            seekSequence.push(i);
            seekTime += Math.abs(currentHead - i);
            currentHead = i;
        }
    }
    else if (algorithm === "C-SCAN") {
        let right = requests.filter(r => r >= head).sort((a, b) => a - b);
        let left = requests.filter(r => r < head).sort((a, b) => a - b);
        
        seekSequence.push(head);
        for (let i of right) {
            seekSequence.push(i);
            seekTime += Math.abs(currentHead - i);
            currentHead = i;
        }
        if (currentHead < diskSize - 1) {
            seekSequence.push(diskSize - 1);
            seekTime += Math.abs(currentHead - (diskSize - 1));
            currentHead = diskSize - 1;
        }
        seekSequence.push(0);
        seekTime += diskSize - 1;
        currentHead = 0;
        
        for (let i of left) {
            seekSequence.push(i);
            seekTime += Math.abs(currentHead - i);
            currentHead = i;
        }
    }
    else if (algorithm === "LOOK") {
        let left = requests.filter(r => r < head).sort((a, b) => b - a);
        let right = requests.filter(r => r >= head).sort((a, b) => a - b);
        seekSequence = [head, ...right, ...left];

        for (let i = 1; i < seekSequence.length; i++) {
            seekTime += Math.abs(seekSequence[i] - seekSequence[i - 1]);
        }
    }
    else if (algorithm === "C-LOOK") {
        let right = requests.filter(r => r >= head).sort((a, b) => a - b);
        let left = requests.filter(r => r < head).sort((a, b) => a - b);
        seekSequence = [head, ...right, ...left];

        for (let i = 1; i < seekSequence.length; i++) {
            seekTime += Math.abs(seekSequence[i] - seekSequence[i - 1]);
        }
    }

    output.innerHTML = `<b>Seek Time:</b> ${seekTime} cylinders<br><b>Sequence:</b> ${seekSequence.join(" ? ")}`;
    drawChart(seekSequence);
}

// Draw Chart
function drawChart(sequence) {
    let ctx = document.getElementById('chart').getContext('2d');

    if (window.myChart) window.myChart.destroy();

    window.myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: sequence.map((_, i) => `Step ${i + 1}`),
            datasets: [{
                label: 'Head Movement',
                data: sequence,
                borderColor: '#007bff',
                backgroundColor: 'rgba(0, 123, 255, 0.2)',
                tension: 0.3
            }]
        },
        options: {
            responsive: true,
            animation: {
                duration: 1500,
                easing: 'easeInOutQuart'
            }
        }
    });
}

