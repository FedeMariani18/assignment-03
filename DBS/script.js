const BASE_URL = "http://localhost:8080/api";
const POLLING_INTERVAL = 2000;
const N_MEASUREMENTS = 20;

const stateElem = document.getElementById("system-state");
const valveElem = document.getElementById("valve-value");
const modeBtn = document.getElementById("mode-btn");
const slider = document.getElementById("valve-slider");
const sliderValue = document.getElementById("slider-value");

let currentMode = null;

// Chart.js
const ctx = document.getElementById("levelChart").getContext("2d");
const chart = new Chart(ctx, {
    type: "line",
    data: {
        labels: [],
        datasets: [{
            label: "Water Level",
            data: [],
            borderWidth: 2,
            tension: 0.2
        }]
    }
});

function setSystemState(state) {
    stateElem.textContent = state;
    stateElem.className = "state";

    if (state === "MANUAL") stateElem.classList.add("manual");
    else if (state === "AUTOMATIC") stateElem.classList.add("automatic");
    else if (state === "UNCONNECTED") stateElem.classList.add("unconnected");
    else stateElem.classList.add("not-available");
}

async function fetchStatus() {
    const r = await fetch(`${BASE_URL}/status`);
    if (!r.ok) throw new Error();
    return r.json();
}

async function fetchMeasurements() {
    const r = await fetch(`${BASE_URL}/measurements?last=${N_MEASUREMENTS}`);
    if (!r.ok) throw new Error();
    return r.json();
}

/* === COMANDI VERSO IL CUS === */

async function sendMode(mode) {
    await fetch(`${BASE_URL}/mode`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ mode })
    });
}

async function sendValve(value) {
    await fetch(`${BASE_URL}/valve`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ value })
    });
}

/* === EVENTI GUI === */

modeBtn.addEventListener("click", async () => {
    const newMode = currentMode === "MANUAL" ? "AUTOMATIC" : "MANUAL";
    await sendMode(newMode);
});

slider.addEventListener("input", async () => {
    const value = slider.value;
    sliderValue.textContent = value + "%";
    await sendValve(value);
});

/* === AGGIORNAMENTO DASHBOARD === */

async function updateDashboard() {
    try {
        const status = await fetchStatus();
        const measurements = await fetchMeasurements();

        currentMode = status.mode;
        setSystemState(currentMode);

        valveElem.textContent = status.valve;
        slider.disabled = currentMode !== "MANUAL";
        slider.value = status.valve;
        sliderValue.textContent = status.valve + "%";

        modeBtn.textContent =
            currentMode === "MANUAL"
                ? "Switch to AUTOMATIC"
                : "Switch to MANUAL";

        chart.data.labels = measurements.map((_, i) => i + 1);
        chart.data.datasets[0].data = measurements;
        chart.update();

    } catch {
        setSystemState("NOT AVAILABLE");
        slider.disabled = true;
        valveElem.textContent = "--";
    }
}

updateDashboard();
setInterval(updateDashboard, POLLING_INTERVAL);
