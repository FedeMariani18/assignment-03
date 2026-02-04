package core;

import interfaces.ControlInterface;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import core.Common.State;

public class SystemController implements ControlInterface {

    private State mode = State.AUTOMATIC;
    private int valve = 0;
    private boolean connected = true;

    private Random rand = new Random();

    @Override
    public synchronized State getState() {
        return mode;
    }

    @Override
    public synchronized void setState(State mode) {
        this.mode = mode;
    }

    @Override
    public synchronized int getValveOpening() {
        return valve;
    }

    @Override
    public synchronized void setValveOpening(int value) {
        if (mode == State.MANUAL) {
            valve = value;
        }
    }

    @Override
    public synchronized boolean isConnected() {
        return connected;
    }

    @Override
    public synchronized List<Integer> getMeasurements(int n) {
        //TODO: temporaneo
        List<Integer> values = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            values.add(20 + rand.nextInt(30));
        }

        return values;
    }
}
